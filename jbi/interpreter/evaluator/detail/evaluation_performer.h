#ifndef JBI_INTERPRETER_EVALUATOR_DETAIL_EVALUATION_PERFORMER_H
#define JBI_INTERPRETER_EVALUATOR_DETAIL_EVALUATION_PERFORMER_H

#include <jbi/interpreter/iterminal.h>
#include <jbi/interpreter/symbol_table.h>
#include <jbi/interpreter/syntax_tree/visitor.h>

namespace jbi
{
    namespace detail
    {

        class evaluation_performer : public jbi::syntax_tree_visitor<value>
        {
        private:
            std::shared_ptr<symbol_table>   _symbols;
            std::shared_ptr<iterminal>      _terminal;

        public:
            explicit evaluation_performer(std::shared_ptr<iterminal> terminal);

            value operator()(const jbi::assignment_statement& var);
            value operator()(const jbi::output_statement& out);

            value operator()(const jbi::arithmetic_operator& op);

            template < typename T >
            value operator()(const jbi::numeric_literal<T>& literal) const
            {
                return literal.value();
            }

            value operator()(const jbi::identifier& id) const;
        };

    }
}

#endif
