# XParserLib

Another take on a parsing library, also based on c++17.

Developing a parser requires lots and lots of compilations, due to the many trials needed to achieve the desired grammar.

While the [`parserlib`](https://github.com/axilmar/parserlib) library has achieved its purpose of providing a runtime-efficient modern parsing library, it is not compile-time friendly, due to excessive use of templates. 

Therefore, this library is also a recursive-descent library, based on the same principles as `parserlib`, but it avoids templates when it can, replacing it with polymorhic classes, in order to be compile-efficient.
