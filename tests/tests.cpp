#include <cassert>
#include <iostream>
#include <sstream>
#include "xparserlib.hpp"


using namespace xparserlib;


static void test_symbol_parser() {
    {
        parser_ptr grammar = symbol('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = symbol('a');
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_string_parser() {
    {
        parser_ptr grammar = string("abc");
        string_type input = "abc";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = string("abc");
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
        parser_ptr grammar = -symbol('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = -symbol('a');
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.begin());
    }
}


static void test_sequence_parser() {
    {
        parser_ptr grammar = symbol('a') >> 'b' >> "xy";
        string_type input = "abxy";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = symbol('a') >> 'b' >> "xy";
        string_type input = "ab1y";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_choice_parser() {
    {
        parser_ptr grammar = symbol('a') | 'b' | "xy";
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = symbol('a') | 'b' | "xy";
        string_type input = "b";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = symbol('a') | 'b' | "xy";
        string_type input = "xy";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        parser_ptr grammar = symbol('a') | 'b' | "xy";
        string_type input = "1";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(!result);
        assert(pc.position() == input.begin());
    }
}


static void test_rule() {
    {
        rule grammar = symbol('a');
        string_type input = "a";
        parse_context pc(input);
        const bool result = grammar.parse(pc);
        assert(result);
        assert(pc.position() == input.end());
    }

    {
        rule grammar = symbol('a');
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
        parser_ptr grammar = (symbol('a') ->* 1) >> symbol('b') ->* 2;
        string_type input = "ab";
        parse_context pc(input);
        const bool result = grammar->parse(pc);
        assert(result);
        assert(pc.position() == input.end());
        assert(pc.matches().size() == 2);
        assert(pc.matches()[0].type == 1);
        assert(pc.matches()[0].begin == input.begin());
        assert(pc.matches()[0].end == input.begin() + 1);
        assert(pc.matches()[1].type == 2);
        assert(pc.matches()[1].begin == input.begin() + 1);
        assert(pc.matches()[1].end == input.end());
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

    add.name = "add";
    mul.name = "mul";
    val.name = "val";
    num.name = "num";

    class calculator {
    public:
        static double eval(const matches_type& matches) {
            std::vector<double> stack;

            for (const match& m : matches) {
                switch (m.type) {
                    case NUM: {
                        std::stringstream stream;
                        for (auto it = m.begin; it != m.end; ++it) {
                            stream << (char)*it;
                        }
                        double v;
                        stream >> v;
                        stack.push_back(v);
                        break;
                    }

                    case ADD: {
                        assert(stack.size() >= 2);
                        const double a1 = *(stack.end() - 2);
                        const double a2 = *(stack.end() - 1);
                        const double v = a1 + a2;
                        stack.pop_back();
                        stack.pop_back();
                        stack.push_back(v);
                        break;
                    }

                    case SUB: {
                        assert(stack.size() >= 2);
                        const double a1 = *(stack.end() - 2);
                        const double a2 = *(stack.end() - 1);
                        const double v = a1 - a2;
                        stack.pop_back();
                        stack.pop_back();
                        stack.push_back(v);
                        break;
                    }

                    case MUL: {
                        assert(stack.size() >= 2);
                        const double a1 = *(stack.end() - 2);
                        const double a2 = *(stack.end() - 1);
                        const double v = a1 * a2;
                        stack.pop_back();
                        stack.pop_back();
                        stack.push_back(v);
                        break;
                    }

                    case DIV: {
                        assert(stack.size() >= 2);
                        const double a1 = *(stack.end() - 2);
                        const double a2 = *(stack.end() - 1);
                        const double v = a1 / a2;
                        stack.pop_back();
                        stack.pop_back();
                        stack.push_back(v);
                        break;
                    }
                }
            }

            assert(stack.size() == 1);
            return stack.front();
        }
    };

    #define CALC_TEST(F)\
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

    CALC_TEST(1.0);
    CALC_TEST(1.0+2.0);
    CALC_TEST(1.0+2.0+3.0);
    CALC_TEST(1.0+2.0*3.0);
    CALC_TEST(1.0+2.0/3.0);
    CALC_TEST(1.0*2.0+3.0);
    CALC_TEST(1.0/2.0+3.0);
    CALC_TEST(1.0-2.0);
    CALC_TEST(1.0-2.0-3.0);
    CALC_TEST(1.0-2.0*3.0);
    CALC_TEST(1.0-2.0/3.0);
    CALC_TEST(1.0*2.0-3.0);
    CALC_TEST(1.0/2.0-3.0);
    CALC_TEST(1.0+2.0-3.0*4.0/5.0);
    CALC_TEST(1.0/2.0*3.0-4.0+5.0);
    CALC_TEST((1.0+2.0)*3.0);
    CALC_TEST(1.0+(2.0*3.0));
    CALC_TEST((1.0+2.0)/3.0);
    CALC_TEST(1.0+(2.0/3.0));
    CALC_TEST((1.0*2.0)+3.0);
    CALC_TEST(1.0*(2.0+3.0));
    CALC_TEST((1.0/2.0)+3.0);
    CALC_TEST(1.0/(2.0+3.0));
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
}
