#ifndef XPARSERLIB_ERROR_PARSER_HPP
#define XPARSERLIB_ERROR_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that adds an error.
     */
    class error_parser : public parser {
    public:
        /**
         * The constructor.
         * @param type error type.
         */
        error_parser(error_type type);

        /**
         * Adds an error to the parse context, if the position is valid.
         * @param pc the parse context.
         * @return true if pc position is valid, false otherwise.
         */
        bool parse(parse_context& pc) const override;

    private:
        const error_type m_type;
    };


    /**
     * Creates a error parser.
     * @param type error type.
     * @return a error parser.
     */
    parser_ptr error(error_type type);


} //namespace xparserlib


#endif //XPARSERLIB_ERROR_PARSER_HPP
