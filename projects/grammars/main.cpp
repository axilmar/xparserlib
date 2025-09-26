#include "ebnf.hpp"


using namespace xparserlib;


int main() {
    std::string file = load_file("test.ebnf");
    string_type input(file);
    tokenize_and_parse_result tapr;
    tokenize_and_parse(input, ebnf::tokenizer_grammar, ebnf::parser_grammar, tapr);
}
