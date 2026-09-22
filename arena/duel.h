#if !defined(PITO_DUEL_H)
#define PITO_DUEL_H

#include <algorithm>
#include <cstdint>
#include <string>

namespace arena::duel::constants
{
    inline constexpr int16_t base_health{100};
    inline constexpr int16_t base_stamina{100};
    inline constexpr int16_t base_potions{3};

    inline constexpr int16_t basic_max_damage{base_health / 5};
    inline constexpr int16_t heavy_max_damage{base_health / 2};

    inline constexpr int16_t potion_heal{base_health / base_potions};

    // duel options
    inline constexpr int16_t op_basic_attack {1};
    inline constexpr int16_t op_heavy_attack {2};
    inline constexpr int16_t op_defend {3};
    inline constexpr int16_t op_breathe {4};
    inline constexpr int16_t op_use_potion {5};
    inline constexpr int16_t op_inspect {6};
    inline constexpr int16_t op_surrender {7};

}

namespace arena::duel
{

    using Option=int16_t;
    using Status=int16_t;
    using Damage=int16_t;
    using Property=int16_t;

    bool duel(Status& player_health, Status &player_stamina, Status
            &player_pots, Status dmg_modifier, Status enemy_health_mod, Status
            enemy_stamina_mod, Status enemy_potions_mod, std::string_view
            player_name, std::string_view enemy_name, std::string& log);
}

#endif
