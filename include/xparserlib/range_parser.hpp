#ifndef XPARSERLIB_RANGE_PARSER_HPP
#define XPARSERLIB_RANGE_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that parses a symbol within a range.
     */
    class range_parser : public parser {
    public:
        /**
         * The constructor.
         * @param min min value of range.
         * @param max max value of range.
         */
        range_parser(symbol_type min, symbol_type max);

        /**
         * Parses a symbol against a range.
         * @param pc the parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

    private:
        const symbol_type m_min;
        const symbol_type m_max;
    };


    /**
     * Creates a parser out of a range.
     * @param min min value of range.
     * @param max max value of range.
     * @return a range parser.
     */
    parser_ptr make_range_parser(symbol_type min, symbol_type max);


    /**
     * Creates a parser out of a range.
     * @param min min value of range.
     * @param max max value of range.
     * @return a range parser.
     */
    parser_ptr range(symbol_type min, symbol_type max);


} //namespace xparserlib


#endif //XPARSERLIB_RANGE_PARSER_HPP
