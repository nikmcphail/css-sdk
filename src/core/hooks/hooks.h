#pragma once

#include "safetyhook.hpp"

class hooks_t {
public:
  SafetyHookVmt directx_device_hook;
  SafetyHookVm  directx_present_hook;
  SafetyHookVm  directx_reset_hook;

  SafetyHookVmt surface_hook;
  SafetyHookVm  lock_cursor_hook;

  SafetyHookVmt base_client_hook;
  SafetyHookVm  frame_stage_notify_hook;
  SafetyHookVm  level_shutdown_hook;

  bool initialize();
  void unload();
};