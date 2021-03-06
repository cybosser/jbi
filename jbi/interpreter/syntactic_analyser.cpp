#include <jbi/interpreter/syntactic_analyser.h>

#include <jbi/core/memory.h>
#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/syntax_tree/arithmetic_operator.h>
#include <jbi/interpreter/syntax_tree/declaration_statement.h>
#include <jbi/interpreter/syntax_tree/identifier.h>
#include <jbi/interpreter/syntax_tree/input_statement.h>
#include <jbi/interpreter/syntax_tree/literals.h>
#include <jbi/interpreter/syntax_tree/output_statement.h>
#include <jbi/interpreter/syntax_tree/range.h>

#include <stack>

namespace jbi
{

    namespace
    {

        class token_source
        {
        private:
            lexical_analyser    _tokenizer;

            std::stack<token>   _pushed;

        public:
            explicit token_source(lexical_analyser tokenizer) noexcept
                : _tokenizer(std::move(tokenizer))
            { }

            token pop()
            {
                if (_pushed.empty())
                    return _tokenizer.read();

                token result = _pushed.top();
                _pushed.pop();
                return result;
            }

            void push(token token)
            {
                _pushed.emplace(std::move(token));
            }
        };

    }


    class syntactic_analyser::impl
    {
    private:
        token_source _tokens;

    public:
        explicit impl(lexical_analyser tokenizer) noexcept
            : _tokens(std::move(tokenizer))
        { }

        std::unique_ptr<statement> parse()
        {
            auto statement = parse_statement();
            JBI_THROW_IF(_tokens.pop() != token::eof(), syntax_exception("junk at end of line"));
            return statement;
        }

    private:
        std::unique_ptr<statement> parse_statement()
        {
            const token lookahead = _tokens.pop();

            if (lookahead == token::var())
                return parse_declaration_statement();

            if (lookahead == token::out())
                return make_unique<output_statement>(parse_expression());

            if (lookahead == token::in())
                return make_unique<input_statement>(parse_identifier());

            JBI_THROW(syntax_exception("missing statement"));
        }

        std::unique_ptr<statement> parse_declaration_statement()
        {
            const std::string identifier = parse_identifier();
            match_token(token::equals(), "missing =");
            return make_unique<declaration_statement>(identifier, parse_expression());
        }

        std::unique_ptr<expression> parse_expression()
        {
            auto expression = parse_term();

            token lookahead = _tokens.pop();

            for ( ; is_one_of(lookahead, token::plus(), token::minus()); lookahead = _tokens.pop())
            {
                const arithmetic_operation operation = arithmetic_operation::from_symbol(get<char>(lookahead.value()));
                expression = make_unique<arithmetic_operator>(operation, std::move(expression), parse_term());
            }

            _tokens.push(lookahead);

            return expression;
        }

        std::unique_ptr<expression> parse_term()
        {
            auto expression = parse_exponent();

            token lookahead = _tokens.pop();

            for ( ; is_one_of(lookahead, token::asterisk(), token::slash()); lookahead = _tokens.pop())
            {
                const arithmetic_operation operation = arithmetic_operation::from_symbol(get<char>(lookahead.value()));
                expression = make_unique<arithmetic_operator>(operation, std::move(expression), parse_exponent());
            }

            _tokens.push(lookahead);

            return expression;
        }

        std::unique_ptr<expression> parse_exponent()
        {
            auto expression = parse_factor();

            token lookahead = _tokens.pop();

            if (lookahead == token::carret())
            {
                const arithmetic_operation operation = arithmetic_operation::from_symbol(get<char>(lookahead.value()));
                return make_unique<arithmetic_operator>(operation, std::move(expression), std::move(parse_exponent()));
            }

            _tokens.push(lookahead);

            return expression;
        }

        std::unique_ptr<expression> parse_factor()
        {
            const token lookahead = _tokens.pop();

            if (lookahead.tag() == token_tag::integer_literal)
                return make_unique<integer_literal>(get<int>(lookahead.value()));

            if (lookahead.tag() == token_tag::floating_literal)
                return make_unique<floating_literal>(get<double>(lookahead.value()));

            if (lookahead.tag() == token_tag::identifier)
                return make_unique<identifier>(get<std::string>(lookahead.value()));

            if (lookahead == token::left_parenthesis())
            {
                auto result = parse_expression();
                match_token(token::right_parenthesis(), "missing )");
                return result;
            }

            if (lookahead == token::left_brace())
            {
                auto start = parse_expression();
                match_token(token::comma(), "missing ,");

                auto stop = parse_expression();
                match_token(token::right_brace(), "missing }");

                return make_unique<range>(std::move(start), std::move(stop));
            }

            JBI_THROW(syntax_exception("missing expression"));
        }

        std::string parse_identifier()
        {
            const token lookahead = _tokens.pop();
            JBI_THROW_IF(lookahead.tag() != token_tag::identifier, syntax_exception("missing identifier"));
            return get<std::string>(lookahead.value());
        }

        void match_token(token expected, const std::string& message)
        {
            JBI_THROW_IF(_tokens.pop() != expected, syntax_exception(message));
        }
    };

    syntactic_analyser::syntactic_analyser(lexical_analyser tokenizer) noexcept
        : _impl(new impl(std::move(tokenizer)))
    { }

    syntactic_analyser::~syntactic_analyser() = default;

    syntactic_analyser::syntactic_analyser(syntactic_analyser&&) noexcept = default;

    syntactic_analyser& syntactic_analyser::operator=(syntactic_analyser&&) noexcept = default;

    std::unique_ptr<statement> syntactic_analyser::parse()
    {
        return _impl->parse();
    }

}
