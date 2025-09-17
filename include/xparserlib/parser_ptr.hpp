#ifndef XPARSERLIB_PARSER_PTR_HPP
#define XPARSERLIB_PARSER_PTR_HPP


#include <memory>


namespace xparserlib {


    class parser;


    /**
     * Parser pointer type.
     */
    class parser_ptr : public std::shared_ptr<class parser> {
    public:
        using std::shared_ptr<class parser>::shared_ptr;

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


