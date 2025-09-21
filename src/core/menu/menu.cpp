#include "menu.h"

#include <Windows.h>
#include "imgui.h"

void menu::present() {
  auto& io           = ImGui::GetIO();
  io.MouseDrawCursor = open;

  if (GetAsyncKeyState(VK_INSERT) & 1)
    open = !open;

  if (!open)
    return;

  draw_main_menu();
}

void menu::draw_main_menu() {
  if (ImGui::Begin("CSS-SDK##sdk_main_menu", nullptr, ImGuiWindowFlags_NoCollapse)) {
    //
  }
  ImGui::End();
}