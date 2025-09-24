#include "xparserlib/sequence_parser.hpp"
#include "xparserlib/symbol_parser.hpp"
#include "xparserlib/string_parser.hpp"
#include "xparserlib/rule.hpp"
#include "vector.hpp"


namespace xparserlib {


    sequence_parser::sequence_parser(const parsers_type& parsers)
        : m_parsers(parsers)
    {
    }


    bool sequence_parser::parse(parse_context& pc) const {
        const auto start_state = pc.state();
        for (const parser_ptr& parser : m_parsers) {
            if (!parser->parse(pc)) {
                pc.set_state(start_state);
                return false;
            }
        }
        return true;
    }


    const parsers_type& sequence_parser::parsers() const {
        return m_parsers;
    }


    parser_ptr operator >> (const parser_ptr& left, const parser_ptr& right) {
        sequence_parser* l = dynamic_cast<sequence_parser*>(left.get());
        sequence_parser* r = dynamic_cast<sequence_parser*>(right.get());
        if (l && r) {
            return std::make_shared<sequence_parser>(l->parsers() + r->parsers());
        }
        if (l) {
            return std::make_shared<sequence_parser>(l->parsers() + right);
        }
        if (r) {
            return std::make_shared<sequence_parser>(left + r->parsers());
        }
        return std::make_shared<sequence_parser>(parsers_type{left, right});
    }


    parser_ptr operator - (const parser_ptr& left, const parser_ptr& right) {
        return !right >> left;
    }


} //namespace xparserlib
