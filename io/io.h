#if !defined(PITO_IO_H)
#define PITO_IO_H

#include <string_view>
#include <cstdint>
#include <optional>
#include <string>

namespace arena::io
{
    extern void clear_output();
    extern void pause_buffer();
    extern void print_line(std::string_view str);
    extern void print_colored(std::string_view str, bool newline=true);
    extern void log_and_print(std::string& log, const std::string& str);
    
    extern std::string build_ui(
        int16_t health,
        int16_t stamina,
        int16_t potions,
        std::string_view name, 
        std::string_view msg);

    // optional aqui é overkill porque 0 é um sentinela
    // válido nesse caso mas vou usar só pq sim
    [[nodiscard]] extern std::optional<int16_t> print_and_get_choices(
        const std::string_view title, 
        const std::string_view options,
        char separator='*'
    );

    extern std::string get_name();
}

#endif
