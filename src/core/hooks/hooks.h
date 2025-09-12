#pragma once

#include "safetyhook.hpp"

class hooks_t {
public:
  SafetyHookVmt directx_device_hook;
  SafetyHookVm  directx_present_hook;
  SafetyHookVm  directx_reset_hook;

  SafetyHookVmt surface_hook;
  SafetyHookVm  lock_cursor_hook;

  bool initialize();
  void unload();
};