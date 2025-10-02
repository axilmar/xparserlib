#include "xparserlib/match_parser.hpp"
#include "xparserlib/string_parser.hpp"


namespace xparserlib {


    match_parser::match_parser(const parser_ptr& parser, match_type type)
        : m_parser(parser)
        , m_type(type)
    {
    }


    bool match_parser::parse(parse_context& pc) const {
        const iterator_type start_position = pc.position();
        const size_t start_line = pc.line();
        const size_t start_column = pc.column();
        const size_t first_child_index = pc.matches().size();
        if (m_parser->parse(pc)) {
            pc.add_match(m_type, start_position, start_line, start_column, pc.position(), pc.line(), pc.column(), first_child_index);
            return true;
        }
        return false;
    }


    const parser_ptr& match_parser::parser() const {
        return m_parser;
    }
    

    match_type match_parser::type() const {
        return m_type;
    }


    parser_ptr operator ->* (const parser_ptr& parser, match_type type) {
        return std::make_shared<match_parser>(parser, type);
    }


    parser_ptr operator ->* (const string_type& string, match_type type) {
        return std::make_shared<match_parser>(parser(string), type);
    }


    parser_ptr operator ->* (class rule& rule, match_type type) {
        return std::make_shared<match_parser>(parser(rule), type);
    }


} //namespace xparserlib
