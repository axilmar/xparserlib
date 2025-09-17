#include "xparserlib/logical_not_parser.hpp"


namespace xparserlib {


    logical_not_parser::logical_not_parser(const parser_ptr& parser)
        : m_parser(parser)
    {
    }


    bool logical_not_parser::parse(parse_context& pc) const {
        const auto start_state = pc.state();
        const bool result = !m_parser->parse(pc);
        pc.set_state(start_state);
        return result;
    }


    parser_ptr make_logical_not_parser(const parser_ptr& parser) {
        return std::make_shared<logical_not_parser>(parser);
    }


} //namespace xparserlib
