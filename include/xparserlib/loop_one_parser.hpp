#ifndef XPARSERLIB_LOOP_ONE_PARSER_HPP
#define XPARSERLIB_LOOP_ONE_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that parses another parser one or more times.
     */
    class loop_one_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parser parser to parse.
         */
        loop_one_parser(const parser_ptr& parser);

        /**
         * Invokes a parser.
         * @param pc the parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

    private:
        const parser_ptr m_parser;
    };


    /**
     * Creates a loop one parser out of a parser.
     * @param parser parser to create a loop one parser from.
     * @return a parser parser.
     */
    parser_ptr make_loop_one_parser(const parser_ptr& parser);


} //namespace xparserlib


#endif //XPARSERLIB_LOOP_ONE_PARSER_HPP
