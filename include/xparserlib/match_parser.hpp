#ifndef XPARSERLIB_MATCH_PARSER_HPP
#define XPARSERLIB_MATCH_PARSER_HPP


#include "rule.hpp"


namespace xparserlib {


    /**
     * A parser that parses another parser; if parsing succeeds, a match is added to the parse context.
     */
    class match_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parser parser to parse.
         * @param type match type.
         */
        match_parser(const parser_ptr& parser, match_type type);

        /**
         * Parses a parser.
         * @param pc the parse context.
         * @return always true.
         */
        bool parse(parse_context& pc) const override;

        const parser_ptr& parser() const;
        match_type type() const;

    private:
        const parser_ptr m_parser;
        const match_type m_type;
    };


    /**
     * Creates a match parser out of a parser and a match type.
     * @param parser parser to create a match parser from.
     * @param type match type.
     * @return a match parser.
     */
    parser_ptr operator ->* (const parser_ptr& parser, match_type type);


    /**
     * Creates a match parser out of a string and a match type.
     * @param string string to create a match parser from.
     * @param type match type.
     * @return a match parser.
     */
    parser_ptr operator ->* (const string_type& string, match_type type);


    /**
     * Creates a match parser out of a rule and a match type.
     * @param rule rule to create a match parser from.
     * @param type match type.
     * @return a match parser.
     */
    parser_ptr operator ->* (class rule& rule, match_type type);


} //namespace xparserlib


#endif //XPARSERLIB_MATCH_PARSER_HPP
