#include <cstdlib>
#include <iostream>
#include <limits>
#include "io.h"

namespace arena
{
    static void clear_input()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void clear_output()
    {
        std::cout << std::flush;
        std::system("cls");
    }

    void print_line(const std::string_view str)
    {
        std::cout << str << '\n';
    }

    // no containers were taught until chap 12
    // options separated by *
    std::optional<int> print_and_get_choices(
            const std::string_view title, 
            const std::string_view options,
            char separator
        )
    {
        using uint=unsigned int;
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
            if (low < sz - 1)
            {
                std::cout << ++n << ". " 
                    << options.substr(low, sz - low) << '\n';
            }

            std::cout << "Choose your option: ";
            std::cin >> buffer;
            
            clear_output(); // after choice

            if (!std::cin)
            {
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
}
