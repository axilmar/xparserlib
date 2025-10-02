#ifndef XPARSERLIB_NEWLINE_PARSER_HPP
#define XPARSERLIB_NEWLINE_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * Creates a parser that increments the parse context's line
     * when another parser parses successfully.
     */
    class newline_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parser the parser to use.
         */
        newline_parser(const parser_ptr& parser);

        /**
         * If the internal parser parses successfully,
         * then it increments the line of the parse context.
         * @param pc the parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

    private:
        const parser_ptr m_parser;
    };


    /**
     * Creates a newline parser.
     * @param parser the parser to use.
     * @return the newline parser.
     */
    parser_ptr newline(const parser_ptr& parser);


} //namespace xparserlib


#endif //XPARSERLIB_NEWLINE_PARSER_HPP
