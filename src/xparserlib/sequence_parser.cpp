#include "xparserlib/sequence_parser.hpp"
#include "xparserlib/symbol_parser.hpp"
#include "xparserlib/string_parser.hpp"
#include "xparserlib/rule.hpp"
#include "vector.hpp"


namespace xparserlib {


    sequence_parser::sequence_parser(const parsers_type& parsers)
        : m_parsers(parsers)
    {
    }


    bool sequence_parser::parse(parse_context& pc) const {
        const auto start_state = pc.state();
        for (const parser_ptr& parser : m_parsers) {
            if (!parser->parse(pc)) {
                pc.set_state(start_state);
                return false;
            }
        }
        return true;
    }


    const parsers_type& sequence_parser::parsers() const {
        return m_parsers;
    }



    /* left: parser_ptr */


    parser_ptr operator >> (const parser_ptr& left, const parser_ptr& right) {
        sequence_parser* l = dynamic_cast<sequence_parser*>(left.get());
        sequence_parser* r = dynamic_cast<sequence_parser*>(right.get());
        if (l && r) {
            return std::make_shared<sequence_parser>(l->parsers() + r->parsers());
        }
        if (l) {
            return std::make_shared<sequence_parser>(l->parsers() + right);
        }
        if (r) {
            return std::make_shared<sequence_parser>(left + r->parsers());
        }
        return std::make_shared<sequence_parser>(parsers_type{left, right});
    }


    parser_ptr operator >> (const parser_ptr& left, symbol_type right) {
        sequence_parser* l = dynamic_cast<sequence_parser*>(left.get());
        if (l) {
            return std::make_shared<sequence_parser>(l->parsers() + parser(right));
        }
        return std::make_shared<sequence_parser>(parsers_type{ left, parser(right) });
    }


    parser_ptr operator >> (const parser_ptr& left, const string_type& right) {
        sequence_parser* l = dynamic_cast<sequence_parser*>(left.get());
        if (l) {
            return std::make_shared<sequence_parser>(l->parsers() + parser(right));
        }
        return std::make_shared<sequence_parser>(parsers_type{ left, parser(right) });
    }


    parser_ptr operator >> (const parser_ptr& left, rule& right) {
        sequence_parser* l = dynamic_cast<sequence_parser*>(left.get());
        if (l) {
            return std::make_shared<sequence_parser>(l->parsers() + parser(right));
        }
        return std::make_shared<sequence_parser>(parsers_type{ left, parser(right) });
    }


    /* left: symbol_type */


    parser_ptr operator >> (symbol_type left, const parser_ptr& right) {
        sequence_parser* r = dynamic_cast<sequence_parser*>(right.get());
        if (r) {
            return std::make_shared<sequence_parser>(parser(left) + r->parsers());
        }
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), right });
    }


    parser_ptr operator >> (symbol_type left, const string_type& right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator >> (symbol_type left, rule& right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    /* left: string_type */


    parser_ptr operator >> (const string_type& left, const parser_ptr& right) {
        sequence_parser* r = dynamic_cast<sequence_parser*>(right.get());
        if (r) {
            return std::make_shared<sequence_parser>(parser(left) + r->parsers());
        }
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), right });
    }


    parser_ptr operator >> (const string_type& left, symbol_type right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator >> (const string_type& left, const string_type& right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator >> (const string_type& left, rule& right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    /* left: rule */


    parser_ptr operator >> (rule& left, const parser_ptr& right) {
        sequence_parser* r = dynamic_cast<sequence_parser*>(right.get());
        if (r) {
            return std::make_shared<sequence_parser>(parser(left) + r->parsers());
        }
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), right });
    }


    parser_ptr operator >> (rule& left, symbol_type right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator >> (rule& left, const string_type& right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator >> (rule& left, rule& right) {
        return std::make_shared<sequence_parser>(parsers_type{ parser(left), parser(right) });
    }


    parser_ptr operator - (const parser_ptr& left, const parser_ptr& right) {
        return !right >> left;
    }


    parser_ptr operator - (const parser_ptr& left, rule& right) {
        return !right >> left;
    }


    parser_ptr operator - (rule& left, const parser_ptr& right) {
        return !right >> left;
    }


    parser_ptr operator - (rule& left, rule& right) {
        return !right >> left;
    }


} //namespace xparserlib
