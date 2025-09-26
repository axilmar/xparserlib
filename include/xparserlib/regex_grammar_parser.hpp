#ifndef XPARSERLIB_REGEX_GRAMMAR_PARSER_HPP
#define XPARSERLIB_REGEX_GRAMMAR_PARSER_HPP


#include <regex>
#include "range_parser.hpp"


namespace xparserlib {


    /**
     * A parser that instantiates a regular expression (std::regex)
     * with the source code to check if the source represents a regular expression.
     * 
     * If a regular expression can be instantiated without an exception,
     * then the source is a legit regular expression.
     * 
     * After the parsing, the parse context position is set to the end of the regular
     * expression text.
     * 
     * The limit of the regular expression text is defined by another parser.
     */
    class regex_grammar_parser : public parser {
    public:
        /**
         * The constructor.
         * @param delimiter_parser the parser to use for recognizing the boundaries of the regular expression.
         * @param flags the regular expression constructor flags.
         */
        regex_grammar_parser(const parser_ptr& delimiter_parser, std::regex::flag_type flags = std::regex_constants::ECMAScript);

        /**
         * Parses the input.
         * It first calls the delimiter parser to parse the incoming input.
         * When the delimiter parser returns true,
         * the regular expression's range is from the parsing position
         * when this function is called to the first position
         * recognized by the delimiter parser.
         * @param pc the parse context.
         * @return true on success, false otherwise.
         */
        bool parse(parse_context& pc) const override;

    private:
        parser_ptr m_delimiter_parser;
        std::regex::flag_type m_flags;
    };


    /**
     * Creates a regex grammar parser.
     * @param delimiter_parser the parser to use for recognizing the boundaries of the regular expression.
     * @param flags the regular expression constructor flags.
     * @return a regex grammar parser.
     */
    parser_ptr regex_grammar(const parser_ptr& delimiter_parser, std::regex::flag_type flags = std::regex_constants::ECMAScript);


    /**
     * A parser that instantiates a regular expression (std::wregex)
     * with the source code to check if the source represents a regular expression.
     *
     * If a regular expression can be instantiated without an exception,
     * then the source is a legit regular expression.
     *
     * After the parsing, the parse context position is set to the end of the regular
     * expression text.
     *
     * The limit of the regular expression text is defined by another parser.
     */
    class wregex_grammar_parser : public parser {
    public:
        /**
         * The constructor.
         * @param delimiter_parser the parser to use for recognizing the boundaries of the regular expression.
         * @param flags the regular expression constructor flags.
         */
        wregex_grammar_parser(const parser_ptr& delimiter_parser, std::wregex::flag_type flags = std::regex_constants::ECMAScript);

        /**
         * Parses the input.
         * It first calls the delimiter parser to parse the incoming input.
         * When the delimiter parser returns true,
         * the regular expression's range is from the parsing position
         * when this function is called to the first position
         * recognized by the delimiter parser.
         * @param pc the parse context.
         * @return true on success, false otherwise.
         */
        bool parse(parse_context& pc) const override;

    private:
        std::wregex::flag_type m_flags;
        parser_ptr m_delimiter_parser;
    };


    /**
     * Creates a wregex grammar parser.
     * @param delimiter_parser the parser to use for recognizing the boundaries of the regular expression.
     * @param flags the regular expression constructor flags.
     * @return a wregex grammar parser.
     */
    parser_ptr wregex_grammar(const parser_ptr& delimiter_parser, std::wregex::flag_type flags = std::regex_constants::ECMAScript);


} //namespace xparserlib


#endif //XPARSERLIB_REGEX_GRAMMAR_PARSER_HPP
