#include "xparserlib/skip_parser.hpp"


namespace xparserlib {


    skip_parser::skip_parser(const parser_ptr& parser)
        : m_parser(parser)
    {
    }


    bool skip_parser::parse(parse_context& pc) const {
        while (pc.valid()) {
            if (m_parser->parse(pc)) {
                return true;
            }
            pc.increment_position();
        }
        return false;
    }


    parser_ptr skip(const parser_ptr& parser) {
        return std::make_shared<skip_parser>(parser);
    }


} //namespace xparserlib
