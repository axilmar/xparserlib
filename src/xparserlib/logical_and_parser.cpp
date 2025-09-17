#include "xparserlib/logical_and_parser.hpp"


namespace xparserlib {


    logical_and_parser::logical_and_parser(const parser_ptr& parser)
        : m_parser(parser)
    {
    }


    bool logical_and_parser::parse(parse_context& pc) const {
        const auto start_state = pc.state();
        const bool result = m_parser->parse(pc);
        pc.set_state(start_state);
        return result;
    }


    parser_ptr make_logical_and_parser(const parser_ptr& parser) {
        return std::make_shared<logical_and_parser>(parser);
    }


} //namespace xparserlib
