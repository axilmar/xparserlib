#ifndef XPARSERLIB_PARSER_HPP
#define XPARSERLIB_PARSER_HPP


#include "parse_context.hpp"
#include "parser_ptr.hpp"


namespace xparserlib {


    /**
     * Base class for parser components.
     */
    class parser {
    public:
        /**
         * Virtual destructor due to polymorphism.
         */
        virtual ~parser() {}

        /**
         * Interface for parsing.
         * @param pc parse context.
         * @return true on success, false on failure.
         */
        virtual bool parse(parse_context& pc) const = 0;
    };


    /**
     * Parser container type.
     */
    using parsers_type = std::vector<parser_ptr>;


} //namespace xparserlib


#endif //XPARSERLIB_PARSER_HPP
