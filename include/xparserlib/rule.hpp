#ifndef XPARSERLIB_RULE_HPP
#define XPARSERLIB_RULE_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * Represents a production rule.
     * Rules are managed via references, and therefore can be recursive.
     */
    class rule {
    public:
        /**
         * The constructor.
         * @param parser parser to use for parsing.
         */
        rule(const parser_ptr& parser = nullptr);

        /**
         * Creates a zero or more times loop out of this rule.
         * @return a zero or more times loop out of this rule.
         */
        parser_ptr operator *();

        /**
         * Creates a one or more times loop out of this rule.
         * @return a one or more times loop out of this rule.
         */
        parser_ptr operator +();

        /**
         * Makes this rule optional.
         * @return an optional parser for this rule.
         */
        parser_ptr operator -();

        /**
         * Creates a logical and parser from this rule.
         * @return a logical and parser from this rule.
         */
        parser_ptr operator &();

        /**
         * Creates a logical not parser from this rule.
         * @return a logical not parser from this rule.
         */
        parser_ptr operator !();

        /**
         * Invokes the internal parser.
         * @param pc parse context.
         * @return whatever the internal parser returns.
         */
        bool parse(parse_context& pc) const;

    private:
        parser_ptr m_parser;
    };


    /**
     * Creates a parser for a rule.
     * @param rule rule to create a parser from.
     */
    parser_ptr make_rule_parser(class rule& rule);
   
    
    /**
     * Creates a parser for a rule.
     * @param rule rule to create a parser from.
     */
    parser_ptr parser(class rule& rule);


} //namespace xparserlib


#endif //XPARSERLIB_RULE_HPP
