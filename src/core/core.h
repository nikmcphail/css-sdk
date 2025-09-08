#pragma once

#include "globals/globals.h"

namespace core {

  inline globals_t g_globals;

  bool check_insecure();
  bool initialize();
  bool should_unload();
  void unload();
} // namespace core