#ifndef XPARSERLIB_SKIP_PARSER_HPP
#define XPARSERLIB_SKIP_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that skips input until a match is found.
     */
    class skip_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parser parser to use for testing.
         */
        skip_parser(const parser_ptr& parser);

        /**
         * Iterates the input until the internal parser succeeds in parsing.
         * @param pc the parse context.
         * @return true if the internal parser returns true, false if input is exhausted.
         */
        bool parse(parse_context& pc) const override;

    private:
        const parser_ptr m_parser;
        const parser_ptr m_skip_parser;
    };


    /**
     * Creates a skip parser out of a parser.
     * @param parser parser to create a skip parser from.
     * @return a skip parser.
     */
    parser_ptr skip(const parser_ptr& parser);


} //namespace xparserlib


#endif //XPARSERLIB_SKIP_PARSER_HPP
