#ifndef JBI_INTERPRETER_ARITHMETIC_OPERATION_H
#define JBI_INTERPRETER_ARITHMETIC_OPERATION_H

#include <jbi/core/exceptions.h>
#include <jbi/core/utility.h>

namespace jbi
{

    class arithmetic_operation
    {
    private:
        char    _symbol;

    public:
        bool equals(const arithmetic_operation& other) const noexcept
        {
            return _symbol == other._symbol;
        }

        static arithmetic_operation addition() noexcept         { return arithmetic_operation('+'); }
        static arithmetic_operation subtraction() noexcept      { return arithmetic_operation('-'); }
        static arithmetic_operation multiplication() noexcept   { return arithmetic_operation('*'); }
        static arithmetic_operation division() noexcept         { return arithmetic_operation('/'); }
        static arithmetic_operation exponentiation() noexcept   { return arithmetic_operation('^'); }

        static arithmetic_operation from_symbol(char symbol)
        {
            JBI_THROW_IF(!is_one_of(symbol, '+', '-', '*', '/', '^'), argument_exception("symbol"));
            return arithmetic_operation(symbol);
        }

        std::string to_string() const { return jbi::to_string(_symbol); }

    private:
        arithmetic_operation(char symbol) noexcept
            : _symbol(symbol)
        { }
    };

    inline bool operator==(const arithmetic_operation& left, const arithmetic_operation& right) noexcept
    {
        return left.equals(right);
    }

    inline bool operator!=(const arithmetic_operation& left, const arithmetic_operation& right) noexcept
    {
        return !(left == right);
    }

}

#endif
