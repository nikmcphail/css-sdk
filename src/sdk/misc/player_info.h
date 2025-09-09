#pragma once

#include <cstdint>

#define MAX_PLAYER_NAME_LENGTH 32
#define SIGNED_GUID_LEN        32
#define MAX_CUSTOM_FILES       4

struct player_info_t {
  // scoreboard information
  char          name[MAX_PLAYER_NAME_LENGTH];
  // local server user ID, unique while server is running
  int           user_id;
  // global unique player identifer
  char          gu_id[SIGNED_GUID_LEN + 1];
  // friends identification number
  uint32_t      friends_id;
  // friends name
  char          friends_name[MAX_PLAYER_NAME_LENGTH];
  // true, if player is a bot controlled by game.dll
  bool          fake_player;
  // true if player is the HLTV proxy
  bool          is_hltv;
  // custom files CRC for this player
  unsigned int  custom_files[MAX_CUSTOM_FILES];
  // this counter increases each time the server downloaded a new file
  unsigned char files_downloaded;
};