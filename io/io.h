#if !defined(PITO_IO_H)
#define PITO_IO_H

#include <string_view>
#include <optional>

namespace arena
{
    void print_line(const std::string_view str);

    // optional aqui é overkill porque 0 é um sentinela
    // válido nesse caso mas vou usar só pq sim
    std::optional<int> print_and_get_choices(
                const std::string_view title, 
                const std::string_view options,
                char separator='*'
            );
}

#endif
