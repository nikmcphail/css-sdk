#pragma once

#include "base_entity.h"

#include "src/core/core.h"
#include "src/core/netvars/netvars.h"
#include "src/sdk/misc/player_info.h"
#include "src/sdk/interfaces/engine_client.h"

#define PLAYER_UNCONNECTED_NAME "unconnected"
#define PLAYER_ERROR_NAME       "ERRORNAME"

class player_resource_t : public base_entity_t {
public:
  NETVAR_ARRAY(ping, int, "CPlayerResource", "m_iPing");
  NETVAR_ARRAY(score, int, "CPlayerResource", "m_iScore");
  NETVAR_ARRAY(deaths, int, "CPlayerResource", "m_iDeaths");
  NETVAR_ARRAY(connected, bool, "CPlayerResource", "m_bConnected");
  NETVAR_ARRAY(team, int, "CPlayerResource", "m_iTeam");
  NETVAR_ARRAY(alive, bool, "CPlayerResource", "m_bAlive");
  NETVAR_ARRAY(health, int, "CPlayerResource", "m_iHealth");
  NETVAR_ARRAY(account_id, unsigned, "CPlayerResource", "m_iAccountID");
  NETVAR_ARRAY(valid, bool, "CPlayerResource", "m_bValid");
  NETVAR_ARRAY(user_id, int, "CPlayerResource", "m_iUserID");

  NETVAR_ARRAY_OFF(name, const char*, "CPlayerResource", "m_iUserID", -816);

  inline bool is_fake(int index, bool player_info = false) {
    if (!player_info)
      return !ping(index);

    player_info_t info;
    if (core::g_interfaces.engine_client->get_player_info(index, &info))
      return info.fake_player;
    return false;
  }

  inline const char* get_name(int index) {
    const char* psz_name = name(index);
    return psz_name ? psz_name : PLAYER_ERROR_NAME;
  }
};