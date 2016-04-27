#ifndef JBI_INTERPRETER_EVALUATOR_EXPRESSION_EVALUATOR_H
#define JBI_INTERPRETER_EVALUATOR_EXPRESSION_EVALUATOR_H

#include <jbi/interpreter/symbol_table.h>
#include <jbi/interpreter/syntax_tree/visitor.h>

namespace jbi
{

    class expression_evaluator : public expression_visitor<value>
    {
    private:
        std::shared_ptr<symbol_table> _symbols;

    public:
        explicit expression_evaluator(std::shared_ptr<symbol_table> symbols);

        value operator()(const arithmetic_operator& op);

        template < typename T >
        value operator()(const numeric_literal<T>& literal) const
        {
            return literal.value();
        }

        value operator()(const identifier& id) const;
        value operator()(const range& range);
    };

};

#endif
