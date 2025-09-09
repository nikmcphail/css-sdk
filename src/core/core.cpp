#include "core.h"

#include <Windows.h>
#include <winuser.h>

#include "src/sdk/interfaces/cvar.h"
#include "src/sdk/interfaces/game_console.h"
#include "src/sdk/misc/color.h"

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
  sdk_message(COLOR_WHITE, "Build Mode: %s", _CONFIGURATION);
  sdk_message(COLOR_WHITE, "Interfaces Initialized");

  if (!g_addresses.collect_addresses())
    return false;
  sdk_message(COLOR_WHITE, "Addresses Initialized");

  sdk_message(COLOR_GREEN_BALANCED, "Loaded");

  g_globals.attached = true;
  return true;
}

bool core::should_unload() { return (GetAsyncKeyState(VK_DELETE) & 1); }

void core::unload() {
  g_globals.unloading = true;
  g_interfaces.game_console->activate();
  g_interfaces.game_console->clear();
  sdk_message(COLOR_RED_BALANCED, "Unloaded");
}

void core::sdk_message(const color_t& color, const char* format, ...) {
  g_interfaces.cvar->console_color_printf(COLOR_BLUE_LIGHT, "[SDK] ");

  char    buffer[1024];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  g_interfaces.cvar->console_color_printf(color, buffer);
  g_interfaces.cvar->console_printf("\n");
}

void core::sdk_error(const char* format, ...) {
  g_interfaces.cvar->console_color_printf(COLOR_RED_BALANCED, "[Error] ");

  char    buffer[1024];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  g_interfaces.cvar->console_color_printf(COLOR_RED_BALANCED, buffer);
  g_interfaces.cvar->console_printf("\n");
}

void core::sdk_warning(const char* format, ...) {
  g_interfaces.cvar->console_color_printf(COLOR_YELLOW_BALANCED, "[Warning] ");

  char    buffer[1024];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  g_interfaces.cvar->console_color_printf(COLOR_YELLOW_BALANCED, buffer);
  g_interfaces.cvar->console_printf("\n");
}

// kind of basic, might improve later if i need more than simple boolean statements
void core::sdk_test(bool test_case, const char* success_text, const char* fail_text) {
  if (test_case) {
    g_interfaces.cvar->console_color_printf(COLOR_GREEN_BALANCED, "[Test Passed] %s\n",
                                            success_text);
  } else {
    g_interfaces.cvar->console_color_printf(COLOR_RED_BALANCED, "[Test Failed] %s\n",
                                            fail_text);
  }
}