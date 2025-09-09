#include "core.h"

#include <Windows.h>
#include <winuser.h>

#include "src/sdk/interfaces/cvar.h"
#include "src/sdk/interfaces/game_console.h"

bool core::check_insecure() {
  int     argc;
  LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
  if (!argv)
    return false;

  bool insecure = false;
  for (int i = 0; i < argc; ++i) {
    insecure = !wcscmp(argv[i], L"-insecure");

    if (insecure)
      break;
  }

  if (!insecure)
    MessageBoxA(nullptr, "Please add -insecure to your launch options.",
                "Incorrect Launch Options", MB_ICONERROR);

  LocalFree(argv);
  return insecure;
}

bool core::initialize() {
  float time = 0.f;
  while (!GetModuleHandleA("ServerBrowser.dll")) {
    Sleep(500), time += 0.5f;
    if (time >= 60.f || (GetAsyncKeyState(VK_DELETE) & 1))
      return false;
  }

  if (!g_interfaces.collect_interfaces())
    return false;

  g_interfaces.game_console->activate();
  g_interfaces.game_console->clear();
  sdk_message(color_t{250, 202, 222, 255}, "Interfaces initialized");

  if (!g_addresses.collect_addresses())
    return false;
  sdk_message(color_t{250, 202, 222, 255}, "Addresses initialized");

  sdk_message(color_t{0, 255, 0, 255}, "Loaded");

  g_globals.attached = true;
  return true;
}

bool core::should_unload() { return (GetAsyncKeyState(VK_DELETE) & 1); }

void core::unload() {
  g_globals.unloading = true;
  g_interfaces.game_console->activate();
  g_interfaces.game_console->clear();
  sdk_message(color_t{255, 0, 0, 255}, "Unloaded");
}

void core::sdk_message(const color_t& color, const char* format, ...) {
  g_interfaces.cvar->console_color_printf(color_t{255, 255, 255, 255}, "SDK | ");

  char    buffer[1024];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  g_interfaces.cvar->console_color_printf(color, buffer);
  g_interfaces.cvar->console_printf("\n");
}