#ifndef XPARSERLIB_CHOICE_PARSER_HPP
#define XPARSERLIB_CHOICE_PARSER_HPP


#include "rule.hpp"


namespace xparserlib {


    /**
     * A choice parser.
     * At least one of the internal parsers must parse successfully,
     * in order for the choice parser to parse successfully.
     */
    class choice_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parsers collection of parsers to use for parsing.
         */
        choice_parser(const parsers_type& parsers);

        /**
         * Parses all the internal parsers, in the order given in the constructor.
         * If one of them succeeds, the whole choice succeeds; otherwise, the parse context state
         * is set to the one when this function was entered.
         * @param pc parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

        const parsers_type& parsers() const;

    private:
        const parsers_type m_parsers;
    };


    /**
     * Creates a choice out of two parsers.
     * Choice parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a choice parser that contains parsers for the left and right operand.
     */
    parser_ptr operator | (const parser_ptr& left, const parser_ptr& right);


} //namespace xparserlib


#endif //XPARSERLIB_CHOICE_PARSER_HPP
