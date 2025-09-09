#include <Windows.h>
#include <thread>

#include "core/core.h"

unsigned long WINAPI initialize(void* argument) {
#ifdef INSECURE_CHECK // This is defined by default in both Release and Debug configurations.
                      // Remove it in CMakeLists if you don't want the check.
  if (!core::check_insecure()) {
    FreeLibraryAndExitThread(static_cast<HMODULE>(argument), EXIT_FAILURE);
    return 0;
  }
#endif

  if (core::initialize()) {
    while (!core::should_unload()) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    core::unload();
  }

  std::this_thread::sleep_for(std::chrono::seconds(1));

  FreeLibraryAndExitThread(static_cast<HMODULE>(argument), EXIT_SUCCESS);
}

BOOL WINAPI DllMain(HINSTANCE h_inst_dll, DWORD reason, LPVOID reserved) {
  if (reason == DLL_PROCESS_ATTACH) {
    auto handle = CreateThread(nullptr, 0, initialize, h_inst_dll, 0, nullptr);
    if (handle) {
      CloseHandle(handle);
    }
  }

  return TRUE;
}