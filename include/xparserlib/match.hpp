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
         * @param begin begin position.
         * @param end end position.
         */
        match(match_type type, const iterator_type& begin, const iterator_type& end);

        /**
         * Returns the type of match.
         * @return the type of match.
         */
        match_type type() const;

        /**
         * Returns an iterator at where the match begins, in the source.
         * @return iterator to the match start.
         */
        const iterator_type& begin() const;

        /**
         * Returns an iterator at where the match ends, in the source.
         * @return iterator to the match end.
         */
        const iterator_type& end() const;

    private:
        match_type m_type;
        iterator_type m_begin;
        iterator_type m_end;
    };


} //namespace xparserlib


#endif //XPARSERLIB_MATCH_HPP
