#include "xparserlib/newline_parser.hpp"


namespace xparserlib {


    newline_parser::newline_parser(const parser_ptr& parser)
        : m_parser(parser)
    {
    }


    bool newline_parser::parse(parse_context& pc) const {
        if (m_parser->parse(pc)) {
            pc.increment_line();
            return true;
        }
        return false;
    }


    parser_ptr newline(const parser_ptr& parser) {
        return std::make_shared<newline_parser>(parser);
    }


} //namespace xparserlib
