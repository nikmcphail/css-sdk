#include "render.h"

#include "src/core/core.h"
#include "src/core/menu/menu.h"

#include <d3d9.h>

#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam,
                                                             LPARAM lParam);

LRESULT WINAPI wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
  if (!core::g_globals.attached) {
    return CallWindowProcW(core::g_render.orig_wndproc, hwnd, msg, wp, lp);
  }

  auto call_def = true;

  switch (msg) {
    case WM_SYSCHAR: {
      call_def = false;
      break;
    }

    default: {
      break;
    }
  }

  {
    std::scoped_lock _{core::g_render.imgui_mutex};
    ImGui_ImplWin32_WndProcHandler(hwnd, msg, wp, lp);
  }

  if (menu::open) {
    return call_def ? DefWindowProcW(hwnd, msg, wp, lp) : 0;
  }

  return CallWindowProcW(core::g_render.orig_wndproc, hwnd, msg, wp, lp);
}

void render_t::setup_style() {
  auto& io    = ImGui::GetIO();
  auto& style = ImGui::GetStyle();

  io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

  style.Alpha                            = 1.0f;
  style.DisabledAlpha                    = 0.6f;
  style.WindowPadding                    = ImVec2(8.0f, 8.0f);
  style.WindowRounding                   = 0.0f;
  style.WindowBorderSize                 = 1.0f;
  style.WindowMinSize                    = ImVec2(32.0f, 32.0f);
  style.WindowTitleAlign                 = ImVec2(0.0f, 0.5f);
  style.WindowMenuButtonPosition         = ImGuiDir_Left;
  style.ChildRounding                    = 0.0f;
  style.ChildBorderSize                  = 1.0f;
  style.PopupRounding                    = 0.0f;
  style.PopupBorderSize                  = 1.0f;
  style.FramePadding                     = ImVec2(4.0f, 3.0f);
  style.FrameRounding                    = 0.0f;
  style.FrameBorderSize                  = 1.0f;
  style.ItemSpacing                      = ImVec2(8.0f, 4.0f);
  style.ItemInnerSpacing                 = ImVec2(4.0f, 4.0f);
  style.CellPadding                      = ImVec2(4.0f, 2.0f);
  style.IndentSpacing                    = 21.0f;
  style.ColumnsMinSpacing                = 6.0f;
  style.ScrollbarSize                    = 14.0f;
  style.ScrollbarRounding                = 0.0f;
  style.GrabMinSize                      = 10.0f;
  style.GrabRounding                     = 0.0f;
  style.TabRounding                      = 0.0f;
  style.TabBorderSize                    = 0.0f;
  style.TabCloseButtonMinWidthSelected   = 0.0f;
  style.TabCloseButtonMinWidthUnselected = 0.0f;
  style.ColorButtonPosition              = ImGuiDir_Right;
  style.ButtonTextAlign                  = ImVec2(0.5f, 0.5f);
  style.SelectableTextAlign              = ImVec2(0.0f, 0.0f);

  style.Colors[ImGuiCol_Text]                 = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
  style.Colors[ImGuiCol_TextDisabled]         = ImVec4(0.498f, 0.498f, 0.498f, 1.0f);
  style.Colors[ImGuiCol_WindowBg]             = ImVec4(0.286f, 0.337f, 0.259f, 1.0f);
  style.Colors[ImGuiCol_ChildBg]              = ImVec4(0.286f, 0.337f, 0.259f, 1.0f);
  style.Colors[ImGuiCol_PopupBg]              = ImVec4(0.239f, 0.267f, 0.200f, 1.0f);
  style.Colors[ImGuiCol_Border]               = ImVec4(0.537f, 0.569f, 0.51f, 0.5f);
  style.Colors[ImGuiCol_BorderShadow]         = ImVec4(0.137f, 0.157f, 0.110f, 0.52f);
  style.Colors[ImGuiCol_FrameBg]              = ImVec4(0.239f, 0.267f, 0.200f, 1.0f);
  style.Colors[ImGuiCol_FrameBgHovered]       = ImVec4(0.267f, 0.298f, 0.227f, 1.0f);
  style.Colors[ImGuiCol_FrameBgActive]        = ImVec4(0.298f, 0.337f, 0.259f, 1.0f);
  style.Colors[ImGuiCol_TitleBg]              = ImVec4(0.239f, 0.267f, 0.200f, 1.0f);
  style.Colors[ImGuiCol_TitleBgActive]        = ImVec4(0.286f, 0.337f, 0.259f, 1.0f);
  style.Colors[ImGuiCol_TitleBgCollapsed]     = ImVec4(0.0f, 0.0f, 0.0f, 0.51f);
  style.Colors[ImGuiCol_MenuBarBg]            = ImVec4(0.239f, 0.267f, 0.200f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarBg]          = ImVec4(0.349f, 0.420f, 0.310f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrab]        = ImVec4(0.278f, 0.318f, 0.239f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.247f, 0.298f, 0.220f, 1.0f);
  style.Colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.227f, 0.267f, 0.208f, 1.0f);
  style.Colors[ImGuiCol_CheckMark]            = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);
  style.Colors[ImGuiCol_SliderGrab]           = ImVec4(0.349f, 0.420f, 0.310f, 1.0f);
  style.Colors[ImGuiCol_SliderGrabActive]     = ImVec4(0.537f, 0.568f, 0.510f, 0.5f);
  style.Colors[ImGuiCol_Button]               = ImVec4(0.286f, 0.337f, 0.259f, 0.4f);
  style.Colors[ImGuiCol_ButtonHovered]        = ImVec4(0.349f, 0.420f, 0.310f, 1.0f);
  style.Colors[ImGuiCol_ButtonActive]         = ImVec4(0.537f, 0.568f, 0.510f, 0.5f);

  style.Colors[ImGuiCol_TableHeaderBg]     = ImVec4(0.239f, 0.267f, 0.200f, 1.0f);
  style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);
  style.Colors[ImGuiCol_TableBorderLight]  = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);
  style.Colors[ImGuiCol_Header]            = ImVec4(0.75f, 0.65f, 0.15f, 0.9f);
  style.Colors[ImGuiCol_HeaderHovered]     = ImVec4(0.85f, 0.75f, 0.25f, 1.0f);
  style.Colors[ImGuiCol_HeaderActive]      = ImVec4(0.65f, 0.55f, 0.10f, 1.0f);

  style.Colors[ImGuiCol_Separator]         = ImVec4(0.537f, 0.569f, 0.51f, 0.5f);
  style.Colors[ImGuiCol_SeparatorHovered]  = ImVec4(0.537f, 0.568f, 0.510f, 1.0f);
  style.Colors[ImGuiCol_SeparatorActive]   = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);
  style.Colors[ImGuiCol_ResizeGrip]        = ImVec4(0.188f, 0.227f, 0.176f, 0.0f);
  style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.537f, 0.568f, 0.510f, 1.0f);
  style.Colors[ImGuiCol_ResizeGripActive]  = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);

  style.Colors[ImGuiCol_Tab]                = ImVec4(0.349f, 0.420f, 0.310f, 1.0f);
  style.Colors[ImGuiCol_TabHovered]         = ImVec4(0.537f, 0.568f, 0.510f, 0.78f);
  style.Colors[ImGuiCol_TabActive]          = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocused]       = ImVec4(0.239f, 0.267f, 0.200f, 1.0f);
  style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.349f, 0.420f, 0.310f, 1.0f);

  style.Colors[ImGuiCol_PlotLines]            = ImVec4(0.608f, 0.608f, 0.608f, 1.0f);
  style.Colors[ImGuiCol_PlotLinesHovered]     = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogram]        = ImVec4(1.0f, 0.776f, 0.278f, 1.0f);
  style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6f, 0.0f, 1.0f);
  style.Colors[ImGuiCol_TableRowBg]           = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
  style.Colors[ImGuiCol_TableRowBgAlt]        = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
  style.Colors[ImGuiCol_TextSelectedBg]       = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);

  style.Colors[ImGuiCol_DragDropTarget]        = ImVec4(0.729f, 0.667f, 0.239f, 1.0f);
  style.Colors[ImGuiCol_NavHighlight]          = ImVec4(0.588f, 0.537f, 0.176f, 1.0f);
  style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.7f);
  style.Colors[ImGuiCol_NavWindowingDimBg]     = ImVec4(0.8f, 0.8f, 0.8f, 0.2f);
  style.Colors[ImGuiCol_ModalWindowDimBg]      = ImVec4(0.8f, 0.8f, 0.8f, 0.35f);
}

void render_t::setup_input() {
  orig_wndproc = reinterpret_cast<WNDPROC>(
      SetWindowLongPtrW(core::g_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndproc)));
}

void render_t::unload_input() {
  SetWindowLongPtrW(core::g_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(orig_wndproc));
}

bool render_t::initialize() {
  ImGui::CreateContext();
  auto& io = ImGui::GetIO();

  if (!ImGui_ImplWin32_Init(core::g_window)) {
    return false;
  }

  if (!ImGui_ImplDX9_Init(core::g_interfaces.directx_device)) {
    return false;
  }

  io.Fonts->AddFontDefault();

  // setup_fonts();
  setup_style();

  return true;
}

void render_t::unload() {
  ImGui_ImplDX9_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();
}

DWORD g_prev_srgb{};

void render_t::begin() {
  core::g_interfaces.directx_device->GetRenderState(D3DRS_SRGBWRITEENABLE, &g_prev_srgb);
  core::g_interfaces.directx_device->SetRenderState(D3DRS_SRGBWRITEENABLE, FALSE);

  ImGui_ImplDX9_NewFrame();
  ImGui_ImplWin32_NewFrame();

  auto& display_size = ImGui::GetIO().DisplaySize;
  screen_size        = {display_size.x, display_size.y};

  {
    std::scoped_lock _{core::g_render.imgui_mutex};
    ImGui::NewFrame();
  }

  draw_list = ImGui::GetBackgroundDrawList();
}

void render_t::finish() {
  ImGui::Render();
  ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
  core::g_interfaces.directx_device->SetRenderState(D3DRS_SRGBWRITEENABLE, g_prev_srgb);
}