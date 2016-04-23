#include <jbi/interpreter/symbol_table.h>

namespace jbi
{

    const value& symbol_table::get(const std::string& identifier) const
    {
        const auto position = _symbols.find(identifier);
        JBI_THROW_IF(position == _symbols.end(), argument_exception("identifier"));
        return position->second;
    }

    bool symbol_table::contains(const std::string& identifier) const
    {
        return _symbols.find(identifier) != _symbols.end();
    }

}