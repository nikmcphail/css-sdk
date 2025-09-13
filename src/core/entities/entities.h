#pragma once

class cs_player_t;
class player_resource_t;

class entities_t {
public:
  cs_player_t*       local_player;
  void*              local_weapon;
  player_resource_t* player_resource;

  void store();
  void clear();
};