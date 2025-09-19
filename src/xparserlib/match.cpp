#include "xparserlib/match.hpp"


namespace xparserlib {


    match::match(match_type type, const iterator_type& begin, const iterator_type& end)
        : m_type(type)
        , m_begin(begin)
        , m_end(end)
    {
    }


    match_type match::type() const {
        return m_type;
    }


    const iterator_type& match::begin() const {
        return m_begin;
    }


    const iterator_type& match::end() const {
        return m_end;
    }


} //namespace xparserlib
