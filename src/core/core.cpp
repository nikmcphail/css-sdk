#include "core.h"

#include <Windows.h>

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
  g_globals.attached = true;
  return true;
}

bool core::should_unload() {
  g_globals.unloading = true;
  return (GetAsyncKeyState(VK_DELETE) & 1);
}

void core::unload() {}