#ifndef XPARSERLIB_STRING_TYPE_HPP
#define XPARSERLIB_STRING_TYPE_HPP


#include <vector>


namespace xparserlib {


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
    };


} //namespace xparserlib


#endif //XPARSERLIB_STRING_TYPE_HPP
