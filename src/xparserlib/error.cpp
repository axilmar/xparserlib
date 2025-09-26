#include "xparserlib/error.hpp"


namespace xparserlib {


    error::error(error_type type, const iterator_type& begin, const iterator_type& end)
        : m_type(type)
        , m_begin(begin)
        , m_end(end)
    {
    }


    error_type error::type() const {
        return m_type;
    }


    const iterator_type& error::begin() const {
        return m_begin;
    }


    const iterator_type& error::end() const {
        return m_end;
    }


} //namespace xparserlib
