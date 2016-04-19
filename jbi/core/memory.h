#ifndef JBI_CORE_MEMORY_H
#define JBI_CORE_MEMORY_H

#include <memory>

namespace jbi
{

    template < typename T, typename... Args >
    std::unique_ptr<T> make_unique(Args&&... args)
    {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    };

}

#endif
