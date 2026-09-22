#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <format>
#include <limits>
#include "../lang/texts.h"
#include "io.h"

namespace arena::io
{
    using uint=unsigned int;
    const uint MAX_NAME_SIZE = 16;

    static void clear_input()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    extern void clear_output()
    {
        std::cout << std::flush;
        std::system("cls");
    }

    extern void print_line(std::string_view str)
    {
        std::cout << str << '\n';
    }

    extern void print_colored(std::string_view str, bool newline)
    {
        std::cout << "\e[91m";
        std::cout << str;
        std::cout << "\e[0m";
        if (newline)
            std::cout << '\n';
    }

    extern void log_and_print(std::string& log, const std::string& str)
    {
        log += str;
        log += '\n';
        print_line(str);
    }

    extern void pause_buffer()
    {
        std::cout << std::flush;
        std::system("pause");
    }

    extern std::string build_ui(
        int16_t health,
        int16_t stamina,
        int16_t potions,
        std::string_view name,
        std::string_view msg
    ) 
    {
        return std::format(
                "{} [{}] {} HP / {} STA / {} POT",
                msg,
                name,
                health,
                stamina,
                potions
                );
    }

    // no containers were taught until chap 12
    // options separated by *
    [[nodiscard]] std::optional<int16_t> print_and_get_choices(
            const std::string_view title, 
            const std::string_view options,
            char separator
        )
    {
        const uint sz{static_cast<uint>(options.length())};
        uint lower_bound{};

        // check options
        bool found{false};
        for (uint idx{}; idx < sz; ++idx)
        {
            if (options.at(idx) != separator)
            {
                found = true;
                lower_bound = idx;
                break;
            }
        }

        if (!found)
            return {};

        while (true)
        {
            std::cout << title << '\n';
            uint buffer{}, low{lower_bound};
            uint n{};
            for (uint idx{}; idx < sz; idx++)
            {
                if (idx > 0 && options.at(idx) == separator)
                {
                    if (options.at(idx - 1) != separator)
                    {
                        std::cout << ++n << ". " 
                            << options.substr(low, idx - low) << '\n';
                    }
                    low = idx + 1;
                }
            }
            if (low < sz)
            {
                std::cout << ++n << ". " 
                    << options.substr(low, sz - low) << '\n';
            }

            std::cout << arena::dialog::input_tip;
            std::cin >> buffer;
            
            clear_output(); // after choice

            if (!std::cin)
            {
                if (std::cin.eof())
                {
                    std::cout << "EOF reached too soon!";
                    std::exit(1);
                }

                clear_input();
                std::cout << "Invalid choice, try again.\n";
                continue;
            }
            clear_input();
            if (buffer > 0 && buffer <= n)
            {
                return buffer;
            }
            std::cout << "Invalid choice, try again.\n";
        }

    }

    extern std::string get_name()
    {
        std::string buffer{};
        while (true)
        {
            std::cout << "Type your character's name\n";
            std::cout << arena::dialog::input_tip;
            std::getline(std::cin >> std::ws, buffer);

            clear_output();

            if (!std::cin)
            { 
                if (std::cin.eof())
                {
                    std::cout << "EOF reached too soon!";
                    std::exit(1);
                }

                clear_input();
                std::cout << "Something went wrong. Try again!\n";
                continue;
            }

            // check max length 
            if (buffer.length() >= MAX_NAME_SIZE)
            {
                std::cout << "Character's name is too long, try again!\n";
                continue;
            }
            
            // check numbers
            bool found{false};
            for (uint i{}; i < buffer.length(); ++i)
            {
                if (buffer.at(i) >= '0' && buffer.at(i) <= '9')
                {
                    std::cout << "Character's name cannot contain numbers, try again!\n";
                    found = true;
                    break;
                }
            }

            if (found)
                continue;

            return buffer;
        }
    }
}
