#include <cassert>
#include "xparserlib/range_parser.hpp"


namespace xparserlib {


    range_parser::range_parser(symbol_type min, symbol_type max)
        : m_min(min)
        , m_max(max)
    {
        assert(min <= max);
    }


    bool range_parser::parse(parse_context& pc) const {
        if (pc.valid()) {
            const symbol_type token = *pc.position();
            if (token >= m_min && token <= m_max) {
                pc.increment_position();
                return true;
            }
        }
        return false;
    }


    parser_ptr range(symbol_type min, symbol_type max) {
        return std::make_shared<range_parser>(min, max);
    }


} //namespace xparserlib
