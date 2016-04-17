#ifndef JBI_INTERPRETER_LEXER_TOKEN_H
#define JBI_INTERPRETER_LEXER_TOKEN_H

#include <jbi/variant/variant.h>

namespace jbi
{

    enum class token_tag
    {
        var,
        in,
        out,
        print,

        integer,
        float_,
        string,

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
        token_tag tag() const       { return _tag; }
        token_value value() const   { return _value; }

        bool equals(const token& other) const
        {
            return _tag == other._tag && _value == other._value;
        }

        static token var()      { return token(token_tag::var); }
        static token in()       { return token(token_tag::in); }
        static token out()      { return token(token_tag::out); }
        static token print()    { return token(token_tag::print); }

        static token number(int number)                 { return token(token_tag::integer, number); }
        static token number(double number)              { return token(token_tag::float_, number); }
        static token string(const std::string& string)  { return token(token_tag::string, string); }

        static token identifier(const std::string& identifier)
        {
            JBI_THROW_IF(identifier.empty(), argument_exception());
            return token(token_tag::identifier, identifier);
        }

        static token arrow()                { return token(token_tag::arrow); }

        static token equals()               { return token(token_tag::symbol, '='); }
        static token plus()                 { return token(token_tag::symbol, '+'); }
        static token minus()                { return token(token_tag::symbol, '-'); }
        static token asterisk()             { return token(token_tag::symbol, '*'); }
        static token slash()                { return token(token_tag::symbol, '/'); }
        static token carret()               { return token(token_tag::symbol, '^'); }
        static token comma()                { return token(token_tag::symbol, ','); }
        static token left_parenthesis()     { return token(token_tag::symbol, '('); }
        static token right_parenthesis()    { return token(token_tag::symbol, ')'); }
        static token left_brace()           { return token(token_tag::symbol, '{'); }
        static token right_brace()          { return token(token_tag::symbol, '}'); }

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
