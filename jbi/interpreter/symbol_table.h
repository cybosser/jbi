#ifndef JBI_INTERPRETER_SYMBOL_TABLE_H
#define JBI_INTERPRETER_SYMBOL_TABLE_H

#include <jbi/interpreter/types/value.h>

#include <unordered_map>

namespace jbi
{

    class symbol_table
    {
    private:
       std::unordered_map<std::string, value> _symbols;

    public:
        template < typename Identifier, typename Value >
        void set(Identifier&& identifier, Value&& value_)
        {
            _symbols[std::forward<Identifier>(identifier)] = std::forward<Value>(value_);
        }

        const value& get(const std::string& identifier) const;
        bool contains(const std::string& identifier) const;
    };

}

#endif
