#ifndef XPARSERLIB_TOKENIZE_AND_PARSE_HPP
#define XPARSERLIB_TOKENIZE_AND_PARSE_HPP


#include <utility>
#include "match.hpp"
#include "error.hpp"
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
             * True if tokenization failed, false if there were one or more errors.
             */
            bool success;

            /**
             * The matches identified during the tokenization process.
             * Match iterators point to the source.
             */
            matches_type matches;

            /**
             * The errors created during the tokenization process.
             */
            errors_type errors;

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
             * True if parsing failed, false if there were one or more errors.
             */
            bool success;

            /**
             * The matches over the parser input (i.e. the tokenizer matches converted to a string type), 
             * identified during the parsing process.
             * Match iterators point to the parser input.
             */
            matches_type matches;

            /**
             * The errors created during the parsing process.
             */
            errors_type errors;

            /**
             * Position the parser stopped at.
             */
            iterator_type position;

            /**
             * The matches over the source input, identified during the parsing process.
             * Match iterators point to the source, rather than to the the parser input.
             */
            matches_type source_matches;

            /**
             * The errors over the source input.
             * Just like source matches, the source errors point to the source, 
             * rather than to the parser input.
             */
            errors_type source_errors;

            /**
             * Source position the parser stopped at.
             */
            iterator_type source_position;
        } parsing;

        /**
         * True if tokenization and parsing failed, false if there were one or more errors.
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
