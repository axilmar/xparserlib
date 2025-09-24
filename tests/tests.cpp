#include <cassert>
#include <iostream>
#include <sstream>
#include "xparserlib.hpp"


using namespace xparserlib;


static void test_symbol_parser() {
    {
        parser_ptr grammar = parser('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = parser('a');
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_string_parser() {
    {
        parser_ptr grammar = parser("abc");
        string_type input = "abc";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = parser("abc");
        string_type input = "abd";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_set_parser() {
    {
        parser_ptr grammar = set("abc");
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = set("abc");
        string_type input = "d";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_range_parser() {
    {
        parser_ptr grammar = range('0', '9');
        string_type input = "5";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = range('0', '9');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_loop_zero_parser() {
    {
        parser_ptr grammar = *parser('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = *parser('a');
        string_type input = "aa";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = *parser('a');
        string_type input = "aaa";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = *parser('a');
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.begin());
    }

    {
        parser_ptr grammar = *parser('a');
        string_type input = "aab";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end() - 1);
    }
}


static void test_loop_one_parser() {
    {
        parser_ptr grammar = +parser('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = +parser('a');
        string_type input = "aa";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = +parser('a');
        string_type input = "aaa";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = +parser('a');
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }

    {
        parser_ptr grammar = +parser('a');
        string_type input = "aab";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end() - 1);
    }
}


static void test_optional_parser() {
    {
        parser_ptr grammar = -parser('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = -parser('a');
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.begin());
    }
}


static void test_sequence_parser() {
    {
        parser_ptr grammar = parser('a') >> 'b' >> "xy";
        string_type input = "abxy";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = parser('a') >> 'b' >> "xy";
        string_type input = "ab1y";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_choice_parser() {
    {
        parser_ptr grammar = parser('a') | 'b' | "xy";
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = parser('a') | 'b' | "xy";
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = parser('a') | 'b' | "xy";
        string_type input = "xy";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = parser('a') | 'b' | "xy";
        string_type input = "1";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_rule() {
    {
        rule grammar = parser('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar.parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        rule grammar = parser('a');
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar.parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }

    {
        rule a = 'a';
        rule b = 'b';
        rule grammar = a >> b >> 'c';
        string_type input = "abc";
        parse_context pc(input);
        const bool result = grammar.parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        rule a = 'a';
        rule b = 'b';
        rule c = 'c';
        rule grammar = a | b | 'c';
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar.parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }
}


static void test_match() {
    {
        parser_ptr grammar = (parser('a') ->* 1) >> parser('b') ->* 2;
        string_type input = "ab";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
        assert(pc.matches().size() == 2);
        assert(pc.matches()[0].type() == 1);
        assert(pc.matches()[0].begin() == input.begin());
        assert(pc.matches()[0].end() == input.begin() + 1);
        assert(pc.matches()[1].type() == 2);
        assert(pc.matches()[1].begin() == input.begin() + 1);
        assert(pc.matches()[1].end() == input.end());
    }
}


static void test_left_recursion() {
    enum {
        NUM,
        ADD,
        SUB,
        MUL,
        DIV
    };

    rule add;

    auto digit = +range('0', '9');

    rule num = (digit >> '.' >> digit)->*NUM;

    rule val = num
             | '(' >> add >> ')';

    rule mul = (mul >> '*' >> val) ->* MUL
             | (mul >> '/' >> val) ->* DIV
             | mul >> '%' >> val
             | val;

    add = (add >> '+' >> mul) ->* ADD
        | (add >> '-' >> mul) ->* SUB
        | mul;

    /*
    //used for debugging purposes
    add.name = "add";
    mul.name = "mul";
    val.name = "val";
    num.name = "num";
    */

    class calculator {
    public:
        static double eval(const match& m) {
            switch (m.type()) {
                case NUM: {
                    std::stringstream stream;
                    for (auto it = m.begin(); it != m.end(); ++it) {
                        stream << (char)*it;
                    }
                    double v;
                    stream >> v;
                    return v;
                }

                case ADD: {
                    assert(m.children().size() == 2);
                    const double v = eval(m.children()[0]) + eval(m.children()[1]);
                    return v;
                }

                case SUB: {
                    assert(m.children().size() == 2);
                    const double v = eval(m.children()[0]) - eval(m.children()[1]);
                    return v;
                }

                case MUL: {
                    assert(m.children().size() == 2);
                    const double v = eval(m.children()[0]) * eval(m.children()[1]);
                    return v;
                }

                case DIV: {
                    assert(m.children().size() == 2);
                    const double v = eval(m.children()[0]) / eval(m.children()[1]);
                    return v;
                }
            }

            throw std::runtime_error("invalid match type");
        }

        static double eval(const matches_type& matches) {
            assert(matches.size() == 1);
            return eval(matches[0]);
        }
    };

    #define CALC_TEST_1(F)\
    {\
        string_type input = #F;\
        parse_context pc(input);\
        const bool result = add.parse(pc);\
        assert(result);\
        const double v = F;\
        const double r = calculator::eval(pc.matches());\
        if (v != r) {\
            std::cout << "Assertion failed: " << v << " == " << r << ", file " << __FILE__ << ", line " << __LINE__ << std::endl;\
        }\
    }

    CALC_TEST_1(1.0);
    CALC_TEST_1(1.0+2.0);
    CALC_TEST_1(1.0+2.0+3.0);
    CALC_TEST_1(1.0+2.0*3.0);
    CALC_TEST_1(1.0+2.0/3.0);
    CALC_TEST_1(1.0*2.0+3.0);
    CALC_TEST_1(1.0/2.0+3.0);
    CALC_TEST_1(1.0-2.0);
    CALC_TEST_1(1.0-2.0-3.0);
    CALC_TEST_1(1.0-2.0*3.0);
    CALC_TEST_1(1.0-2.0/3.0);
    CALC_TEST_1(1.0*2.0-3.0);
    CALC_TEST_1(1.0/2.0-3.0);
    CALC_TEST_1(1.0+2.0-3.0*4.0/5.0);
    CALC_TEST_1(1.0/2.0*3.0-4.0+5.0);
    CALC_TEST_1((1.0+2.0)*3.0);
    CALC_TEST_1(1.0+(2.0*3.0));
    CALC_TEST_1((1.0+2.0)/3.0);
    CALC_TEST_1(1.0+(2.0/3.0));
    CALC_TEST_1((1.0*2.0)+3.0);
    CALC_TEST_1(1.0*(2.0+3.0));
    CALC_TEST_1((1.0/2.0)+3.0);
    CALC_TEST_1(1.0/(2.0+3.0));
}


static void test_error() {
    {
        rule stm = parser("a;") | "b;" | "c;" | error(1);
        parser_ptr grammar = *(stm | skip(';'));
        string_type input = "a;b;d;c;f;a;";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
        assert(pc.errors().size() == 2);
        assert(pc.errors()[0].type() == 1);
        assert(pc.errors()[0].position() == input.begin() + 4);
        assert(pc.errors()[1].type() == 1);
        assert(pc.errors()[1].position() == input.begin() + 8);
    }
}


static void test_tokenize_and_parse() {
    enum TOKEN_ID {
        TOKEN_NUM,
        TOKEN_ADD,
        TOKEN_SUB,
        TOKEN_MUL,
        TOKEN_DIV,
        TOKEN_LEFT_PARENTHESIS,
        TOKEN_RIGHT_PARENTHESIS
    };

    rule tokenizer_grammar = *(
        parser(' ') |
        (+range('0', '9') >> -('.' >> +range('0', '9')))->*TOKEN_NUM |
        parser('+')->*TOKEN_ADD |
        parser('-')->*TOKEN_SUB |
        parser('*')->*TOKEN_MUL |
        parser('/')->*TOKEN_DIV |
        parser('(')->*TOKEN_LEFT_PARENTHESIS |
        parser(')')->*TOKEN_RIGHT_PARENTHESIS
    );

    enum AST_ID {
        AST_NUM,
        AST_ADD,
        AST_SUB,
        AST_MUL,
        AST_DIV
    };

    rule parser_grammar;

    rule num = parser(TOKEN_NUM)->*AST_NUM;

    rule val = num
             | TOKEN_LEFT_PARENTHESIS >> parser_grammar >> TOKEN_RIGHT_PARENTHESIS;

    rule mul = (mul >> TOKEN_MUL >> val)->*AST_MUL
             | (mul >> TOKEN_DIV >> val)->*AST_DIV
             | val;

    rule add = (add >> TOKEN_ADD >> mul)->*AST_ADD
             | (add >> TOKEN_SUB >> mul)->*AST_SUB
             | mul;

    parser_grammar = add;

    class calculator {
    public:
        static double eval(const match& m) {
            switch (m.type()) {
            case AST_NUM: {
                std::stringstream stream;
                for (auto it = m.begin(); it != m.end(); ++it) {
                    stream << (char)*it;
                }
                double v;
                stream >> v;
                return v;
            }

            case AST_ADD: {
                assert(m.children().size() == 2);
                const double v = eval(m.children()[0]) + eval(m.children()[1]);
                return v;
            }

            case AST_SUB: {
                assert(m.children().size() == 2);
                const double v = eval(m.children()[0]) - eval(m.children()[1]);
                return v;
            }

            case AST_MUL: {
                assert(m.children().size() == 2);
                const double v = eval(m.children()[0]) * eval(m.children()[1]);
                return v;
            }

            case AST_DIV: {
                assert(m.children().size() == 2);
                const double v = eval(m.children()[0]) / eval(m.children()[1]);
                return v;
            }
            }

            throw std::runtime_error("invalid match type");
        }

        static double eval(const matches_type& matches) {
            assert(matches.size() == 1);
            return eval(matches[0]);
        }
    };

    #define CALC_TEST_2(F)\
    {\
        string_type input = #F;\
        tokenize_and_parse_result tapr;\
        const bool result = tokenize_and_parse(input, tokenizer_grammar, parser_grammar, tapr);\
        assert(result);\
        const double v = F;\
        const double r = calculator::eval(tapr.parsing.source_matches);\
        if (v != r) {\
            std::cout << "Assertion failed: " << v << " == " << r << ", file " << __FILE__ << ", line " << __LINE__ << std::endl;\
        }\
    }

    CALC_TEST_2(1.0);
    CALC_TEST_2(1.0 + 2.0);
    CALC_TEST_2(1.0 + 2.0 + 3.0);
    CALC_TEST_2(1.0 + 2.0 * 3.0);
    CALC_TEST_2(1.0 + 2.0 / 3.0);
    CALC_TEST_2(1.0 * 2.0 + 3.0);
    CALC_TEST_2(1.0 / 2.0 + 3.0);
    CALC_TEST_2(1.0 - 2.0);
    CALC_TEST_2(1.0 - 2.0 - 3.0);
    CALC_TEST_2(1.0 - 2.0 * 3.0);
    CALC_TEST_2(1.0 - 2.0 / 3.0);
    CALC_TEST_2(1.0 * 2.0 - 3.0);
    CALC_TEST_2(1.0 / 2.0 - 3.0);
    CALC_TEST_2(1.0 + 2.0 - 3.0 * 4.0 / 5.0);
    CALC_TEST_2(1.0 / 2.0 * 3.0 - 4.0 + 5.0);
    CALC_TEST_2((1.0 + 2.0) * 3.0);
    CALC_TEST_2(1.0 + (2.0 * 3.0));
    CALC_TEST_2((1.0 + 2.0) / 3.0);
    CALC_TEST_2(1.0 + (2.0 / 3.0));
    CALC_TEST_2((1.0 * 2.0) + 3.0);
    CALC_TEST_2(1.0 * (2.0 + 3.0));
    CALC_TEST_2((1.0 / 2.0) + 3.0);
    CALC_TEST_2(1.0 / (2.0 + 3.0));
}


static void test_any() {
    {
        parser_ptr grammar = any();
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = any();
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }
}


void run_tests() {
    test_symbol_parser();
    test_string_parser();
    test_set_parser();
    test_range_parser();
    test_loop_zero_parser();
    test_loop_one_parser();
    test_optional_parser();
    test_sequence_parser();
    test_choice_parser();
    test_rule();
    test_match();
    test_left_recursion();
    test_error();
    test_tokenize_and_parse();
    test_any();
}
