#ifndef XPARSERLIB_STRING_PARSER_HPP
#define XPARSERLIB_STRING_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A string parser parses a string.
     */
    class string_parser : public parser {
    public:
        /**
         * The constructor.
         * @param string string to parse.
         */
        string_parser(const string_type& string);

        /**
         * Parses a string.
         * @param pc the parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

    private:
        const string_type m_string;
    };


    /**
     * Creates a parser out of a string.
     * @param string string to create a string parser from.
     * @return a string parser.
     */
    parser_ptr parser(const string_type& string);


} //namespace xparserlib


#endif //XPARSERLIB_STRING_PARSER_HPP
