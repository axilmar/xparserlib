#ifndef XPARSERLIB_STRING_TYPE_HPP
#define XPARSERLIB_STRING_TYPE_HPP


#include <vector>
#include <string>


namespace xparserlib {


    class match;


    /**
     * Container of matches.
     */
    using matches_type = std::vector<match>;


    /**
     * Symbols to parse are simple integers, for efficiency.
     * The library can be used to parse characters as well as tokens,
     * so 'int' is treated as a universal type.
     */
    using symbol_type = int;


    /**
     * Strings to parse are vectors of symbols, for efficiency.
     */
    class string_type : public std::vector<symbol_type> {
    public:
        using std::vector<symbol_type>::vector;

        /**
         * Constructor from null-terminated string.
         * @param string null-terminated string.
         */
        string_type(const char* string);

        /**
         * Constructor from null-terminated wide string.
         * @param string null-terminated wide string.
         */
        string_type(const wchar_t* string);

        /**
         * Constructor from string object.
         * @param string string object.
         */
        string_type(const std::string& string);

        /**
         * Constructor from wide string object.
         * @param string string object.
         */
        string_type(const std::wstring& string);

        /**
         * Extracts an input string from a series of matches.
         * Useful for tokenization.
         * @param tokens tokens to use for extracting a string for parsing; 
         *  the match type becomes the symbol to parse.
         */
        string_type(const matches_type& tokens);
    };


    /**
     * Iterator over a string.
     */
    using iterator_type = string_type::const_iterator;


} //namespace xparserlib


#endif //XPARSERLIB_STRING_TYPE_HPP
