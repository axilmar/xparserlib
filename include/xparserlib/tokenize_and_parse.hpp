#ifndef XPARSERLIB_TOKENIZE_AND_PARSE_HPP
#define XPARSERLIB_TOKENIZE_AND_PARSE_HPP


#include <utility>
#include "match.hpp"
#include "rule.hpp"


namespace xparserlib {


    /**
     * The result of the tokenization and parsing process.
     */
    struct tokenize_and_parse_result {
        /**
         * The tokenization result.
         */
        struct tokenization {
            /**
             * True if tokenization succeeded, false if failed.
             */
            bool success;

            /**
             * The matches identified during the tokenization process.
             */
            matches_type matches;

            /**
             * Position the tokenizer stopped at.
             */
            iterator_type position;
        } tokenization;

        struct parsing {
            /**
             * The input used in parsing is the result of the tokenization process.
             * For each position in the tokenization matches container,
             * a corresponding entry is created in this container.
             */
            string_type input;

            /**
             * True if parsing succeeded, false if failed.
             */
            bool success;

            /**
             * The matches over the tokenizer output, identified during the parsing process.
             */
            matches_type token_matches;

            /**
             * Position the parser stopped at.
             */
            iterator_type token_position;

            /**
             * The matches over the source input, identified during the parsing process.
             */
            matches_type matches;

            /**
             * Source position the parser stopped at.
             */
            iterator_type position;
        } parsing;

        /**
         * True if tokenization and parsing succeeded, false otherwise.
         */
        bool success;
    };


    /**
     * Tokenizes an input, then uses the created token array as input to a parser.
     * @param input input to parse.
     * @param tokenizer_grammar the tokenizer grammar.
     * @param parser_grammar the parser grammar.
     * @param result the result of the process.
     * @return true if the whole process succeeded, false otherwise.
     */
    bool tokenize_and_parse(string_type& input, rule& tokenizer_grammar, rule& parser_grammar, tokenize_and_parse_result& result);


} //namespace xparserlib


#endif //XPARSERLIB_TOKENIZE_AND_PARSE_HPP
