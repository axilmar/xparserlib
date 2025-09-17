#ifndef XPARSERLIB_LOGICAL_NOT_PARSER_HPP
#define XPARSERLIB_LOGICAL_NOT_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that tests input with the help of another parser not negates its result.
     */
    class logical_not_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parser parser to parse.
         */
        logical_not_parser(const parser_ptr& parser);

        /**
         * Parses a parser; keeps the parse context state intact.
         * @param pc the parse context.
         * @return the opposite of whatever the parser returns.
         */
        bool parse(parse_context& pc) const override;

    private:
        const parser_ptr m_parser;
    };


    /**
     * Creates an logical not parser out of a parser.
     * @param parser parser to create an logical not parser from.
     * @return a parser parser.
     */
    parser_ptr make_logical_not_parser(const parser_ptr& parser);


} //namespace xparserlib


#endif //XPARSERLIB_LOGICAL_NOT_PARSER_HPP
