#include <cassert>
#include <cstdint>
#include <optional>
#include "lang/texts.h"
#include "io/io.h"
#include "arena/arena.h"

using namespace arena;

namespace arena::menu
{
    constexpr int16_t opt_rules {1};
    constexpr int16_t opt_play {2};
    constexpr int16_t opt_exit {3};
}

int main()
{
    bool playing {true};
    while (playing)
    {
        io::clear_output();

        io::print_colored(arena::dialog::titlecard);

        std::optional<int> opts{
            io::print_and_get_choices(
                dialog::menu_title, 
                dialog::menu_options)
        };

        assert(opts > 0);

        switch(opts.value())
        {
            case menu::opt_rules:
            {
                io::clear_output();
                io::print_line(dialog::rules);
                io::pause_buffer();
                break;
            }
            case menu::opt_play:
            {
                std::string log = start_tournament();
                io::clear_output();
                io::print_colored("Battle log:");
                io::print_line(log);
                io::pause_buffer();
                break;
            }
            case menu::opt_exit:
            {
                io::print_line(dialog::exit_msg);
                playing = false;
            }
        }
    }
    return 0;
}
