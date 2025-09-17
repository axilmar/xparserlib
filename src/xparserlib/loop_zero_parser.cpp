#include "xparserlib/loop_zero_parser.hpp"


namespace xparserlib {


    loop_zero_parser::loop_zero_parser(const parser_ptr& parser)
        : m_parser(parser)
    {
    }


    bool loop_zero_parser::parse(parse_context& pc) const {
        while (true) {
            const iterator_type start_position = pc.position();
            if (!m_parser->parse(pc) || pc.position() == start_position) {
                break;
            }
        }
        return true;
    }


    parser_ptr make_loop_zero_parser(const parser_ptr& parser) {
        return std::make_shared<loop_zero_parser>(parser);
    }


} //namespace xparserlib
