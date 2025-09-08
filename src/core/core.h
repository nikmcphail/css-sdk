#pragma once

#include "globals/globals.h"
#include "interfaces/interfaces.h"
#include "addresses/addresses.h"

namespace core {

  inline globals_t    g_globals;
  inline interfaces_t g_interfaces;
  inline addresses_t  g_addresses;

  bool check_insecure();
  bool initialize();
  bool should_unload();
  void unload();
} // namespace core