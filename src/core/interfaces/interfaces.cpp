#include "interfaces.h"

#include <Windows.h>
#include <string>

#include "fmt/core.h"

template <typename t> t* get_interface(const char* module_name, const char* partial) {
  HMODULE module = GetModuleHandleA(module_name);
  if (!module)
    return nullptr;

  FARPROC create_interface_proc = GetProcAddress(module, "CreateInterface");
  if (!create_interface_proc)
    return nullptr;

  using create_interface_fn = void* (*)(const char*, int*);
  auto create_interface     = reinterpret_cast<create_interface_fn>(create_interface_proc);

  for (int i = 0; i < 100; i++) {
    std::string name = fmt::format("{}{:03}", partial, i);

    void* ret = create_interface(name.c_str(), nullptr);
    if (ret)
      return static_cast<t*>(ret);
  }

  return nullptr;
}

bool interfaces_t::collect_interfaces() {
  this->cvar = get_interface<i_cvar_t>("vstdlib.dll", "VEngineCvar");
  if (!this->cvar) {
    MessageBox(nullptr, "ERROR", "ERROR", MB_OK);
    return false;
  }

  return true;
}