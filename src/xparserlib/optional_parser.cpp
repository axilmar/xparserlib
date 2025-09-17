#include "xparserlib/optional_parser.hpp"


namespace xparserlib {


    optional_parser::optional_parser(const parser_ptr& parser)
        : m_parser(parser)
    {
    }


    bool optional_parser::parse(parse_context& pc) const {
        m_parser->parse(pc);
        return true;
    }


    parser_ptr make_optional_parser(const parser_ptr& parser) {
        return std::make_shared<optional_parser>(parser);
    }


} //namespace xparserlib
