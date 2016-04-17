#ifndef JBI_INTERPRETER_TYPE_H
#define JBI_INTERPRETER_TYPE_H

#include <cstddef>

namespace jbi
{

    class type
    {
    private:
        enum class class_
        {
            integer,
            floating_point
        };

        class_          _class;
        std::size_t     _size;

    public:
        bool equals(const type& other) const
        {
            return _class == other._class && _size == other._size;
        }

        static type int_()      { return type(class_::integer, sizeof(int)); }
        static type double_()   { return type(class_::floating_point, sizeof(double)); }

        static type common_type(const type& first, const type& second);

    private:
        type(class_ cls, std::size_t size)
            : _class(cls), _size(size)
        { }
    };

    inline bool operator==(const type& left, const type& right)
    {
        return left.equals(right);
    }

    inline bool operator!=(const type& left, const type& right)
    {
        return !(left == right);
    }

}

#endif
