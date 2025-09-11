#pragma once

#include <Windows.h>
#include <mutex>
#include <shared_mutex>
#include "src/sdk/main/vector2.h"

struct ImDrawList;
class ImFont;

class render_t {
public:
  // ImFont*              font_small   = nullptr;
  // ImFont*              font_regular = nullptr;
  // ImFont*              font_bold    = nullptr;
  // ImFont*              font_large   = nullptr;
  // ImFont*              font_mono    = nullptr;
  vector2_t            screen_size{};
  ImDrawList*          draw_list;
  HWND                 window;
  std::recursive_mutex imgui_mutex{};
  std::shared_mutex    unload_mutex{};
  WNDPROC              orig_wndproc{};

  // void get_view_matrix();

  // void setup_fonts();
  void setup_style();
  bool initialize();
  void unload();
  void begin();
  void finish();
  void setup_input();
  void unload_input();
};