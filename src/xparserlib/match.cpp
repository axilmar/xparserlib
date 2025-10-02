#include "xparserlib/match.hpp"


namespace xparserlib {


    match::match(match_type type, const iterator_type& begin, size_t begin_line, size_t begin_column, const iterator_type& end, size_t end_line, size_t end_column, matches_type&& children)
        : m_type(type)
        , m_begin(begin)
        , m_begin_line(begin_line)
        , m_begin_column(begin_column)
        , m_end(end)
        , m_end_line(end_line)
        , m_end_column(end_column)
        , m_children(std::move(children))
    {
    }


    match_type match::type() const {
        return m_type;
    }


    const iterator_type& match::begin() const {
        return m_begin;
    }


    size_t match::begin_line() const {
        return m_begin_line;
    }


    size_t match::begin_column() const {
        return m_begin_column;
    }


    const iterator_type& match::end() const {
        return m_end;
    }


    size_t match::end_line() const {
        return m_end_line;
    }


    size_t match::end_column() const {
        return m_end_column;
    }


    const matches_type& match::children() const {
        return m_children;
    }


} //namespace xparserlib
