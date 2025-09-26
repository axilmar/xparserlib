#include <cassert>
#include "xparserlib/parse_context.hpp"


namespace xparserlib {


    parse_context::state::state(const iterator_type& p, size_t mc)
        : m_position(p)
        , m_match_count(mc)
    {
    }


    parse_context::parse_context(string_type& string) 
        : parse_context(string.begin(), string.end())
    {
    }


    parse_context::parse_context(const iterator_type& begin, const iterator_type& end)
        : m_position(begin)
        , m_end(end)
    {
        assert(begin <= end);
    }


    const iterator_type& parse_context::position() const {
        return m_position;
    }


    const matches_type& parse_context::matches() const {
        return m_matches;
    }

    
    const iterator_type& parse_context::end() const {
        return m_end;
    }


    bool parse_context::valid() const {
        return m_position < m_end;
    }


    bool parse_context::ended() const {
        return m_position == m_end;
    }


    class parse_context::state parse_context::state() const {
        return { m_position, m_matches.size() };
    }


    errors_type parse_context::errors() const {
        errors_type errors(m_errors.size());
        size_t index = 0;
        for (const auto& p : m_errors) {
            errors[index] = p.second;
            ++index;
        }
        return errors;
    }


    void parse_context::increment_position() {
        ++m_position;
        assert(m_position <= m_end);
    }


    void parse_context::increment_position(size_t count) {
        m_position += count;
        assert(m_position <= m_end);
    }


    void parse_context::add_match(match_type type, const iterator_type& begin, const iterator_type& end, size_t first_child_index) {
        assert(begin < m_end);
        assert(end <= m_end);
        assert(begin < end);
        assert(first_child_index <= m_matches.size());
        matches_type match_children;
        match_children.insert(match_children.end(), std::make_move_iterator(m_matches.begin() + first_child_index), std::make_move_iterator(m_matches.end()));
        m_matches.resize(first_child_index);
        m_matches.push_back({ match(type, begin, end, std::move(match_children)) });
    }


    void parse_context::set_state(const class state& state) {
        m_position = state.m_position;
        m_matches.resize(state.m_match_count);
    }


    void parse_context::add_error(error_type type, const iterator_type& begin, const iterator_type& end) {
        assert(begin < end);
        assert(begin < m_end);
        assert(end <= m_end);
        const class error error(type, begin, end);
        const auto [it, ok] = m_errors.insert(std::make_pair(begin, error));
        if (!ok) {
            class error& last_error = it->second;

            //same error type
            if (last_error.m_type == type) {
                if (end > last_error.m_end) {
                    last_error.m_end = end;
                }
            }

            //else other error type
            else {
                if (end >= last_error.m_end) {
                    last_error.m_type = type;
                    last_error.m_end = end;
                }
            }
        }
    }


} //namespace xparserlib
