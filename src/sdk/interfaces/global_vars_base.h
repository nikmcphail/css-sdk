#pragma once

class global_vars_base_t {
public:
  float real_time;
  int   frame_count;
  float absolute_frame_time;
  float current_time;
  float frame_time;
  int   max_clients;
  int   tick_count;
  float interval_per_tick;
  float interpolation_amount;
  int   sim_ticks_this_frame;
  int   network_protocol;
  void* save_data;
  bool  is_client;
  int   timestamp_networking_base;
  int   timestamp_randomize_window;
};