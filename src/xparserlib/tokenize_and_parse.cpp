#include <algorithm>
#include "xparserlib/tokenize_and_parse.hpp"


namespace xparserlib {


    class tapm {
    public:
        static void get_source_match(const matches_type& tokenizer_matches, const iterator_type& parser_input_begin, const match& parser_match, match& source_match) {
            source_match.m_type = parser_match.m_type;
            source_match.m_begin = tokenizer_matches[parser_match.m_begin - parser_input_begin].m_begin;
            source_match.m_end = tokenizer_matches[parser_match.m_end - 1 - parser_input_begin].m_end;
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
        result.tokenization.errors = tokenizer_parse_context.errors();

        //parse
        result.parsing.input = result.tokenization.matches;
        parse_context parser_parse_context(result.parsing.input);
        result.parsing.success = parser_grammar.parse(parser_parse_context) && parser_parse_context.ended();
        result.parsing.matches = parser_parse_context.matches();
        tapm::get_source_matches(result.tokenization.matches, result.parsing.input.begin(), result.parsing.matches, result.parsing.source_matches);
        result.parsing.errors = parser_parse_context.errors();

        //complete the result
        result.success = result.tokenization.success && result.parsing.success;
        return result.success;
    }


} //namespace xparserlib
