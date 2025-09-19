#include "xparserlib/match.hpp"


namespace xparserlib {


    string_type::string_type(const char* string) {
        if (string) {
            for (; *string; ++string) {
                push_back(*string);
            }
        }
    }


    string_type::string_type(const wchar_t* string) {
        if (string) {
            for (; *string; ++string) {
                push_back(*string);
            }
        }
    }


    string_type::string_type(const matches_type& tokens)
        : std::vector<symbol_type>(tokens.size())
    {
        for (size_t index = 0; index < tokens.size(); ++index) {
            std::vector<symbol_type>::operator[](index) = tokens[index].type();
        }
    }


} //namespace xparserlib
