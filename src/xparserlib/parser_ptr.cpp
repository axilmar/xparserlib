#include "xparserlib/symbol_parser.hpp"
#include "xparserlib/string_parser.hpp"
#include "xparserlib/loop_zero_parser.hpp"
#include "xparserlib/loop_one_parser.hpp"
#include "xparserlib/optional_parser.hpp"
#include "xparserlib/logical_and_parser.hpp"
#include "xparserlib/logical_not_parser.hpp"
#include "xparserlib/bool_parser.hpp"


namespace xparserlib {


    parser_ptr::parser_ptr(symbol_type symbol)
        : std::shared_ptr<class parser>(parser(symbol))
    {
    }


    parser_ptr::parser_ptr(const char* string)
        : std::shared_ptr<class parser>(parser(string))
    {
    }


    parser_ptr::parser_ptr(const wchar_t* string)
        : std::shared_ptr<class parser>(parser(string))
    {
    }


    parser_ptr::parser_ptr(const string_type& string)
        : std::shared_ptr<class parser>(parser(string))
    {
    }


    parser_ptr::parser_ptr(const std::initializer_list<symbol_type>& string)
        : std::shared_ptr<class parser>(parser(string))
    {
    }


    parser_ptr::parser_ptr(bool value)
        : std::shared_ptr<class parser>(parser(value))
    {
    }


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
