#ifndef XPARSERLIB_SYMBOL_PARSER_HPP
#define XPARSERLIB_SYMBOL_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A symbol parser parses a single symbol.
     */
    class symbol_parser : public parser {
    public:
        /**
         * The constructor.
         * @param symbol symbol to parse.
         */
        symbol_parser(symbol_type symbol);

        /**
         * Parses a single symbol.
         * @param pc the parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

    private:
        const symbol_type m_symbol;
    };


    /**
     * Creates a parser out of a symbol.
     * @param symbol symbol to create a symbol parser from.
     * @return a symbol parser.
     */
    parser_ptr parser(symbol_type symbol);


} //namespace xparserlib


#endif //XPARSERLIB_SYMBOL_PARSER_HPP
