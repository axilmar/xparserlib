#include "xparserlib/any_parser.hpp"


namespace xparserlib {


    bool any_parser::parse(parse_context& pc) const {
        if (pc.valid()) {
            pc.increment_position();
            return true;
        }
        return false;
    }


    parser_ptr any() {
        return std::make_shared<any_parser>();
    }


} //namespace xparserlib
