#include <algorithm>
#include "xparserlib/set_parser.hpp"


namespace xparserlib {


    static string_type _sort(const string_type& str) {
        string_type result{str.begin(), str.end()};
        std::sort(result.begin(), result.end());
        return result;
    }


    set_parser::set_parser(const string_type& set)
        : m_set(_sort(set))
    {
    }


    bool set_parser::parse(parse_context& pc) const {
        if (pc.valid()) {
            const symbol_type token = *pc.position();
            auto it = std::upper_bound(m_set.begin(), m_set.end(), token);
            if (it != m_set.begin()) {
                --it;
                if (*it == token) {
                    pc.increment_position();
                    return true;
                }
            }
        }
        return false;
    }


    parser_ptr set(const string_type& set) {
        return std::make_shared<set_parser>(set);
    }


} //namespace xparserlib
