#ifndef XPARSERLIB_SET_PARSER_HPP
#define XPARSERLIB_SET_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    /**
     * A parser that parses a single symbol out of a set.
     */
    class set_parser : public parser {
    public:
        /**
         * The constructor.
         * @param set set to parse.
         */
        set_parser(const string_type& set);

        /**
         * Parses a set.
         * @param pc the parse context.
         * @return true on success, false on failure.
         */
        bool parse(parse_context& pc) const override;

    private:
        const string_type m_set;
    };


    /**
     * Creates a parser out of a set.
     * @param set set to create a set parser from.
     * @return a set parser.
     */
    parser_ptr set(const string_type& set);


} //namespace xparserlib


#endif //XPARSERLIB_SET_PARSER_HPP
