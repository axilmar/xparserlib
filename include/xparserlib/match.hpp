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
    struct match {
        /**
         * Type of match.
         */
        match_type type;

        /**
         * Where the match begins, in the source.
         */
        iterator_type begin;

        /**
         * Where the match ends, in the source.
         */
        iterator_type end;
    };


} //namespace xparserlib


#endif //XPARSERLIB_MATCH_HPP
