#ifndef XPARSERLIB_BOOL_PARSER_HPP
#define XPARSERLIB_BOOL_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A boolean parser.
     */
    class bool_parser : public parser {
    public:
        /**
         * The constructor.
         * @param v the boolean value to return as the result of parsing.
         */
        bool_parser(bool v);

        /**
         * Returns the boolean value.
         * @param pc the parse context.
         * @return the boolean value.
         */
        bool parse(parse_context& pc) const override;

    private:
        const bool m_value;
    };


    /**
     * Creates a boolean parser.
     * @param value boolean value.
     * @return a boolean parser.
     */
    parser_ptr parser(bool value);


} //namespace xparserlib


#endif //XPARSERLIB_BOOL_PARSER_HPP
