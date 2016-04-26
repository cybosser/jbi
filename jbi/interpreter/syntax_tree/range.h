#ifndef JBI_INTERPRETER_SYNTAX_TREE_RANGE_H
#define JBI_INTERPRETER_SYNTAX_TREE_RANGE_H

#include <jbi/interpreter/syntax_tree/expression.h>

namespace jbi
{

    class range : public expression
    {
    private:
        std::unique_ptr<expression> _start;
        std::unique_ptr<expression> _stop;

    public:
        range(std::unique_ptr<expression> start, std::unique_ptr<expression> stop)
            : _start(std::move(start)), _stop(std::move(stop))
        {
            JBI_THROW_IF(!_start, argument_exception("start"));
            JBI_THROW_IF(!_stop, argument_exception("stop"));
        }

        const std::unique_ptr<expression>& start() const noexcept { return _start; }
        const std::unique_ptr<expression>& stop() const noexcept { return _stop; }

        JBI_DEFINE_VISITABLE(range);
    };

}

#endif
