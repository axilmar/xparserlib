#include "xparserlib/error_parser.hpp"


namespace xparserlib {


    error_parser::error_parser(error_type type)
        : m_type(type)
    {
    }


    bool error_parser::parse(parse_context& pc) const {
        if (pc.valid()) {
            pc.add_error(m_type, pc.position());
        }
        return false;
    }


    parser_ptr error(error_type type) {
        return std::make_shared<error_parser>(type);
    }


} //namespace xparserlib
