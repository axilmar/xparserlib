#ifndef XPARSERLIB_PARSER_PTR_HPP
#define XPARSERLIB_PARSER_PTR_HPP


#include <memory>
#include <initializer_list>
#include "string_type.hpp"


namespace xparserlib {


    class parser;


    /**
     * Parser pointer type.
     */
    class parser_ptr : public std::shared_ptr<class parser> {
    public:
        using std::shared_ptr<class parser>::shared_ptr;

        /**
         * Symbol parser constructor.
         * @param symbol symbol.
         */
        parser_ptr(symbol_type symbol);

        /**
         * String parser constructor.
         * @param string string.
         */
        parser_ptr(const char* string);

        /**
         * String parser constructor.
         * @param string string.
         */
        parser_ptr(const wchar_t* string);

        /**
         * String parser constructor.
         * @param string string.
         */
        parser_ptr(const string_type& string);

        /**
         * String parser constructor.
         * @param string string.
         */
        parser_ptr(const std::initializer_list<symbol_type>& string);

        /**
         * Boolean parser constructor.
         * @param value boolean value.
         */
        parser_ptr(bool value);

        /**
         * Creates a zero or more times loop out of this parser.
         * @return a zero or more times loop out of this parser.
         */
        parser_ptr operator *();

        /**
         * Creates a one or more times loop out of this parser.
         * @return a one or more times loop out of this parser.
         */
        parser_ptr operator +();

        /**
         * Makes this parser optional.
         * @return an optional parser for this parser.
         */
        parser_ptr operator -();

        /**
         * Creates a logical and parser from this parser.
         * @return a logical and parser from this parser.
         */
        parser_ptr operator &();

        /**
         * Creates a logical not parser from this parser.
         * @return a logical not parser from this parser.
         */
        parser_ptr operator !();
    };


} //namespace xparserlib


#endif //XPARSERLIB_PARSER_PTR_HPP


