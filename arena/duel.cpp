#include "../lang/texts.h"
#include "../io/io.h"
#include "../utils/random.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <optional>
#include "duel.h"

#define MISS 0

namespace arena::duel
{

    static std::string_view enemy_name;
    static int16_t enemy_health;
    static int16_t enemy_stamina;
    static int16_t enemy_potions;

    static bool player_defending;
    static bool enemy_defending;

    using namespace std::literals;

    static void create_enemy(
            std::string_view name,
            int16_t health_modifier = 0, 
            int16_t stamina_modifier = 0,
            int16_t potions_modifier = 0)
    {
        enemy_health = constants::base_health + health_modifier;
        enemy_stamina = constants::base_stamina + stamina_modifier;
        enemy_potions = constants::base_potions + potions_modifier; 
        enemy_name = name;
    }

    // attacks 
    static Damage basic_attack(Status target, Status dmg_modifier, bool defense)
    {
        const bool hit{random::get(1, 5) > 1};
        if (hit)
        {
            const int16_t prob{static_cast<int16_t>(random::get(constants::basic_max_damage/2,constants::basic_max_damage))};
            Damage damage{std::min(constants::basic_max_damage, static_cast<int16_t>(prob + dmg_modifier))};
            damage = defense ? static_cast<int16_t>(damage / 2) : damage;
            return damage;
        }
        return {};
    }

    static std::optional<Damage> heavy_attack(Status target, Status dmg_modifier, bool defense)
    {
        const bool hit{random::get(1, 5) > 2};
        if (hit)
        {
            const int16_t prob{static_cast<int16_t>(random::get(constants::basic_max_damage, constants::heavy_max_damage))};
            Damage damage{std::min(constants::heavy_max_damage, static_cast<int16_t>(prob + dmg_modifier))};
            damage = defense ? static_cast<int16_t>(damage / 2) : damage;
            return damage;
        }
        return {};
    }

    static Property breathe(Status stamina, Status max_stamina=constants::base_stamina)
    {
        return std::min(max_stamina, 
                static_cast<int16_t>(stamina + 2 * constants::basic_max_damage));
    }

    static std::optional<Property> use_potion(Status& target_health, Status max_health, Status potions)
    {
        if (potions > 0)
        {
            --potions;
            target_health = std::min(max_health, 
                    static_cast<int16_t>(target_health + constants::potion_heal));
            return potions;
        }

        return {};
    }

    static std::optional<Property> exec_action(
            Option option,
            Status& src_health,
            Status& target_health,
            Status max_health,
            Status& src_stamina,
            Status max_stamina,
            Status& src_potions,
            Status dmg_modifier,
            bool& defending,
            bool is_player_action)
    {
        switch(option)
        {
        case constants::op_basic_attack:
            {
                const bool defense{is_player_action ? enemy_defending : player_defending};
                std::optional<Status> damage = basic_attack(target_health, dmg_modifier, defense);
                if (damage)
                {
                    target_health -= *damage;
                    return damage;
                }
                return MISS;
            }
        case constants::op_heavy_attack:
            { 
                const bool defense{is_player_action ? enemy_defending : player_defending};
                std::optional<Status> damage = heavy_attack(target_health, dmg_modifier, defense);
                if (damage)
                {
                    if (damage > src_stamina)
                    {
                        return {};
                    }
                    target_health -= *damage;
                    src_stamina -= *damage;
                    return damage;
                }
                return MISS;
            }
        case constants::op_defend:
            {
                defending = true;
                return defending;
            }
        case constants::op_breathe:
            {
                return (src_stamina = breathe(src_stamina, max_stamina));
            }
        case constants::op_use_potion:
            {
                const std::optional<Status> potions = use_potion(src_health, max_health, src_potions);
                
                if (potions)
                {
                    src_potions = *potions;
                    return src_potions;
                }
                return {};
            }
        case constants::op_inspect:
            {
                io::print_line(io::build_ui(
                        enemy_health, 
                        enemy_stamina,
                        enemy_potions,
                        enemy_name,
                        dialog::inspect_text));
                return {};
            }
        case constants::op_surrender:
            {
                const bool confirm{
                    io::print_and_get_choices(
                            "Are you sure?", "Yes*No") == 1
                };
                
                if (confirm) 
                {
                    src_health = 0;
                    return true;
                }

                return {};
            }
        }

        return {};
    }

    static Option get_player_option(Status health, Status stamina, Status pots, std::string_view name)
    { 
        std::string title = io::build_ui(
                health,
                stamina,
                pots,
                name,
                dialog::combat_title
            );

        const std::optional<Option> option = arena::io::print_and_get_choices(
                title,
                dialog::combat_options);

        if (!option)
        {
            io::print_line("[ERROR] No option available.");
            std::exit(1);
        }

        return *option;
    }

    static Option get_enemy_option()
    {
        if (enemy_health < constants::potion_heal && enemy_potions > 0) // low hp
            return constants::op_use_potion; 
        else if (enemy_stamina < constants::base_stamina / 2)
            return constants::op_breathe;
        else if (player_defending)
            return constants::op_heavy_attack;
        else
        {
            const int action{random::get(1, 3)};
            switch (action)
            {
                case 1: return constants::op_heavy_attack;
                case 2: return constants::op_basic_attack;
                default: return constants::op_defend;
            }
        }
    }
    
    static void log_info(Option option, Property result, std::string src_name, std::string& log)
    {
        std::string msg{};
        switch(option)
        {
        case constants::op_basic_attack:
            {
                if (result > 0)
                    msg = src_name + " used basic attack. Damage (HP) = " + std::to_string(result);
                else
                    msg = src_name + " missed.";
                break;
            }
        case constants::op_heavy_attack:
            {
                if (result > 0)
                    msg = src_name + " used heavy attack. Damage (HP) = " + std::to_string(result);
                else
                    msg = src_name + " missed.";
                break;
            }
        case constants::op_defend:
            {
                msg = src_name + " is defending.";
                break;
            }
        case constants::op_breathe:
            {
                msg = src_name + " took a breath.";
                break;
            }
        case constants::op_use_potion:
            {
                msg = src_name + " drank a potion and restored some health.";
                break;
            }
        case constants::op_surrender:
            {
                msg = src_name + " bailed.";
                break;
            }
        }

        if (msg.length())
            io::log_and_print(log, msg);
    }

    static void log_info(Option option, std::string src_name, std::string& log)
    {
        std::string msg{};
        switch (option)
        {
        case constants::op_heavy_attack:
            {
                msg = src_name + " heavy attack failed. Low stamina.";
                break;
            }
        case constants::op_use_potion:
            {
                msg = src_name + " is out of potions.";
                break;
            }
        }

        if (msg.length())
            io::log_and_print(log, msg);
    }

    static void player_turn(Status& player_health, Status& player_stamina, Status& player_pots, Status& dmg_modifier, std::string_view player_name, std::string& log)
    {
        while (true)
        {
            const Option player_option{
                get_player_option(player_health, player_stamina, player_pots, player_name)
            };

            std::optional<Property> result = 
                exec_action(
                    player_option, player_health, enemy_health,
                    constants::base_health, player_stamina, constants::base_stamina,
                    player_pots, dmg_modifier, player_defending, true
                );

            if (result)
            {
                log_info(player_option, *result, static_cast<std::string>(player_name), log);
                return;
            }
            log_info(player_option, static_cast<std::string>(player_name), log);
        }
    }

    static void enemy_turn(Option option,
            Status& player_health, Status enemy_health_mod, Status enemy_stamina_mod, std::string& log)
    {
        constexpr Status dmg_modifier{0}; // no modifier for enemies
        const Status max_health{static_cast<Status>(constants::base_health + enemy_health_mod)};
        const Status max_stamina{static_cast<Status>(constants::base_stamina + enemy_stamina_mod)};
        std::optional<Property> result = exec_action(
            option, enemy_health, player_health, max_health,
            enemy_stamina, max_stamina, enemy_potions, dmg_modifier, 
            enemy_defending, false); 

        if (result)
        {
            log_info(option, *result, static_cast<std::string>(enemy_name), log);
            return;
        }

        log_info(option, static_cast<std::string>(enemy_name), log);
    }

    // no duelo eu quero:
    // - jogador: hp atual, stamina máxima, potions, attack damage, nome

    // - inimigo: modificador de hp, stamina, potions e nome
    // - log
    bool duel(Status& player_health, Status &player_stamina, Status &player_pots, Status dmg_modifier, 
            Status enemy_health_mod, Status enemy_stamina_mod, Status enemy_potions_mod, 
            std::string_view player_name, std::string_view enemy_name,
            std::string& log)
    {
        create_enemy(enemy_name, enemy_health_mod, enemy_stamina_mod, enemy_potions_mod);
        
        do 
        {
            player_turn(player_health, player_stamina, player_pots, dmg_modifier, player_name, log);

            enemy_defending = false;

            if (player_health <= 0 || enemy_health <= 0)
                break;

            Option enemy_option{get_enemy_option()};
            enemy_turn(enemy_option, player_health, enemy_health_mod, enemy_stamina_mod, log);

            player_defending = false;
        }
        while (player_health > 0 && enemy_health > 0);

        return player_health > 0;
    }
}
