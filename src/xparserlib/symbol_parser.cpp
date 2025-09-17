#include "xparserlib/symbol_parser.hpp"


namespace xparserlib {


    symbol_parser::symbol_parser(symbol_type symbol)
        : m_symbol(symbol)
    {
    }


    bool symbol_parser::parse(parse_context& pc) const {
        if (pc.valid() && *pc.position() == m_symbol) {
            pc.increment_position();
            return true;
        }
        return false;
    }


    parser_ptr make_symbol_parser(symbol_type symbol) {
        return std::make_shared<symbol_parser>(symbol);
    }


    parser_ptr symbol(symbol_type symbol) {
        return make_symbol_parser(symbol);
    }


    parser_ptr parser(symbol_type symbol) {
        return make_symbol_parser(symbol);
    }


} //namespace xparserlib
