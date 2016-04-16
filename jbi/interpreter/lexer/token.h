#ifndef JBI_INTERPRETER_LEXER_TOKEN_H
#define JBI_INTERPRETER_LEXER_TOKEN_H

#include <jbi/core/none.h>
#include <jbi/variant/variant.h>

namespace jbi
{

    enum class token_tag
    {
        equals,

        plus,
        minus,
        times,
        slash,

        integer,
        float_,

        identifier
    };

    using token_value = variant<int, double, std::string, none_t>;

    class token
    {
    private:
        token_tag     _tag;
        token_value   _value;

    public:
        token(token_tag tag)
            : _tag(tag), _value(none)
        { }

        template < typename T >
        token(token_tag tag, T&& value)
            : _tag(tag), _value(std::forward<T>(value))
        { }

        token_tag tag() const { return _tag; }
        token_value value() const { return _value; }

        static token equals() { return token(token_tag::equals); }

        static token plus() { return token(token_tag::plus); }
        static token minus() { return token(token_tag::minus); }
        static token times() { return token(token_tag::times); }
        static token slash() { return token(token_tag::slash); }

        static token number(int number) { return token(token_tag::integer, number); }
        static token number(double number) { return token(token_tag::float_, number); }

        static token identifier(const std::string& identifier)
        {
            JBI_THROW_IF(identifier.empty(), argument_exception());
            return token(token_tag::identifier, identifier);
        }
    };

}

#endif
