#ifndef JBI_INTERPRETER_LEXICAL_ANALYSER_TOKEN_H
#define JBI_INTERPRETER_LEXICAL_ANALYSER_TOKEN_H

#include <jbi/variant/variant.h>

namespace jbi
{

    enum class token_tag
    {
        builtin,

        integer_literal,
        floating_literal,
        string_literal,

        identifier,

        arrow,

        symbol,

        eof
    };

    using token_value = variant<char, int, double, std::string>;

    class token
    {
    private:
        token_tag     _tag;
        token_value   _value;

    public:
        token_tag tag() const noexcept               { return _tag; }
        const token_value& value() const noexcept   { return _value; }

        bool equals(const token& other) const
        {
            return _tag == other._tag && _value == other._value;
        }

        static token var()      { return builtin("var"); }
        static token in()       { return builtin("in"); }
        static token out()      { return builtin("out"); }
        static token print()    { return builtin("print"); }

        static token literal(int number)                 { return token(token_tag::integer_literal, number); }
        static token literal(double number)              { return token(token_tag::floating_literal, number); }
        static token literal(const std::string& string)  { return token(token_tag::string_literal, string); }

        static token identifier(const std::string& identifier)
        {
            JBI_THROW_IF(identifier.empty(), argument_exception("identifier"));
            return token(token_tag::identifier, identifier);
        }

        static token arrow()                { return token(token_tag::arrow); }

        static token equals()               { return symbol('='); }
        static token plus()                 { return symbol('+'); }
        static token minus()                { return symbol('-'); }
        static token asterisk()             { return symbol('*'); }
        static token slash()                { return symbol('/'); }
        static token carret()               { return symbol('^'); }
        static token comma()                { return symbol(','); }
        static token left_parenthesis()     { return symbol('('); }
        static token right_parenthesis()    { return symbol(')'); }
        static token left_brace()           { return symbol('{'); }
        static token right_brace()          { return symbol('}'); }

        // TODO find better solution
        static token eof()                  { return token(token_tag::eof); }

    private:
        token()
        { }

        token(token_tag tag)
            : _tag(tag)
        { }

        template < typename T >
        token(token_tag tag, T&& value)
            : _tag(tag), _value(std::forward<T>(value))
        { }

        static token builtin(const std::string& keyword)    { return token(token_tag::builtin, keyword); }
        static token symbol(char symbol)                    { return token(token_tag::symbol, symbol); }
    };

    inline bool operator==(const token& left, const token& right)
    {
        return left.equals(right);
    }

    inline bool operator!=(const token& left, const token& right)
    {
        return !(left == right);
    }

}

#endif
