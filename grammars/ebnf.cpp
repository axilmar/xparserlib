#include "ebnf.hpp"


using namespace xparserlib;


namespace xparserlib::ebnf {


    //ebnf grammar as defined in https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form


    /**** tokenizer ****/


    static rule space = ' ';
    static rule whitespace = range('\0', 32) ;


    static rule comment
        = "(*" >> *(any() - "*)") >> "*)"
        ;


    static rule letter
        = range('a', 'z') | range('A', 'Z')
        ;


    static rule digit
        = range('0', '9')
        ;


    static rule identifier
        = ((letter | '_') >> *(letter | digit | '_' | '-'))->*TOKEN_IDENTIFIER
        ;


    static rule char_terminal
        = ('\'' >> any() >> '\'')->*TOKEN_CHAR_TERMINAL
        ;


    static rule terminal_expr
        = '\'' >> *(any() - '\'') >> '\''
        | '\"' >> *(any() - '\"') >> '\"'
        ;


    static rule terminal
        = terminal_expr->*TOKEN_TERMINAL
        ;


    static rule regex_terminal
        = ('/' >> regex_grammar('/') >> '/')->*TOKEN_REGEX_TERMINAL
        ;


    static rule assignment_operator
        = (parser("::=") | ":=" | ':' | '=')->*TOKEN_ASSIGNMENT_OPERATOR
        ;


    static rule range_operator
        = parser("..")->*TOKEN_RANGE_OPERATOR
        ;


    static rule group_start = parser('(')->*TOKEN_GROUP_START;
    static rule group_end = parser(')')->*TOKEN_GROUP_END;


    static rule optional_start = parser('[')->*TOKEN_OPTIONAL_START;
    static rule optional_end = parser(']')->*TOKEN_OPTIONAL_END;


    static rule repetition_start = parser('{')->*TOKEN_REPETITION_START;
    static rule repetition_end = parser('}')->*TOKEN_REPETITION_END;


    static rule optional_operator = parser('?')->*TOKEN_OPTIONAL_OPERATOR;
    static rule loop_0_operator = parser('*')->*TOKEN_LOOP_0_OPERATOR;
    static rule loop_1_operator = parser('+')->*TOKEN_LOOP_1_OPERATOR;
    static rule exclusion_operator = parser('-')->*TOKEN_EXCLUSION_OPERATOR;
    static rule concatenation_operator = parser(',')->*TOKEN_CONCATENATION_OPERATOR;
    static rule alternation_operator = parser('|')->*TOKEN_ALTERNATION_OPERATOR;


    static rule newline
        = parser("\r\n")
        | "\n\r"
        | '\n'
        | '\r'
        ;


    static rule terminator =
        ((newline >> newline) | parser(';') | '.')->*TOKEN_TERMINATOR
        ;


    static rule token
        = identifier
        | char_terminal
        | terminal
        | regex_terminal
        | assignment_operator
        | range_operator
        | group_start
        | group_end
        | optional_start
        | optional_end
        | repetition_start
        | repetition_end
        | optional_operator
        | loop_0_operator
        | loop_1_operator
        | exclusion_operator
        | concatenation_operator
        | alternation_operator
        | terminator
        ;


    rule tokenizer_grammar
        = *(space | comment | token | whitespace | error(ERROR_INVALID_CHARACTERS) | skip(any()))
        ;


    /**** parser ****/


    extern rule alternation;


    static rule identifier_term
        = parser(TOKEN_IDENTIFIER)->*AST_IDENTIFIER;


    static rule range_char
        = parser(TOKEN_CHAR_TERMINAL)->*AST_CHAR_TERMINAL
        ;


    static rule range_term
        = (range_char >> TOKEN_RANGE_OPERATOR >> range_char)->*AST_RANGE_TERMINAL
        ;

    static rule group_term
        = TOKEN_GROUP_START >> alternation >> TOKEN_GROUP_END
        ;

    static rule optional_term
        = (TOKEN_OPTIONAL_START >> alternation >> TOKEN_OPTIONAL_END)->*AST_OPTIONAL
        ;

    static rule loop_0_term
        = (TOKEN_REPETITION_START >> alternation >> TOKEN_REPETITION_END)->*AST_LOOP_0
        ;

    static rule char_term
        = parser(TOKEN_CHAR_TERMINAL)->*AST_TERMINAL
        ;

    static rule string_term
        = parser(TOKEN_TERMINAL)->*AST_TERMINAL
        ;

    static rule regex_term
        = parser(TOKEN_REGEX_TERMINAL)->*AST_REGEX_TERMINAL
        ;


    static rule term
        = group_term
        | optional_term
        | loop_0_term
        | identifier_term
        | range_term
        | char_term
        | string_term
        | regex_term
        ;


    static rule factor
        = (term >> TOKEN_OPTIONAL_OPERATOR)->*AST_OPTIONAL
        | (term >> TOKEN_LOOP_0_OPERATOR)->*AST_LOOP_0
        | (term >> TOKEN_LOOP_1_OPERATOR)->*AST_LOOP_1
        | (term >> TOKEN_EXCLUSION_OPERATOR >> term)->*AST_EXCLUSION
        | term
        ;


    static rule factor_or_rule_terminator
        = factor
        | &parser(TOKEN_TERMINATOR)
        ;


    static rule first_concatenation
        = factor >> -parser(TOKEN_CONCATENATION_OPERATOR) >> factor
        ;


    static rule next_concatenation
        = parser(TOKEN_CONCATENATION_OPERATOR) >> factor
        | factor_or_rule_terminator
        ;


    static rule concatenation
        = (first_concatenation >> *next_concatenation)->*AST_CONCATENATION
        | factor
        | error(ERROR_EXPECTED_TERMINAL_OR_OPERATOR)
        | skip(any())
        ;


    static rule alternation
        = (concatenation >> +(TOKEN_ALTERNATION_OPERATOR >> concatenation))->*AST_ALTERNATION
        | concatenation
        ;


    static rule production_rule_name
        = identifier_term
        | error(ERROR_EXPECTED_IDENTIFIER)
        | skip(any())
        ;


    static rule production_rule_assignment_operator
        = TOKEN_ASSIGNMENT_OPERATOR
        | error(ERROR_EXPECTED_ASSIGNMENT_OPERATOR)
        | skip(any())
        ;


    static rule production_rule_terminator
        = +parser(TOKEN_TERMINATOR)
        | error(ERROR_EXPECTED_TERMINATOR)
        | skip(any())
        ;


    static rule production_rule
        = (production_rule_name >> production_rule_assignment_operator >> alternation >> production_rule_terminator)->*AST_RULE
        ;


    rule parser_grammar 
        = *production_rule;


} //namespace xparserlib::ebnf
