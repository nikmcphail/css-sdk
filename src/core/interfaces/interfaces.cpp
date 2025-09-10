#include "interfaces.h"

#include <Windows.h>
#include <string>

#include "fmt/core.h"
#include "src/library/utils.h"
// #include "src/core/core.h"
// #include "src/sdk/main/color.h"
// Uncomment the above lines for LIST_INTERFACE_VERSIONS

template <typename t>
t* get_interface(const char* module_name, const char* partial, bool strict = false) {
  HMODULE module = GetModuleHandleA(module_name);
  if (!module)
    return nullptr;

  FARPROC create_interface_proc = GetProcAddress(module, "CreateInterface");
  if (!create_interface_proc)
    return nullptr;

  using create_interface_fn = void* (*)(const char*, int*);
  auto create_interface     = reinterpret_cast<create_interface_fn>(create_interface_proc);
  if (strict) {
    void* ret = create_interface(partial, nullptr);
    if (ret) {
#ifdef LIST_INTERFACE_VERSIONS
      if (core::g_interfaces.cvar) {
        core::sdk_message(COLOR_BLUE_BALANCED, "%s", partial);
      }
#endif
      return static_cast<t*>(ret);
    }

    return nullptr;
  } else {
    for (int i = 0; i < 100; i++) {
      std::string name = fmt::format("{}{:03}", partial, i);

      void* ret = create_interface(name.c_str(), nullptr);
      if (ret) {
#ifdef LIST_INTERFACE_VERSIONS
        if (core::g_interfaces.cvar) {
          core::sdk_message(COLOR_BLUE_BALANCED, "%s", name.c_str());
        }
#endif
        return static_cast<t*>(ret);
      }
    }
  }

  return nullptr;
}

bool interfaces_t::collect_interfaces() {
  this->cvar = get_interface<i_cvar_t>("vstdlib.dll", "VEngineCvar");
  if (!this->cvar) {
    return false;
  }

  this->base_client = get_interface<i_base_client_dll_t>("client.dll", "VClient");
  if (!this->base_client) {
    return false;
  }

  this->game_console = get_interface<i_game_console_t>("GameUI.dll", "GameConsole");
  if (!this->game_console) {
    return false;
  }

  this->entity_list = get_interface<i_client_entity_list_t>("client.dll", "VClientEntityList");
  if (!this->entity_list) {
    return false;
  }

  this->engine_trace = get_interface<i_engine_trace_t>("engine.dll", "EngineTraceClient");
  if (!this->engine_trace) {
    return false;
  }

  this->engine_client =
      get_interface<iv_engine_client_t>("engine.dll", "VEngineClient014", true);
  if (!this->engine_client) {
    return false;
  }

  this->input_system = get_interface<i_input_system_t>("inputsystem.dll", "InputSystemVersion");
  if (!this->input_system) {
    return false;
  }

  this->game_event =
      get_interface<i_game_event_manager_2_t>("engine.dll", "GAMEEVENTSMANAGER002", true);
  if (!this->game_event) {
    return false;
  }

  this->render_beams =
      *(utils::find_pattern_in_memory("client.dll",
                                      "48 8B 0D ? ? ? ? 48 8B D3 48 8B 01 FF 50 ? 0F B7 93")
            .rel32<i_view_render_beams_t**>(0x3));
  if (!this->render_beams) {
    return false;
  }

  return true;
}