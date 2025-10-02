#include <stdexcept>
#include "xparserlib/rule.hpp"
#include "xparserlib/symbol_parser.hpp"
#include "xparserlib/string_parser.hpp"
#include "xparserlib/loop_zero_parser.hpp"
#include "xparserlib/loop_one_parser.hpp"
#include "xparserlib/optional_parser.hpp"
#include "xparserlib/logical_and_parser.hpp"
#include "xparserlib/logical_not_parser.hpp"
#include "xparserlib/sequence_parser.hpp"
#include "xparserlib/choice_parser.hpp"
#include "xparserlib/match_parser.hpp"
#include "xparserlib/bool_parser.hpp"


namespace xparserlib {


    class rule_reference : public parser {
    public:
        class rule* rule;

        rule_reference(class rule* r) : rule(r) {}

        bool parse(parse_context& pc) const override {
            return rule->parse(pc);
        }
    };


    class lrm {
    public:
        static auto get_left_recursion_state(parse_context& pc) {
            return pc.m_lrs.back();
        }

        static void push_left_recursion_state(parse_context& pc) {
            pc.m_lrs.push_back({ pc.m_position, pc.m_matches.size(), pc.line(), pc.column() });
        }

        static void pop_left_recursion_state(parse_context& pc) {
            pc.m_lrs.pop_back();
        }
    };


    class lr_context : public parser {
    public:
        lr_context(const parser_ptr& parser)
            : m_parser(parser)
        {
        }

        bool parse(parse_context& pc) const override {
            lrm::push_left_recursion_state(pc);
            const bool result = m_parser->parse(pc);
            lrm::pop_left_recursion_state(pc);
            return result;
        }

    private:
        const parser_ptr m_parser;
    };


    class lr_match : public parser {
    public:
        lr_match(match_type type)
            : m_type(type)
        {
        }

        bool parse(parse_context& pc) const override {
            const auto lr_start_state = lrm::get_left_recursion_state(pc);
            pc.add_match(m_type, lr_start_state.position, lr_start_state.line, lr_start_state.column, pc.position(), pc.line(), pc.column(), lr_start_state.match_count);
            return true;
        }

    private:
        const match_type m_type;
    };


    static parser_ptr convert_immediate_left_recursion(const parser_ptr& p, rule* r) {
        //the top level must be a choice
        choice_parser* choice = dynamic_cast<choice_parser*>(p.get());
        if (!choice) {
            return p;
        }

        auto it = choice->parsers().begin();
        const auto end = choice->parsers().end();

        std::vector<std::tuple<std::shared_ptr<match_parser>, std::shared_ptr<sequence_parser>>> recursive_branches;

        //gather the immediate-left-recursive branches of the choice
        for (; it != end; ++it) {
            const parser_ptr& cc = *it;

            std::shared_ptr<sequence_parser> sequence;

            //get sequence from match
            std::shared_ptr<match_parser> mp = std::dynamic_pointer_cast<match_parser>(cc);
            if (mp) {
                sequence = std::dynamic_pointer_cast<sequence_parser>(mp->parser());
            }

            //else get direct sequence
            else {
                sequence = std::dynamic_pointer_cast<sequence_parser>(cc);
            }

            //not a sequence; stop
            if (!sequence) {
                break;
            }

            //found a sequence; if first child is not a rule reference to the given rule, stop
            rule_reference* rr = dynamic_cast<rule_reference*>(sequence->parsers()[0].get());
            if (!rr || rr->rule != r) {
                break;
            }

            //found immediate left-recursive branch
            recursive_branches.push_back({mp, sequence});
        }

        //if there are no recursive branches, return the original parser
        if (recursive_branches.empty()) {
            return p;
        }

        parsers_type non_recursive_branches;

        //gather the non-left recursive branches
        for (; it != end; ++it) {
            non_recursive_branches.push_back(*it);
        }

        //if there are non non-recursive branches, throw an error
        if (non_recursive_branches.empty()) {
            throw std::logic_error("choice without a non-left-recursive branch");
        }

        //convert the grammar
        parsers_type result_sequence_parsers;

        //add a choice with the non-left recursive branches, if they are multiple
        if (non_recursive_branches.size() == 1) {
            result_sequence_parsers.push_back(non_recursive_branches[0]);
        }
        else {
            result_sequence_parsers.push_back(std::make_shared<choice_parser>(non_recursive_branches));
        }

        //gather all the left-recursive branches, stripped of left recursion
        parsers_type left_recursive_choice_parsers;
        for (const auto& e : recursive_branches) {
            const auto& match_parser_ptr = std::get<0>(e);
            const auto& sequence_parser_ptr = std::get<1>(e);

            //strip of the first entry of the parsers of the sequence
            parsers_type sequence_parsers = sequence_parser_ptr->parsers();
            sequence_parsers.erase(sequence_parsers.begin());

            //add a left-recursive match, if a match exists
            if (match_parser_ptr) {
                sequence_parsers.push_back(std::make_shared<lr_match>(match_parser_ptr->type()));
            }

            //add a sequence
            left_recursive_choice_parsers.push_back(std::make_shared<sequence_parser>(sequence_parsers));
        }

        //create a left recursion continuation choice if needed
        if (left_recursive_choice_parsers.size() == 1) {
            result_sequence_parsers.push_back(std::make_shared<loop_zero_parser>(left_recursive_choice_parsers[0]));
        }
        else {
            result_sequence_parsers.push_back(std::make_shared<loop_zero_parser>(std::make_shared<choice_parser>(left_recursive_choice_parsers)));
        }


        //return a sequence parser inside a left recursion context parser
        return std::make_shared<lr_context>(std::make_shared<sequence_parser>(result_sequence_parsers));
    }


    rule::rule(const parser_ptr& parser)
        : m_parser(convert_immediate_left_recursion(parser, this))
    {
    }


    rule::rule(symbol_type symbol) 
        : rule(parser(symbol))
    {
    }


    rule::rule(const char* string)
        : rule(parser(string))
    {
    }


    rule::rule(const wchar_t* string)
        : rule(parser(string))
    {
    }


    rule::rule(const string_type& string)
        : rule(parser(string))
    {
    }


    rule::rule(const std::initializer_list<symbol_type>& string)
        : rule(parser(string))
    {
    }


    rule::rule(bool value)
        : rule(parser(value))
    {
    }


    rule& rule::operator = (const parser_ptr& parser) {
        m_parser = convert_immediate_left_recursion(parser, this);
        return *this;
    }


    parser_ptr rule::operator *() {
        return make_loop_zero_parser(parser(*this));
    }


    parser_ptr rule::operator +() {
        return make_loop_one_parser(parser(*this));
    }


    parser_ptr rule::operator -() {
        return make_optional_parser(parser(*this));
    }


    parser_ptr rule::operator &() {
        return make_logical_and_parser(parser(*this));
    }


    parser_ptr rule::operator !() {
        return make_logical_not_parser(parser(*this));
    }


    bool rule::parse(parse_context& pc) const {
        return m_parser->parse(pc);
    }


    rule* rule::addr() {
        return this;
    }


    parser_ptr parser(class rule& rule) {
        return std::make_shared<rule_reference>(rule.addr());
    }


} //namespace xparserlib
