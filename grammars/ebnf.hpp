#ifndef XPARSERLIB_EBNF_HPP
#define XPARSERLIB_EBNF_HPP


#include "xparserlib.hpp"


namespace xparserlib::ebnf {


    enum TOKEN_TYPE {
        TOKEN_IDENTIFIER = 0,
        TOKEN_CHAR_TERMINAL = 1,
        TOKEN_STRING_TERMINAL = 2,
        TOKEN_REGEX_TERMINAL = 3,
        TOKEN_GROUP_START = 4,
        TOKEN_GROUP_END = 5,
        TOKEN_OPTIONAL_START = 6,
        TOKEN_OPTIONAL_END = 7,
        TOKEN_REPETITION_START = 8,
        TOKEN_REPETITION_END = 9,
        TOKEN_OPTIONAL_OPERATOR = 10,
        TOKEN_LOOP_0_OPERATOR = 11,
        TOKEN_LOOP_1_OPERATOR = 12,
        TOKEN_EXCLUSION_OPERATOR = 13,
        TOKEN_CONCATENATION_OPERATOR = 14,
        TOKEN_ALTERNATION_OPERATOR = 15,
        TOKEN_ASSIGNMENT_OPERATOR = 16,
        TOKEN_RANGE_OPERATOR = 17,
        TOKEN_TERMINATOR = 18
    };


    extern rule tokenizer_grammar;


    enum AST_TYPE {
        AST_IDENTIFIER = 0,
        AST_STRING_TERMINAL = 1,
        AST_REGEX_TERMINAL = 2,
        AST_RANGE_TERMINAL = 3,
        AST_CHAR_TERMINAL = 4,
        AST_OPTIONAL = 5,
        AST_LOOP_0 = 6,
        AST_LOOP_1 = 7,
        AST_EXCLUSION = 8,
        AST_CONCATENATION = 9,
        AST_ALTERNATION = 10,
        AST_RULE = 11
    };


    extern rule parser_grammar;


} //namespace xparserlib::ebnf


#endif //XPARSERLIB_EBNF_HPP
