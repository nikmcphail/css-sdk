#include "base_animating.h"
#include "src/core/core.h"

void base_animating_t::get_bone_position(int bone, vector3_t& origin, qangle_t& angles) {
  static auto func = (void(__fastcall*)(
      void*, int, vector3_t&, qangle_t&))core::g_addresses.client.functions.get_bone_position;

  func(this, bone, origin, angles);
}