#ifndef XPARSERLIB_END_PARSER_HPP
#define XPARSERLIB_END_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that succeeds if the input is exhausted.
     */
    class end_parser : public parser {
    public:
        /**
         * Succeeds if the input is exhausted.
         * @param pc the parse context.
         * @return true if there are no more symbols to parse, false otherwise.
         */
        bool parse(parse_context& pc) const override;
    };


    /**
     * Creates an end parser.
     * @return an end parser.
     */
    parser_ptr end();


} //namespace xparserlib


#endif //XPARSERLIB_END_PARSER_HPP
