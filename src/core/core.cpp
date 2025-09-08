#include "core.h"

#include <Windows.h>

#include "src/sdk/interfaces/cvar.h"

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
  if (!g_interfaces.collect_interfaces())
    return false;

  g_interfaces.cvar->console_color_printf(color_t{255, 255, 255, 255}, "CSS-SDK |");
  g_interfaces.cvar->console_color_printf(color_t{0, 255, 0, 255}, " Loaded\n");

  g_globals.attached = true;
  return true;
}

bool core::should_unload() { return (GetAsyncKeyState(VK_DELETE) & 1); }

void core::unload() {
  g_interfaces.cvar->console_color_printf(color_t{255, 255, 255, 255}, "CSS-SDK |");
  g_interfaces.cvar->console_color_printf(color_t{255, 0, 0, 255}, " Unloaded\n");
  g_globals.unloading = true;
}