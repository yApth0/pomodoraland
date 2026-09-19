#if !defined(PITO_TEXTS_H)
#define PITO_TEXTS_H

#include <string_view>

namespace arena::dialog
{
    // Rules
    inline constexpr std::string_view rules {
        "You are a brave soldier who arrived in Pomodora land to participate on a\
 annual tournament. Pomodora kingdom magesty, King Thomato, is offering\
 his crown to whoever can challenge his soldiers on a bloody tournament.\
 After all, you must defeat his strongest soldier, Khet-choup. Can you take\
 the challenge? 3 soldiers, 1 boss.\n"
    };

    // Exit msg
    inline constexpr std::string_view exit_msg {
        "Goodbye."
    };

    // Menu
    inline constexpr std::string_view menu_title {
        "Welcome to Pomodora Arena. What do you want to do?"
    };
    inline constexpr std::string_view menu_options {
        "Read the rules*Play*Exit"
    };

    // Combat
    inline constexpr std::string_view combat_title {
        "Your turn."
    };
    inline constexpr std::string_view combat_options {
        "Basic attack*Heavy attack*Defend*Breathe*Use potion*Inspect*Surrender"
    };
}
#endif
