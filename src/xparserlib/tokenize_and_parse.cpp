#include <algorithm>
#include "xparserlib/tokenize_and_parse.hpp"


namespace xparserlib {


    class tapm {
    public:
        static void get_source_match(const matches_type& tokenizer_matches, const iterator_type& parser_input_begin, const match& parser_match, match& source_match) {
            source_match.m_type = parser_match.m_type;

            const match& begin_match = tokenizer_matches[parser_match.m_begin - parser_input_begin];

            source_match.m_begin = begin_match.m_begin;
            source_match.m_begin_line = begin_match.m_begin_line;
            source_match.m_begin_column = begin_match.m_begin_column;

            const match& end_match = tokenizer_matches[parser_match.m_end - 1 - parser_input_begin];
            source_match.m_end = end_match.m_end;
            source_match.m_end_line = end_match.m_end_line;
            source_match.m_end_column = end_match.m_end_column;

            get_source_matches(tokenizer_matches, parser_input_begin, parser_match.m_children, source_match.m_children);

        }

        static void get_source_matches(const matches_type& tokenizer_matches, const iterator_type& parser_input_begin, const matches_type& parser_matches, matches_type& source_matches) {
            source_matches.resize(parser_matches.size());
            for (size_t index = 0; index < parser_matches.size(); ++index) {
                const match& parser_match = parser_matches[index];
                match& source_match = source_matches[index];
                get_source_match(tokenizer_matches, parser_input_begin, parser_match, source_match);
            }
        }
    };


    bool tokenize_and_parse(string_type& input, rule& tokenizer_grammar, rule& parser_grammar, tokenize_and_parse_result& result) {
        //clear
        result = tokenize_and_parse_result();

        //tokenize
        parse_context tokenizer_parse_context(input);
        result.tokenization.success = tokenizer_grammar.parse(tokenizer_parse_context) && tokenizer_parse_context.ended();
        result.tokenization.matches = tokenizer_parse_context.matches();
        result.tokenization.position = tokenizer_parse_context.position();

        //parse
        result.parsing.input = result.tokenization.matches;
        parse_context parser_parse_context(result.parsing.input);
        result.parsing.success = parser_grammar.parse(parser_parse_context) && parser_parse_context.ended();
        result.parsing.token_matches = parser_parse_context.matches();
        result.parsing.token_position = parser_parse_context.position();
        tapm::get_source_matches(result.tokenization.matches, result.parsing.input.begin(), result.parsing.token_matches, result.parsing.matches);
        const size_t index = parser_parse_context.position() - result.parsing.input.begin();
        result.parsing.position = index < result.tokenization.matches.size() ? result.tokenization.matches[index].begin() : input.end();

        //complete the result
        result.success = result.tokenization.success && result.parsing.success;
        return result.success;
    }


} //namespace xparserlib
