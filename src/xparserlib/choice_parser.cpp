#include "xparserlib/choice_parser.hpp"
#include "xparserlib/symbol_parser.hpp"
#include "xparserlib/string_parser.hpp"
#include "xparserlib/rule.hpp"
#include "vector.hpp"


namespace xparserlib {


    choice_parser::choice_parser(const parsers_type& parsers)
        : m_parsers(parsers)
    {
    }


    bool choice_parser::parse(parse_context& pc) const {
        for (const parser_ptr& parser : m_parsers) {
            const auto start_state = pc.state();
            if (parser->parse(pc)) {
                return true;
            }
            pc.set_state(start_state);
        }
        return false;
    }


    const parsers_type& choice_parser::parsers() const {
        return m_parsers;
    }



    /* left: parser_ptr */


    parser_ptr operator | (const parser_ptr& left, const parser_ptr& right) {
        choice_parser* l = dynamic_cast<choice_parser*>(left.get());
        choice_parser* r = dynamic_cast<choice_parser*>(right.get());
        if (l && r) {
            return std::make_shared<choice_parser>(l->parsers() + r->parsers());
        }
        if (l) {
            return std::make_shared<choice_parser>(l->parsers() + right);
        }
        if (r) {
            return std::make_shared<choice_parser>(left + r->parsers());
        }
        return std::make_shared<choice_parser>(parsers_type{ left, right });
    }


    parser_ptr operator | (const parser_ptr& left, symbol_type right) {
        choice_parser* l = dynamic_cast<choice_parser*>(left.get());
        if (l) {
            return std::make_shared<choice_parser>(l->parsers() + parser(right));
        }
        return std::make_shared<choice_parser>(parsers_type{ left, parser(right) });
    }


    parser_ptr operator | (const parser_ptr& left, const string_type& right) {
        choice_parser* l = dynamic_cast<choice_parser*>(left.get());
        if (l) {
            return std::make_shared<choice_parser>(l->parsers() + parser(right));
        }
        return std::make_shared<choice_parser>(parsers_type{ left, parser(right) });
    }


    parser_ptr operator | (const parser_ptr& left, rule& right) {
        choice_parser* l = dynamic_cast<choice_parser*>(left.get());
        if (l) {
            return std::make_shared<choice_parser>(l->parsers() + parser(right));
        }
        return std::make_shared<choice_parser>(parsers_type{ left, parser(right) });
    }


    /* left: symbol_type */


    parser_ptr operator | (symbol_type left, const parser_ptr& right) {
        choice_parser* r = dynamic_cast<choice_parser*>(right.get());
        if (r) {
            return std::make_shared<choice_parser>(parser(left) + r->parsers());
        }
        return std::make_shared<choice_parser>(parsers_type{ parser(left), right });
    }


    parser_ptr operator | (symbol_type left, const string_type& right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator | (symbol_type left, rule& right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


    /* left: string_type */


    parser_ptr operator | (const string_type& left, const parser_ptr& right) {
        choice_parser* r = dynamic_cast<choice_parser*>(right.get());
        if (r) {
            return std::make_shared<choice_parser>(parser(left) + r->parsers());
        }
        return std::make_shared<choice_parser>(parsers_type{ parser(left), right });
    }


    parser_ptr operator | (const string_type& left, symbol_type right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator | (const string_type& left, const string_type& right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator | (const string_type& left, rule& right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


    /* left: rule */


    parser_ptr operator | (rule& left, const parser_ptr& right) {
        choice_parser* r = dynamic_cast<choice_parser*>(right.get());
        if (r) {
            return std::make_shared<choice_parser>(parser(left) + r->parsers());
        }
        return std::make_shared<choice_parser>(parsers_type{ parser(left), right });
    }


    parser_ptr operator | (rule& left, symbol_type right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator | (rule& left, const string_type& right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator | (rule& left, rule& right) {
        return std::make_shared<choice_parser>(parsers_type{ parser(left), parser(right) });
    }


} //namespace xparserlib
