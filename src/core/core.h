#pragma once

#include <Windows.h>

#include "globals/globals.h"
#include "interfaces/interfaces.h"
#include "addresses/addresses.h"
#include "render/render.h"
#include "hooks/hooks.h"
#include "patches/patches.h"
#include "src/sdk/misc/client_frame_stage.h"

struct color_t;
class vector3_t;
class trace_filter_t;
class trace_t;
class cs_player_t;

namespace core {

  inline globals_t    g_globals;
  inline interfaces_t g_interfaces;
  inline addresses_t  g_addresses;
  inline render_t     g_render;
  inline hooks_t      g_hooks;
  inline patches_t    g_patches;

  inline HWND g_window;

  bool check_insecure();
  bool initialize();
  bool should_unload();
  void unload();

  void get_window_handle();
  void on_present();
  void pre_frame_stage_notify(client_frame_stage_e stage);
  void post_frame_stage_notify(client_frame_stage_e stage);

  // SDK message functions
  void sdk_message(const color_t& color, const char* format, ...);
  void sdk_error(const char* format, ...);
  void sdk_warning(const char* format, ...);
  void sdk_test(bool test_case = false, const char* success_text = "",
                const char* fail_text = "");
  void sdk_custom(const color_t& color, const char* tag, const char* format, ...);

  // Valve message functions
  void valve_con_message(const char* format, ...);
  void valve_con_color_message(const color_t& color, char const* format, ...);
  void valve_con_warning(const char* format, ...);

  void valve_dev_message(const char* format, ...);
  void valve_dev_warning(const char* format, ...);

  void trace(const vector3_t& start, const vector3_t& end, unsigned int mask,
             trace_filter_t* filter, trace_t* trace);
  void trace_hull(const vector3_t& start, const vector3_t& end, const vector3_t& mins,
                  const vector3_t& maxs, int mask, trace_filter_t* filter, trace_t* trace);

  // Entity functions
  cs_player_t* get_local_player();
} // namespace core