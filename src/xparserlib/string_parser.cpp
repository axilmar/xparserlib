#include "xparserlib/string_parser.hpp"


namespace xparserlib {


    string_parser::string_parser(const string_type& string)
        : m_string(string)
    {
    }


    bool string_parser::parse(parse_context& pc) const {
        iterator_type this_it = m_string.begin();
        iterator_type pc_it = pc.position();
        for(;;) {
            if (this_it == m_string.end()) {
                pc.increment_position(m_string.size());
                return true;
            }
            if (pc_it == pc.end() || *this_it != *pc_it) {
                break;
            }
            ++this_it;
            ++pc_it;
        }
        return false;
    }


    parser_ptr parser(const char* string) {
        return std::make_shared<string_parser>(string);
    }


    parser_ptr parser(const wchar_t* string) {
        return std::make_shared<string_parser>(string);
    }


    parser_ptr parser(const string_type& string) {
        return std::make_shared<string_parser>(string);
    }


} //namespace xparserlib
