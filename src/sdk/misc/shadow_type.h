#pragma once

enum ShadowType_t {
  SHADOWS_NONE = 0,
  SHADOWS_SIMPLE,
  SHADOWS_RENDER_TO_TEXTURE,
  SHADOWS_RENDER_TO_TEXTURE_DYNAMIC, // the shadow is always changing state
  SHADOWS_RENDER_TO_DEPTH_TEXTURE,
};