#ifndef JBI_CORE_EXCEPTIONS_H
#define JBI_CORE_EXCEPTIONS_H

// TODO store context (__FILE__, __LINE__, etc.)
#define JBI_THROW(...) \
    throw __VA_ARGS__

#endif
