#ifndef XPARSERLIB_OPTIONAL_PARSER_HPP
#define XPARSERLIB_OPTIONAL_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that makes another parser optional.
     */
    class optional_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parser parser to parse.
         */
        optional_parser(const parser_ptr& parser);

        /**
         * Parses a parser optionally.
         * @param pc the parse context.
         * @return always true.
         */
        bool parse(parse_context& pc) const override;

    private:
        const parser_ptr m_parser;
    };


    /**
     * Creates an optional parser out of a parser.
     * @param parser parser to create an optional parser from.
     * @return a parser parser.
     */
    parser_ptr make_optional_parser(const parser_ptr& parser);


} //namespace xparserlib


#endif //XPARSERLIB_OPTIONAL_PARSER_HPP
