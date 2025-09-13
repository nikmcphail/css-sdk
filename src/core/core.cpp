#include "core.h"

#include <Windows.h>
#include <d3d9.h>
#include <winuser.h>

#include "src/library/utils.h"
#include "src/sdk/interfaces/cvar.h"
#include "src/sdk/interfaces/game_console.h"
#include "src/sdk/main/color.h"
#include "src/sdk/interfaces/engine_trace.h"
#include "src/sdk/main/ray.h"
#include "src/sdk/main/trace.h"
#include "src/sdk/main/trace_filter.h"
#include "src/sdk/main/cs_player.h"
#include "src/sdk/interfaces/engine_client.h"

#include "menu/menu.h"

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
  // see if we can find haptics pointer
  while (!utils::find_pattern_in_memory("client.dll",
                                        "48 8B 0D ? ? ? ? 48 8B 10 48 8B 19 48 8B C8 FF 92")) {
    core::valve_con_color_message(COLOR_YELLOW_BALANCED,
                                  "[SDK Load Warning] Cannot find haptics pointer, attempting "
                                  "to find again... (Press DELETE to cancel.)");
    Sleep(500), time += 0.5f;
    if (time >= 60.f || (GetAsyncKeyState(VK_DELETE) & 1))
      core::valve_con_color_message(
          COLOR_RED_BALANCED,
          "[SDK Load Error] Haptics pointer not found, unable to continue.");
    return false;
  }

  if (!g_interfaces.collect_interfaces())
    return false;

  // If you enable LIST_INTERFACE_VERSIONS, comment out the clear below.
  g_interfaces.game_console->clear();
  sdk_message(COLOR_WHITE, "Build mode: %s", _CONFIGURATION);
  sdk_message(COLOR_PURPLE_LIGHT, "Press INSERT to open menu.");
  sdk_message(COLOR_ORANGE_LIGHT, "Press DELETE to unload.");
  sdk_message(COLOR_WHITE, "Interfaces initialized.");

  if (!g_addresses.collect_addresses())
    return false;
  sdk_message(COLOR_WHITE, "Addresses initialized.");

  get_window_handle();

  if (!g_render.initialize())
    return false;
  sdk_message(COLOR_WHITE, "Render initialized.");

  g_render.setup_input();
  sdk_message(COLOR_WHITE, "Input initalized.");

  if (!g_hooks.initialize())
    return false;
  sdk_message(COLOR_WHITE, "Hooks initialized.");

  sdk_message(COLOR_GREEN_BALANCED, "Loaded.");
  g_globals.attached = true;
  return true;
}

bool core::should_unload() { return (GetAsyncKeyState(VK_DELETE) & 1); }

void core::unload() {
  std::unique_lock _{g_render.unload_mutex};
  g_globals.unloading = true;
  g_hooks.unload();
  g_render.unload_input();
  g_render.unload();
  g_interfaces.game_console->clear();
  sdk_message(COLOR_RED_BALANCED, "Unloaded.");
}

void core::get_window_handle() {
  D3DDEVICE_CREATION_PARAMETERS creation_parameters;
  g_interfaces.directx_device->GetCreationParameters(&creation_parameters);

  g_window = creation_parameters.hFocusWindow;
}

void core::on_present() {
  g_render.begin();
  menu::present();
  g_render.finish();
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

void core::valve_con_message(const char* format, ...) {
  char buffer[1024];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer) - 2, format, args);
  va_end(args);

  size_t len      = strlen(buffer);
  buffer[len]     = '\n';
  buffer[len + 1] = '\0';

  static ULONG64 con_msg_address = utils::get_export("tier0.dll", "?ConMsg@@YAXPEBDZZ");
  static auto    func            = (void (*)(const char*))con_msg_address;

  func(buffer);
}

void core::valve_con_color_message(const color_t& color, char const* format, ...) {
  char buffer[1024];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer) - 2, format, args);
  va_end(args);

  size_t len      = strlen(buffer);
  buffer[len]     = '\n';
  buffer[len + 1] = '\0';

  static ULONG64 con_color_msg_address =
      utils::get_export("tier0.dll", "?ConColorMsg@@YAXAEBVColor@@PEBDZZ");
  static auto func = (void (*)(const color_t&, const char*))con_color_msg_address;

  func(color, buffer);
}

void core::valve_con_warning(const char* format, ...) {
  char buffer[1024];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer) - 2, format, args);
  va_end(args);

  size_t len      = strlen(buffer);
  buffer[len]     = '\n';
  buffer[len + 1] = '\0';

  static ULONG64 con_warning_address = utils::get_export("tier0.dll", "?ConWarning@@YAXPEBDZZ");
  static auto    func                = (void (*)(const char*))con_warning_address;

  func(buffer);
}

void core::valve_dev_message(const char* format, ...) {
  char buffer[1024];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer) - 2, format, args);
  va_end(args);

  size_t len      = strlen(buffer);
  buffer[len]     = '\n';
  buffer[len + 1] = '\0';

  static ULONG64 dev_msg_address = utils::get_export("tier0.dll", "?DevMsg@@YAXPEBDZZ");
  static auto    func            = (void (*)(const char*))dev_msg_address;

  func(buffer);
}

void core::valve_dev_warning(const char* format, ...) {
  char buffer[1024];

  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer) - 2, format, args);
  va_end(args);

  size_t len      = strlen(buffer);
  buffer[len]     = '\n';
  buffer[len + 1] = '\0';

  static ULONG64 dev_warning_address = utils::get_export("tier0.dll", "?DevWarning@@YAXPEBDZZ");
  static auto    func                = (void (*)(const char*))dev_warning_address;

  func(buffer);
}

void core::trace(const vector3_t& start, const vector3_t& end, unsigned int mask,
                 trace_filter_t* filter, trace_t* trace) {
  ray_t ray(start, end);
  g_interfaces.engine_trace->trace_ray(ray, mask, filter, trace);
}

void core::trace_hull(const vector3_t& start, const vector3_t& end, const vector3_t& mins,
                      const vector3_t& maxs, int mask, trace_filter_t* filter, trace_t* trace) {
  ray_t ray(start, end, mins, maxs);
  g_interfaces.engine_trace->trace_ray(ray, mask, filter, trace);
}

cs_player_t* core::get_local_player() {
  if (i_client_entity_t* local = g_interfaces.entity_list->get_client_entity(
          g_interfaces.engine_client->get_local_player_index()))
    return local->as<cs_player_t>();

  return nullptr;
}

void core::pre_frame_stage_notify(client_frame_stage_e stage) {
  switch (stage) {
    case FRAME_NET_UPDATE_START: {
      break;
    }

    default:
      break;
  }
}

void core::post_frame_stage_notify(client_frame_stage_e stage) {
  switch (stage) {
    case FRAME_NET_UPDATE_START: {
      g_entities.clear();
      break;
    }
    case FRAME_NET_UPDATE_END: {
      g_entities.store();
      break;
    }

    default:
      break;
  }
}