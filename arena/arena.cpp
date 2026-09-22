#include "../lang/texts.h"
#include "../io/io.h"
#include "arena.h"
#include "duel.h"
#include <cassert>
#include <optional>
#include <string_view>

namespace arena
{
    constexpr std::string_view boss1_name{"Arthus"};
    constexpr int16_t boss1_hm{};
    constexpr int16_t boss1_sm{};
    constexpr int16_t boss1_pm{};

    constexpr std::string_view boss2_name{"Don. Quitambo"};
    constexpr int16_t boss2_hm{5};
    constexpr int16_t boss2_sm{5};
    constexpr int16_t boss2_pm{1};

    constexpr std::string_view boss3_name{"Catchula"};
    constexpr int16_t boss3_hm{10};
    constexpr int16_t boss3_sm{10};
    constexpr int16_t boss3_pm{2};

    constexpr std::string_view boss4_name{"Khet-choup"};
    constexpr int16_t boss4_hm{15};
    constexpr int16_t boss4_sm{15};
    constexpr int16_t boss4_pm{3};

    namespace prize {
        constexpr int16_t prize_health {1};
        constexpr int16_t prize_damage {2};
        constexpr int16_t prize_potions {3};
    }

    static void send_defeated_message(std::string name, std::string& log)
    {
        std::string msg{name + " was defeated."};
        io::log_and_print(log, msg);
        io::pause_buffer();
    }

    static void log_selected_prize(std::string prize, std::string& log)
    {
        io::log_and_print(log, prize);
        io::pause_buffer();
        io::clear_output();
    }

    static void select_and_apply_prize(
            int16_t& health, int16_t& dmg_modifier, 
            int16_t& player_potions, int16_t player_health_modifier, std::string& log)
    {
        const std::optional<int> prize{io::print_and_get_choices(
            dialog::prize_title,
            dialog::prize_options
        )};

        if (!prize)
        {
            io::print_line("[ERROR] No prizes available");
            std::exit(1);
        }

        switch (*prize)
        {
            case prize::prize_health:
            {
                log_selected_prize("Health restored.", log);
                health = static_cast<int16_t>(
                        duel::constants::base_health - 
                        player_health_modifier);
                break;
            }
            case prize::prize_damage:
            {
                log_selected_prize("Increased damage.", log);
                dmg_modifier += 5;
                break;
            }
            case prize::prize_potions:
            {
                log_selected_prize("Restocked potions.", log);
                player_potions = duel::constants::base_potions;
                break;
            }
        }
    }

    std::string start_tournament()
    {
        const std::string player_name{io::get_name()};

        const std::optional<int> difficulty {
            io::print_and_get_choices(
                dialog::difficulty_title,
                dialog::difficulty_options)
        };

        assert(difficulty && *difficulty > 0 && *difficulty < 4);
        
        const int16_t player_health_mod {
            static_cast<int16_t>(
                    duel::constants::base_health * ((*difficulty - 1) / 4.0))
        };

        std::string log{};

        int16_t player_health  {
            static_cast<int16_t>(duel::constants::base_health - player_health_mod)
        };
        int16_t player_stamina {duel::constants::base_stamina};
        int16_t player_potions {duel::constants::base_potions};

        int16_t player_dmg_modifier {};
        int16_t player_potions_modifier {};

        log += "\nChampion " + player_name + " started the tournament.\n";

        // first fight

        log += "\nFirst opponent, " + static_cast<std::string>(boss1_name) + ".\n\n"; 

        bool won = duel::duel( 
            player_health, player_stamina,
            player_potions, player_dmg_modifier,
            boss1_hm, boss1_sm, boss1_pm, player_name, boss1_name, log
        );

        if (!won)
        {
            send_defeated_message(player_name, log);
            return log;
        }
        
        select_and_apply_prize(player_health, player_dmg_modifier, player_potions, player_health_mod, log);

        // second fight

        log += "\nSecond opponent, " + static_cast<std::string>(boss2_name) + ".\n\n";

        won = duel::duel( 
            player_health, player_stamina,
            player_potions, player_dmg_modifier,
            boss2_hm, boss2_sm, boss2_pm, player_name, boss2_name, log
        );

        if (!won)
        {
            send_defeated_message(player_name, log);
            return log;
        }
        
        select_and_apply_prize(player_health, player_dmg_modifier, player_potions, player_health_mod, log);

        // third fight

        log += "\nThird opponent, " + static_cast<std::string>(boss3_name) + ".\n\n";
        
        won = duel::duel( 
            player_health, player_stamina,
            player_potions, player_dmg_modifier,
            boss3_hm, boss3_sm, boss3_pm, player_name, boss3_name, log
        );

        if (!won)
        {
            send_defeated_message(player_name, log);
            return log;
        }
        
        select_and_apply_prize(player_health, player_dmg_modifier, player_potions, player_health_mod, log);

        // boss

        log += "\nLast opponent, " + static_cast<std::string>(boss4_name) + ".\n\n";

        won = duel::duel( 
            player_health, player_stamina,
            player_potions, player_dmg_modifier,
            boss4_hm, boss4_sm, boss4_pm, player_name, boss4_name, log
        );

        if (!won)
        {
            send_defeated_message(player_name, log);
            return log;
        }

        io::log_and_print(log, static_cast<std::string>(player_name) + " won the tournament!!!!!");
        io::pause_buffer();
        io::clear_output();

        return log;
    }
}
