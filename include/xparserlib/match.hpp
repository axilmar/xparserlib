#ifndef XPARSERLIB_MATCH_HPP
#define XPARSERLIB_MATCH_HPP


#include "string_type.hpp"


namespace xparserlib {


    class tapm;


    /**
     * The match type; integer, for efficiency.
     */
    using match_type = int;


    /**
     * A match.
     */
    class match {
    public:
        /**
         * The default constructor.
         */
        match() {}

        /**
         * The constructor.
         * @param type type of match.
         * @param begin the start position.
         * @param begin_line the line index of the start position.
         * @param end the end position.
         * @param end the end position.
         * @param end_line the line index of the end position.
         * @param children children matches.
         */
        match(match_type type, const iterator_type& begin, size_t begin_line, size_t begin_column, const iterator_type& end, size_t end_line, size_t end_column, matches_type&& children);

        /**
         * Returns the type of match.
         * @return the type of match.
         */
        match_type type() const;

        /**
         * Returns the start position in the source string.
         * @return the start position in the source string.
         */
        const iterator_type& begin() const;

        /**
         * Returns the line index of the start position.
         * @return the line index of the start position.
         */
        size_t begin_line() const;

        /**
         * Returns the column index of the start position.
         * @return the column index of the start position.
         */
        size_t begin_column() const;

        /**
         * Returns the end position in the source string.
         * @return the end position in the source string.
         */
        const iterator_type& end() const;

        /**
         * Returns the line index of the end position.
         * @return the line index of the end position.
         */
        size_t end_line() const;

        /**
         * Returns the column index of the end position.
         * @return the column index of the end position.
         */
        size_t end_column() const;

        /**
         * Returns the children matches.
         * @return the children matches.
         */
        const matches_type& children() const;

    private:
        match_type m_type;
        iterator_type m_begin;
        size_t m_begin_line;
        size_t m_begin_column;
        iterator_type m_end;
        size_t m_end_line;
        size_t m_end_column;
        matches_type m_children;

        friend class tapm;
    };


} //namespace xparserlib


#endif //XPARSERLIB_MATCH_HPP
