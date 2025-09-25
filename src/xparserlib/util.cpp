#include <fstream>
#include <sstream>
#include "xparserlib/util.hpp"


namespace xparserlib {


    std::string load_file(const char* path) {
        std::ostringstream buf;
        std::ifstream input(path);
        buf << input.rdbuf();
        return buf.str();
    }


} //namespace xparserlib
