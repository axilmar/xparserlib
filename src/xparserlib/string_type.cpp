#include "xparserlib/string_type.hpp"


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


} //namespace xparserlib
