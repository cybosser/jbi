#ifndef JBI_INTERPRETER_TYPES_NUMERIC_RANGE_H
#define JBI_INTERPRETER_TYPES_NUMERIC_RANGE_H

#include <jbi/core/exceptions.h>

#include <iterator>

namespace jbi
{

    template < typename T >
    class numeric_range
    {
    private:
        class range_iterator : public std::iterator<std::input_iterator_tag, const T>
        {
            using base = std::iterator<std::input_iterator_tag, const T>;

        private:
            T _start;
            T _stop;
            T _current;

        public:
            range_iterator(T start, T stop, T current) noexcept
                : _start(start), _stop(stop), _current(current)
            { }

            typename base::reference operator*()
            {
                check_validity();
                return _current;
            }

            typename base::pointer operator->()
            {
                check_validity();
                return std::addressof(_current);
            }

            range_iterator& operator++() noexcept
            {
                ++_current;
                return *this;
            }

            range_iterator operator++(int) noexcept
            {
                range_iterator result(*this);
                operator++();
                return result;
            }

            bool operator==(const range_iterator& other) const noexcept
            {
                return _start == other._start && _stop == other._stop && _current == other._current;
            }

            bool operator!=(const range_iterator& other) const noexcept
            {
                return !(*this == other);
            }

        private:
            void check_validity()
            {
                JBI_THROW_UNLESS(_current < _stop, invalid_operation_exception("Iterator is invalid"));
            }
        };

        T _start;
        T _stop;

    public:
        using iterator = range_iterator;

        numeric_range(T begin, T end)
            : _start(begin), _stop(end)
        {
            JBI_THROW_IF(_start > _stop, argument_exception("stop"));
        }

        T start() const noexcept { return _start; }
        T stop() const noexcept { return _stop; }

        iterator begin() const noexcept { return iterator(_start, _stop, _start); }
        iterator end() const noexcept { return iterator(_start, _stop, _stop); }
    };

}

#endif
