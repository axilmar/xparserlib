#include "xparserlib/loop_zero_parser.hpp"
#include "xparserlib/loop_one_parser.hpp"
#include "xparserlib/optional_parser.hpp"
#include "xparserlib/logical_and_parser.hpp"
#include "xparserlib/logical_not_parser.hpp"


namespace xparserlib {


    parser_ptr parser_ptr::operator *() {
        return make_loop_zero_parser(*this);
    }


    parser_ptr parser_ptr::operator +() {
        return make_loop_one_parser(*this);
    }


    parser_ptr parser_ptr::operator -() {
        return make_optional_parser(*this);
    }


    parser_ptr parser_ptr::operator &() {
        return make_logical_and_parser(*this);
    }


    parser_ptr parser_ptr::operator !() {
        return make_logical_not_parser(*this);
    }


} //namespace xparserlib
