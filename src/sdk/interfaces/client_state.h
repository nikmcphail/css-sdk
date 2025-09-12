#pragma once

#include <Windows.h>

#define MAX_OSPATH 260
#define MAX_EDICTS (1 << 11)

class i_net_channel_t;

class clock_drift_manager_t {
public:
  float clock_offsets[16];
  int   current_clock_offset;
  int   server_tick;
  int   client_tick;
};

class client_state_t {
public:
  byte                  pad0[24];
  int                   socket;
  i_net_channel_t*      net_channel;
  unsigned int          challenge_number;
  double                connect_time;
  int                   retry_number;
  char                  retry_address[MAX_OSPATH];
  char*                 retry_source_tag;
  int                   retry_challenge;
  int                   sign_on_state;
  double                next_cmd_count;
  int                   server_count;
  unsigned __int64      game_server_steam_id;
  int                   current_sequence;
  clock_drift_manager_t clock_drift_manager;
  int                   delta_tick;
  bool                  paused;
  float                 paused_expire_time;
  int                   view_entity;
  int                   player_slot;
  char                  level_file_name[128];
  byte                  pad1[132];
  char                  level_base_name[128];
  byte                  pad2[132];
  int                   max_clients;
  void*                 entity_baselines[2][MAX_EDICTS];
  byte                  pad3[2068];
  void*                 string_table_container;
  bool                  restrict_server_commands;
  bool                  restrict_client_commands;
  byte                  pad4[106];
  bool                  in_simulation;
  int                   old_tick_count;
  float                 tick_remainder;
  float                 frame_time;
  int                   last_outgoing_command;
  int                   choked_commands;
  int                   last_command_ack;
  int                   command_ack;
  int                   sound_sequence;
  bool                  is_hltv;
  bool                  is_replay;
  byte                  pad5[278];
  int                   demo_number;
};