#include <cassert>
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
}
