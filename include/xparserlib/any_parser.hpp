#ifndef XPARSERLIB_ANY_PARSER_HPP
#define XPARSERLIB_ANY_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * Accepts any symbol.
     */
    class any_parser : public parser {
    public:
        /**
         * Accepts any symbol.
         * @param pc parse context.
         * @return true if the end of the input has not been reached, false otherwise.
         */
        bool parse(parse_context& pc) const override;
    };


    /**
     * Creates an any parser.
     * @return an any parser instance.
     */
    parser_ptr any();


} //namespace xparserlib


#endif //XPARSERLIB_ANY_PARSER_HPP
