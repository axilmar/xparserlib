#include "xparserlib/set_parser.hpp"


namespace xparserlib {


    set_parser::set_parser(const string_type& set)
        : m_set(set)
    {
    }


    bool set_parser::parse(parse_context& pc) const {
        if (pc.valid()) {
            const symbol_type token = *pc.position();
            for (const symbol_type& symbol : m_set) {
                if (symbol == token) {
                    pc.increment_position();
                    return true;
                }
            }
        }
        return false;
    }


    parser_ptr set(const string_type& set) {
        return std::make_shared<set_parser>(set);
    }


} //namespace xparserlib
