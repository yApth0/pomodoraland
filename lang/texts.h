#if !defined(PITO_TEXTS_H)
#define PITO_TEXTS_H

#include <string_view>

namespace arena::dialog
{
    inline constexpr std::string_view titlecard {
    "████   ███  █   █  ███  ████   ███  ████   ███  █      ███  █   █ ████    \n\
█░░░█ █ ░░█ ██ ██░█ ░░█ █░░░█ █ ░░█ █░░░█ █ ░░█ █░    █ ░░█ ██  █░█░░░█   \n\
████░░█░ ░█░█░█ █░█░ ░█░█░░░█░█░ ░█░████░░█████░█░░   █████░█░█ █░█░░░█░  \n\
█░░░░ █░░ █░█░░░█░█░░ █░█░░ █░█░░ █░█░░█░ █░░░█░█░░   █░░░█░█░░██░█░░ █░░ \n\
█░░░░░ ███ ░█░░ █░░███ ░████ ░░███ ░█░░░█░█░░░█░█████ █░░░█░█░░ █░████ ░░ \n\
 ░░     ░░░ ░░░  ░░ ░░░ ░░░░░ ░ ░░░ ░░░  ░ ░░  ░░░░░░░ ░░  ░░░░  ░░░░░░ ░ \n\
  ░      ░░░  ░   ░  ░░░  ░░░░   ░░░  ░   ░ ░   ░ ░░░░░ ░   ░ ░   ░ ░░░░  "};

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

    // Difficulty
    inline constexpr std::string_view difficulty_title{
        "Choose your desired difficulty"
    };

    inline constexpr std::string_view difficulty_options{
        "Easy (full life)*Medium (75% life)*Hard (50% life)"
    };

    // Combat
    inline constexpr std::string_view combat_title {
        "Your turn."
    };
    inline constexpr std::string_view combat_options {
        "Basic attack*Heavy attack*Defend*Breathe*Use potion*Inspect*Surrender"
    };

    inline constexpr std::string_view inspect_text {
        "Inspecting enemy stats."
    };

    // prize screen
    inline constexpr std::string_view prize_title {
        "You won! Select a buff for the next fight."
    };

    inline constexpr std::string_view prize_options {
        "Restore health*Increase attack damage*Increase potion count"
    };

    // Terminal stuff
    inline constexpr std::string_view input_tip {
        "$> "
    };
}
#endif
