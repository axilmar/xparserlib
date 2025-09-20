#include "xparserlib/bool_parser.hpp"


namespace xparserlib {


    bool_parser::bool_parser(bool v)
        : m_value(v)
    {
    }


    bool bool_parser::parse(parse_context& pc) const {
        return m_value;
    }


    parser_ptr parser(bool v) {
        return std::make_shared<bool_parser>(v);
    }


} //namespace xparserlib
