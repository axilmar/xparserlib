#ifndef XPARSERLIB_MATCH_HPP
#define XPARSERLIB_MATCH_HPP


#include "string_type.hpp"


namespace xparserlib {


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
         * @param end the end position.
         * @param children children matches.
         */
        match(match_type type, const iterator_type& begin, const iterator_type& end, matches_type&& children);

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
         * Returns the end position in the source string.
         * @return the end position in the source string.
         */
        const iterator_type& end() const;

        /**
         * Returns the children matches.
         * @return the children matches.
         */
        const matches_type& children() const;

    private:
        match_type m_type;
        iterator_type m_begin;
        iterator_type m_end;
        matches_type m_children;
    };


} //namespace xparserlib


#endif //XPARSERLIB_MATCH_HPP
