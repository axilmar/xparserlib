#ifndef XPARSERLIB_REPEAT_TIMES_PARSER
#define XPARSERLIB_REPEAT_TIMES_PARSER


#include "rule.hpp"


namespace xparserlib {


    /**
     * A parser that repeats another parser a specific number of times.
     */
    class repeat_times_parser : public parser {
    public:
        /**
         * The constructor.
         * @param times number of times to repeat the parser.
         * @param parser the parser to repeat.
         */
        repeat_times_parser(size_t times, const parser_ptr& parser);

        /**
         * Repeats a parser a specific number of times.
         * @param pc parse context.
         * @return true if the parser was successful the specific number of times, false otherwise.
         */
        bool parse(parse_context& pc) const override;

    private:
        const size_t m_times;
        parser_ptr m_parser;
    };


    /**
     * Creates a repeat_times_parser.
     * @param times number of times to repeat a parser.
     * @param parser parser to repeat.
     * @return a repeat_times_parser instance.
     */
    parser_ptr operator * (size_t times, const parser_ptr& parser);


} //namespace xparserlib


#endif //XPARSERLIB_REPEAT_TIMES_PARSER
