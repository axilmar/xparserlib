#ifndef XPARSERLIB_SEQUENCE_PARSER_HPP
#define XPARSERLIB_SEQUENCE_PARSER_HPP


#include "rule.hpp"


namespace xparserlib {


    /**
     * A sequence parser.
     * All the internal parsers must parse successfully for a sequence to parse successfully.
     * If one of the internal parsers fails to parse, then the whole sequence fails
     * and the parse context is rewinded to the state before the sequence parsing.
     */
    class sequence_parser : public parser {
    public:
        /**
         * The constructor.
         * @param parsers collection of parsers to use for parsing.
         */
        sequence_parser(const parsers_type& parsers);

        /**
         * Parses all the internal parsers, in the order given in the constructor.
         * If one of them fails, the whole sequence fails and the parse context state
         * is set to the one when this function was entered.
         * @param pc parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

        const parsers_type& parsers() const;

    private:
        const parsers_type m_parsers;
    };


    /* left: parser_ptr */


    /**
     * Creates a sequence out of two parsers.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains parsers for the left and right operand.
     */
    parser_ptr operator >> (const parser_ptr& left, const parser_ptr& right);


    /**
     * Creates a sequence out of a parser and a symbol.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (const parser_ptr& left, symbol_type right);


    /**
     * Creates a sequence out of a parser and a string.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (const parser_ptr& left, const string_type& right);


    /**
     * Creates a sequence out of a parser and a rule.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (const parser_ptr& left, rule& right);


    /* left: symbol_type */


    /**
     * Creates a sequence out of a symbol and a parser.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains parsers for the left and right operand.
     */
    parser_ptr operator >> (symbol_type left, const parser_ptr& right);


    /**
     * Creates a sequence out of a symbol and a string.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (symbol_type left, const string_type& right);


    /**
     * Creates a sequence out of a symbol and a rule.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (symbol_type left, rule& right);


    /* left: string_type */


    /**
     * Creates a sequence out of a string and a parser.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains parsers for the left and right operand.
     */
    parser_ptr operator >> (const string_type& left, const parser_ptr& right);


    /**
     * Creates a sequence out of a string and a symbol.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (const string_type& left, symbol_type right);


    /**
     * Creates a sequence out of a string and a string.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (const string_type& left, const string_type& right);


    /**
     * Creates a sequence out of a string and a rule.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (const string_type& left, rule& right);


    /* left: rule */


    /**
     * Creates a sequence out of a rule and a parser.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains parsers for the left and right operand.
     */
    parser_ptr operator >> (rule& left, const parser_ptr& right);


    /**
     * Creates a sequence out of a rule and a symbol.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (rule& left, symbol_type right);


    /**
     * Creates a sequence out of a rule and a string.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (rule& left, const string_type& right);


    /**
     * Creates a sequence out of a rule and a rule.
     * Sequence parsers are flattened.
     * @param left the left operand.
     * @param right the right operand.
     * @return a sequence parser that contains the left and right parsers.
     */
    parser_ptr operator >> (rule& left, rule& right);


} //namespace xparserlib


#endif //XPARSERLIB_SEQUENCE_PARSER_HPP
