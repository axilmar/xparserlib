#include "xparserlib/regex_grammar_parser.hpp"


namespace xparserlib {


    template <class Regex, class Flags>
    static bool _test_regex(const iterator_type& begin, const iterator_type& end, Flags flags) {
        try {
            typename Regex::string_type input(begin, end);
            Regex regex(input.begin(), input.end(), flags);
        }
        catch (...) {
            return false;
        }
        return true;
    }


    template <class Regex, class Flags>
    static bool _parse(parse_context& pc, Flags flags, const parser_ptr& delimiter_parser) {
        if (pc.valid()) {
            const auto start_state = pc.state();
            for(;;) {
                const auto parse_state = pc.state();
                const bool delimiter_success = delimiter_parser->parse(pc);
                pc.set_state(parse_state);
                if (delimiter_success) {
                    if (_test_regex<Regex>(start_state.position(), pc.position(), flags)) {
                        return true;
                    }
                    break;
                }
                pc.increment_position();
                if (!pc.valid()) {
                    if (_test_regex<Regex>(start_state.position(), pc.position(), flags)) {
                        return true;
                    }
                    break;
                }
            }
            pc.set_state(start_state);
        }
        return false;
    }


    regex_grammar_parser::regex_grammar_parser(const parser_ptr& delimiter_parser, std::regex::flag_type flags)
        : m_delimiter_parser(delimiter_parser)
        , m_flags(flags)
    {
    }


    bool regex_grammar_parser::parse(parse_context& pc) const {
        return _parse<std::regex>(pc, m_flags, m_delimiter_parser);
    }


    parser_ptr regex_grammar(const parser_ptr& delimiter_parser, std::regex::flag_type flags) {
        return std::make_shared<regex_grammar_parser>(delimiter_parser, flags);
    }


    wregex_grammar_parser::wregex_grammar_parser(const parser_ptr& delimiter_parser, std::wregex::flag_type flags)
        : m_delimiter_parser(delimiter_parser)
        , m_flags(flags)
    {
    }


    bool wregex_grammar_parser::parse(parse_context& pc) const {
        return _parse<std::wregex>(pc, m_flags, m_delimiter_parser);
    }


    parser_ptr wregex_grammar(const parser_ptr& delimiter_parser, std::wregex::flag_type flags) {
        return std::make_shared<wregex_grammar_parser>(delimiter_parser, flags);
    }


} //namespace xparserlib
