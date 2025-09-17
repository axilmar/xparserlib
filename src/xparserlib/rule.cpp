#include "xparserlib/rule.hpp"
#include "xparserlib/symbol_parser.hpp"
#include "xparserlib/string_parser.hpp"
#include "xparserlib/loop_zero_parser.hpp"
#include "xparserlib/loop_one_parser.hpp"
#include "xparserlib/optional_parser.hpp"
#include "xparserlib/logical_and_parser.hpp"
#include "xparserlib/logical_not_parser.hpp"


namespace xparserlib {


    class rule_parser : public parser {
    public:
        rule_parser(rule& r) : m_rule(r) {}

        bool parse(parse_context& pc) const override {
            return m_rule.parse(pc);
        }

    private:
        rule& m_rule;
    };


    rule::rule(const parser_ptr& parser)
        : m_parser(parser)
    {
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


    parser_ptr make_rule_parser(class rule& rule) {
        return std::make_shared<rule_parser>(rule);
    }


    parser_ptr parser(class rule& rule) {
        return make_rule_parser(rule);
    }


} //namespace xparserlib
