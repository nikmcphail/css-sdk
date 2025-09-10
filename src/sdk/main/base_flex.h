#pragma once

#include "base_animating.h"

class base_flex_t : public base_animating_overlay_t {
public:
  NETVAR(flex_weight, void*, "CBaseFlex", "m_flexWeight");
  NETVAR(blink_toggle, int, "CBaseFlex", "m_blinktoggle");
  NETVAR(view_target, vector3_t, "CBaseFlex", "m_viewtarget");
};