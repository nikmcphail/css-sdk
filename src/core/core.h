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

  void sdk_message(const color_t& color, const char* message, ...);
} // namespace core