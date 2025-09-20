#include "xparserlib/end_parser.hpp"


namespace xparserlib {


    bool end_parser::parse(parse_context& pc) const {
        return !pc.valid();
    }


    parser_ptr end() {
        return std::make_shared<end_parser>();
    }


} //namespace xparserlib
