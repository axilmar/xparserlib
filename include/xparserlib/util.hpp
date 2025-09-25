#ifndef XPARSERLIB_UTIL_HPP
#define XPARSERLIB_UTIL_HPP


#include <string>


namespace xparserlib {


    /**
     * Loads a file into memory.
     * @param path file to load.
     * @return the file as a string.
     */
    std::string load_file(const char* path);


    } //namespace xparserlib


#endif //XPARSERLIB_UTIL_HPP
