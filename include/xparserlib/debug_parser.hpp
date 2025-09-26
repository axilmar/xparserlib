#ifndef XPARSERLIB_DEBUG_PARSER_HPP
#define XPARSERLIB_DEBUG_PARSER_HPP


#include "parser.hpp"


namespace xparserlib {


    class debug_parser : public parser {
    public:
        debug_parser(const parser_ptr& ptr)
            : m_parser(ptr)
        {
        }

        bool parse(parse_context& pc) const override {
            return m_parser->parse(pc);
        }

    private:
        parser_ptr m_parser;
    };


    inline parser_ptr debug(const parser_ptr& parser) {
        return std::make_shared<debug_parser>(parser);
    }


} //namespace xparserlib


#endif //XPARSERLIB_DEBUG_PARSER_HPP
