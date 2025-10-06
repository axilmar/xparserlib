#ifndef XPARSERLIB_RULE_HPP
#define XPARSERLIB_RULE_HPP


#include "parser.hpp"
#include <initializer_list>


namespace xparserlib {


    /**
     * Represents a production rule.
     * Rules are managed via references, and therefore can be recursive.
     */
    class rule {
    public:
        /**
         * The default constructor.
         * An empty, nameless rule object is constructed.
         */
        rule();

        /**
         * The copy constructor.
         * @param r source object.
         */
        rule(const rule& r);

        /**
         * The move constructor.
         * @param r source object.
         */
        rule(rule&& r);

        /**
         * Constructor from parser.
         * @param parser the parser to use for parsing.
         */
        rule(const parser_ptr& parser);

        /**
         * Constructor from symbol.
         * @param symbol symbol.
         */
        rule(symbol_type symbol);

        /**
         * Constructor from string.
         * @param string string.
         */
        rule(const char* string);

        /**
         * Constructor from string.
         * @param string string.
         */
        rule(const wchar_t* string);

        /**
         * Constructor from string.
         * @param string string.
         */
        rule(const string_type& string);

        /**
         * Constructor from string.
         * @param string string.
         */
        rule(const std::initializer_list<symbol_type>& string);

        /**
         * Constructor from boolean.
         * @param value boolean value.
         */
        rule(bool value);

        /**
         * Constructor from name and parser.
         * @param parser the parser to use for parsing.
         */
        rule(const std::string& name, const parser_ptr& parser);

        /**
         * Constructor from name and symbol.
         * @param symbol symbol.
         */
        rule(const std::string& name, symbol_type symbol);

        /**
         * Constructor from name and string.
         * @param string string.
         */
        rule(const std::string& name, const char* string);

        /**
         * Constructor from name and string.
         * @param string string.
         */
        rule(const std::string& name, const wchar_t* string);

        /**
         * Constructor from name and string.
         * @param string string.
         */
        rule(const std::string& name, const string_type& string);

        /**
         * Constructor from name and string.
         * @param string string.
         */
        rule(const std::string& name, const std::initializer_list<symbol_type>& string);

        /**
         * Constructor from name and boolean.
         * @param value boolean value.
         */
        rule(const std::string& name, bool value);

        /**
         * Assignment from parser.
         * @param parser the parser to use for parsing.
         * @return reference to this.
         */
        rule& operator = (const parser_ptr& parser);

        /**
         * Copy-assignment from rule.
         * @param r the source object.
         * @return reference to this.
         */
        rule& operator = (const rule& r);

        /**
         * move-assignment from rule.
         * @param r the source object.
         * @return reference to this.
         */
        rule& operator = (rule&& r);

        /**
         * Creates a zero or more times loop out of this rule.
         * @return a zero or more times loop out of this rule.
         */
        parser_ptr operator *();

        /**
         * Creates a one or more times loop out of this rule.
         * @return a one or more times loop out of this rule.
         */
        parser_ptr operator +();

        /**
         * Makes this rule optional.
         * @return an optional parser for this rule.
         */
        parser_ptr operator -();

        /**
         * Creates a logical and parser from this rule.
         * @return a logical and parser from this rule.
         */
        parser_ptr operator &();

        /**
         * Creates a logical not parser from this rule.
         * @return a logical not parser from this rule.
         */
        parser_ptr operator !();

        /**
         * Invokes the internal parser.
         * @param pc parse context.
         * @return whatever the internal parser returns.
         */
        bool parse(parse_context& pc) const;

        /**
         * Returns the rule's name.
         * @return the rule's name.
         */
        const std::string& name() const;

        /**
         * Returns the rule's address.
         * @return the rule's address.
         */
        rule* addr();

    private:
        std::string m_name;
        parser_ptr m_parser;
    };


    /**
     * Creates a parser for a rule.
     * @param rule rule to create a parser from.
     */
    parser_ptr parser(class rule& rule);


} //namespace xparserlib


#endif //XPARSERLIB_RULE_HPP
