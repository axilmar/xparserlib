#ifndef XPARSERLIB_PARSE_CONTEXT_HPP
#define XPARSERLIB_PARSE_CONTEXT_HPP


#include "match.hpp"
#include "error.hpp"


namespace xparserlib {


    class lrm;


    /**
     * Parse context.
     * 
     * Keeps the parsing state.
     * Provides functions for manipulating it.
     */
    class parse_context {
    public:
        /**
         * Represents the current state of the parse context.
         * Opaque type, used by parser classes to rewind the state
         * of parsing to a particular point.
         */
        class state {
        private:
            const iterator_type position;
            const size_t match_count;
            state(const iterator_type& p, size_t mc);
            friend class parse_context;
        };

        /**
         * Constructor from string type.
         * @param string string to parse.
         */
        parse_context(string_type& string);

        /**
         * Constructor from range.
         * Range checks are only done at compile-time.
         * @param begin begin of string to parse.
         * @param end end of string to parse.
         */
        parse_context(const iterator_type& begin, const iterator_type& end);

        /**
         * Returns the current position.
         * @return the current position.
         */
        const iterator_type& position() const;

        /**
         * Returns the current matches.
         * @return the current matches.
         */
        const matches_type& matches() const;

        /**
         * Returns the source end.
         * @return the source end.
         */
        const iterator_type& end() const;

        /**
         * Checks if the current position has reached the end position.
         * @return true if the current position has not reached the end position, false otherwise.
         */
        bool valid() const;

        /**
         * Returns the current state.
         * @return the current state.
         */
        class state state() const;

        /**
         * Returns the current errors.
         * @return the current errors.
         */
        const errors_type& errors() const;

        /**
         * Increments the current position by 1.
         * Overflow checks are only done at compile-time.
         */
        void increment_position();

        /**
         * Increments the current position by the given amount.
         * Overflow checks are only done at compile-time.
         * @param count number of positions to increment the current position.
         */
        void increment_position(size_t count);

        /**
         * Adds a match.
         * Overflow and range checks are only done at compile-time.
         * @param type type of match.
         * @param begin start position of the match into the source.
         * @param end end position of the match into the source.
         * @param first_child_index index of first match child.
         */
        void add_match(match_type type, const iterator_type& begin, const iterator_type& end, size_t first_child_index);

        /**
         * Sets the current state from a previously recorded state.
         * @param state the state to set.
         */
        void set_state(const class state& state);

        /**
         * Adds an error.
         * Overflow and range checks are only done at compile-time.
         * @param type type of error.
         * @param position position of the error into the source.
         */
        void add_error(error_type type, const iterator_type& position);

    private:
        //current position
        iterator_type m_position;

        //current matches
        matches_type m_matches;

        //source end
        iterator_type m_end;

        //left recursion state
        struct left_recursion_state {
            iterator_type position;
            size_t match_count;
        };

        //left-recursion state stack
        std::vector<left_recursion_state> m_lrs;

        //errors
        errors_type m_errors;

        friend class lrm;
    };


} //namespace xparserlib


#endif //XPARSERLIB_PARSE_CONTEXT_HPP
