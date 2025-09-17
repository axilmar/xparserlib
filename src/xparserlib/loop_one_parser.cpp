#include "xparserlib/loop_one_parser.hpp"


namespace xparserlib {


    loop_one_parser::loop_one_parser(const parser_ptr& parser)
        : m_parser(parser)
    {
    }


    bool loop_one_parser::parse(parse_context& pc) const {
        if (!m_parser->parse(pc)) {
            return false;
        }
        while (true) {
            const iterator_type start_position = pc.position();
            if (!m_parser->parse(pc) || pc.position() == start_position) {
                break;
            }
        }
        return true;
    }


    parser_ptr make_loop_one_parser(const parser_ptr& parser) {
        return std::make_shared<loop_one_parser>(parser);
    }


} //namespace xparserlib
