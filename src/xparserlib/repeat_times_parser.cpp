#include "xparserlib/repeat_times_parser.hpp"


namespace xparserlib {


    repeat_times_parser::repeat_times_parser(size_t times, const parser_ptr& parser)
        : m_times(times)
        , m_parser(parser)
    {
    }


    bool repeat_times_parser::parse(parse_context& pc) const {
        const auto start_state = pc.state();
        for (size_t i = 0; i < m_times; ++i) {
            if (!m_parser->parse(pc)) {
                pc.set_state(start_state);
                return false;
            }
        }
        return true;
    }


    parser_ptr operator * (size_t times, const parser_ptr& parser) {
        return std::make_shared<repeat_times_parser>(times, parser);
    }


} //namespace xparserlib
