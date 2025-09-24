#include "xparserlib/choice_parser.hpp"
#include "xparserlib/symbol_parser.hpp"
#include "xparserlib/string_parser.hpp"
#include "xparserlib/rule.hpp"
#include "vector.hpp"


namespace xparserlib {


    choice_parser::choice_parser(const parsers_type& parsers)
        : m_parsers(parsers)
    {
    }


    bool choice_parser::parse(parse_context& pc) const {
        for (const parser_ptr& parser : m_parsers) {
            const auto start_state = pc.state();
            if (parser->parse(pc)) {
                return true;
            }
            pc.set_state(start_state);
        }
        return false;
    }


    const parsers_type& choice_parser::parsers() const {
        return m_parsers;
    }


    parser_ptr operator | (const parser_ptr& left, const parser_ptr& right) {
        choice_parser* l = dynamic_cast<choice_parser*>(left.get());
        choice_parser* r = dynamic_cast<choice_parser*>(right.get());
        if (l && r) {
            return std::make_shared<choice_parser>(l->parsers() + r->parsers());
        }
        if (l) {
            return std::make_shared<choice_parser>(l->parsers() + right);
        }
        if (r) {
            return std::make_shared<choice_parser>(left + r->parsers());
        }
        return std::make_shared<choice_parser>(parsers_type{ left, right });
    }


} //namespace xparserlib
