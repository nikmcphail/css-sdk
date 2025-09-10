#pragma once

#include "globals/globals.h"
#include "interfaces/interfaces.h"
#include "addresses/addresses.h"

struct color_t;
class vector3_t;
class trace_filter_t;
class trace_t;
class cs_player_t;

namespace core {

  inline globals_t    g_globals;
  inline interfaces_t g_interfaces;
  inline addresses_t  g_addresses;

  bool check_insecure();
  bool initialize();
  bool should_unload();
  void unload();

  // SDK message functions
  void sdk_message(const color_t& color, const char* format, ...);
  void sdk_error(const char* format, ...);
  void sdk_warning(const char* format, ...);
  void sdk_test(bool test_case = false, const char* success_text = "",
                const char* fail_text = "");

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