#ifndef JBI_INTERPRETER_TYPES_NONE_H
#define JBI_INTERPRETER_TYPES_NONE_H

namespace jbi
{

    struct none_t
    { };

    extern const none_t none;

    bool operator==(const none_t&, const none_t&) noexcept;
    bool operator!=(const none_t&, const none_t&) noexcept;

}

#endif
