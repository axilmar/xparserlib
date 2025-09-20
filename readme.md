# XParserLib

Another take on a parsing library, also based on c++17.

Developing a parser requires lots and lots of compilations, due to the many trials needed to achieve the desired grammar.

While the [`parserlib`](https://github.com/axilmar/parserlib) library has achieved its purpose of providing a runtime-efficient modern parsing library, it is not compile-time friendly, due to excessive use of templates. 

Therefore, this library is also a recursive-descent library, based on the same principles as `parserlib`, but it avoids templates when it can, replacing it with polymorhic classes, in order to be compile-time-efficient.

Capabilities this and `parserlib` share:

- use of c++ operators `(>>, |, *, +, -, &, !, ->*)` for grammar expressions.
- support for strings, sets and ranges.
- support for immediate left recursion.
- multiple error handling.

Capabilities of `parserlib` this library does not have:

- support for generic left recursion; only the immediate form is supported.
- templates.

## Using this library

The library consists of multiple include files (in folder `include/xparserlib`), and multiple source files (in folder `src/xparserlib`), which shall be included in the target project.

The main header is `xparserlib.hpp`, in folder `include`.

## Writing grammars

Writing a grammar involves writing grammatic expressions, and then assigning them to `rule` objects.

Grammatic expressions include:

- terminal symbols:
	- characters (any type assignable to `int`)
	- strings (any type assignable to a string of `int`)
	- booleans
	- end-of-input
	- sets
	- ranges
- non-terminal symbols:
	- sequences
	- choices
	- loops
	- optionals
	- logical operations (`and` and `not`)
- other:
	- matches
	- errors
	- gotos

### Terminal symbols

```cpp
	//characters
	rule c1 = 'a';
    rule c2 = parser('a');
    rule c3 = SYMBOL_A; //enumeration
    rule c4 = 61;
    
    //strings
    rule s1 = "ab";
    rule s2 = L"ab";
    rule s3 = {1, 2, 3};
    rule s4 = {'1', '2', '3'};
    
    //sets
    rule digits1 = set({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'});
    
    //ranges
    rule digits2 = range('0', '9');
    
    //end of input
    rule grammar = '1' >> end();
```

### Non-terminal symbols

```cpp
	rule sequence = parser('a') >> 'b' >> "cd";
    rule choice = parser('1') | '2' | sequence;
    rule loop_0_or_more_times = *parser('$');
    rule loop_1_or_more_times = +parser('$');
    rule optional = -parser('a');
    rule match_a = &parser('a');
    rule match_not_a = !parser('a');
```

### Other

```cpp
	//matches
    rule match_a = parser('a') ->* 'A';

	//errors
	rule word = (+digit >> ';') | error(ERROR_EXPECTED_WORD);
    
    //gotos
    rule next_word = word | skip(';');
    
```

## Grammar examples

```cpp
/* calculator */

enum CALC {
	VAL,
    ADD,
    SUB,
    MUL,
    DIV
};

extern rule expression;

rule digit = range('0', '9');

rule number = +digit >> -('.' >> +digit);

rule val = '(' >> expression >> ')';

rule mul = (mul >> '*' >> val) ->* MUL
         | (mul >> '/' >> val) ->* DIV
         | val;
         
rule add = (add >> '+' >> mul) ->* ADD
         | (add >> '-' >> mul) ->* SUB
         | mul;
         
rule expression = add;
```

## Left recursion

The library can only handle immediate left recursion, of the following form:

```
	A = A B1 B2 ... Bn
      | A C1 C2 ... Cn
      | D1
      | D2
      | ...
      | Dn
```

The above grammar is converted to the following grammar, during grammar construction:

```
	A = (D1 | D2 | ... | Dn) (B1 B2 ... Bn | C1 C2 ... Cn)*
```

Matches are preserved during the conversion.

Handling only the immediate left recursion case allows for simplification of code.

The original `parserlib` library handled any form of left recursion, but it did so during parsing; this library does the conversion at grammar construction time, and therefore the cost of handling left recursion is paid only once, instead of each time something is parsed.

Forms of left recursion other than the immediate ones are usually not interesting in the context of writing compiler frond ends, and therefore they were not considered useful to handle.
