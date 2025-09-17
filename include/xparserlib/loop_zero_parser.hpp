#ifndef XPARSERLIB_LOOP_ZERO_PARSER_HPP
#define XPARSERLIB_LOOP_ZERO_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that parses another parser zero or more times.
     */
    class loop_zero_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parser parser to parse.
         */
        loop_zero_parser(const parser_ptr& parser);

        /**
         * Parses a parser.
         * @param pc the parse context.
         * @return always true.
         */
        bool parse(parse_context& pc) const override;

    private:
        const parser_ptr m_parser;
    };


    /**
     * Creates a loop zero parser out of a parser.
     * @param parser parser to create a loop zero parser from.
     * @return a parser parser.
     */
    parser_ptr make_loop_zero_parser(const parser_ptr& parser);


} //namespace xparserlib


#endif //XPARSERLIB_LOOP_ZERO_PARSER_HPP
