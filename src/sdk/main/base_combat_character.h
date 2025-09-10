#pragma once

#include "base_flex.h"

class base_combat_character_t : public base_flex_t {
public:
  NETVAR(next_attack, float, "CBaseCombatCharacter", "m_flNextAttack");
  NETVAR(active_weapo, ehandle, "CBaseCombatCharacter", "m_hActiveWeapon");
};