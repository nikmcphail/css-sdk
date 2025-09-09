#pragma once

#include "globals/globals.h"
#include "interfaces/interfaces.h"
#include "addresses/addresses.h"

struct color_t;

namespace core {

  inline globals_t    g_globals;
  inline interfaces_t g_interfaces;
  inline addresses_t  g_addresses;

  bool check_insecure();
  bool initialize();
  bool should_unload();
  void unload();

  void sdk_message(const color_t& color, const char* format, ...);
  void sdk_error(const char* format, ...);
  void sdk_warning(const char* format, ...);
  void sdk_test(bool test_case = false, const char* success_text = "",
                const char* fail_text = "");

  void valve_con_message(const char* format, ...);
  void valve_con_color_message(const color_t& color, char const* format, ...);
  void valve_con_warning(const char* format, ...);

  void valve_dev_message(const char* format, ...);
  void valve_dev_warning(const char* format, ...);
} // namespace core