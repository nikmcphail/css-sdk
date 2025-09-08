#pragma once

#include "globals/globals.h"
#include "interfaces/interfaces.h"

namespace core {

  inline globals_t    g_globals;
  inline interfaces_t g_interfaces;

  bool check_insecure();
  bool initialize();
  bool should_unload();
  void unload();
} // namespace core