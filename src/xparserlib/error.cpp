#include "xparserlib/error.hpp"


namespace xparserlib {


    error::error(error_type type, const iterator_type& position)
        : m_type(type)
        , m_position(position)
    {
    }


    error_type error::type() const {
        return m_type;
    }


    const iterator_type& error::position() const {
        return m_position;
    }


} //namespace xparserlib
