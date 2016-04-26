#ifndef JBI_INTERPRETER_EVALUATOR_DETAIL_EVALUATION_PERFORMER_H
#define JBI_INTERPRETER_EVALUATOR_DETAIL_EVALUATION_PERFORMER_H

#include <jbi/interpreter/evaluator/detail/value_printer.h>
#include <jbi/interpreter/symbol_table.h>
#include <jbi/interpreter/syntax_tree/visitor.h>

namespace jbi
{
    namespace detail
    {

        class evaluation_performer : public syntax_tree_visitor<value>
        {
        private:
            std::shared_ptr<iterminal>  _terminal;
            value_printer               _printer;
            symbol_table                _symbols;

        public:
            explicit evaluation_performer(std::shared_ptr<iterminal> terminal);

            value operator()(const declaration_statement& var);
            value operator()(const output_statement& out);
            value operator()(const input_statement& in);

            value operator()(const arithmetic_operator& op);

            template < typename T >
            value operator()(const numeric_literal<T>& literal) const
            {
                return literal.value();
            }

            value operator()(const identifier& id) const;
            value operator()(const range& range);

        private:
            void expect_undeclared(const std::string &identifier) const;
            void expect_declared(const std::string &identifier) const;
        };

    }
}

#endif
