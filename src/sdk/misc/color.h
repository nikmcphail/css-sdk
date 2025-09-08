#pragma once

#include <algorithm>
#include "fmt/core.h"

using byte = unsigned char;
struct color_t {
  byte r = 255, g = 255, b = 255, a = 255;

  inline void set_rgb(float fl_r = 255.f, float fl_g = 255.f, float fl_b = 255.f,
                      float fl_a = 255.f) {
    r = byte(std::clamp(fl_r, 0.f, 255.f));
    g = byte(std::clamp(fl_g, 0.f, 255.f));
    b = byte(std::clamp(fl_b, 0.f, 255.f));
    a = byte(std::clamp(fl_a, 0.f, 255.f));
  }

  inline void set_hsv(float fl_h, float fl_s = 100.f, float fl_v = 100.f, float fl_a = 255.f) {
    float fl_r, fl_g, fl_b;

    fl_h = std::clamp(fl_h, 0.f, 360.f);
    fl_s = std::clamp(fl_s, 0.f, 100.f);
    fl_v = std::clamp(fl_v, 0.f, 100.f);

    fl_s /= 100;
    fl_v /= 100;
    if (!fl_s)
      fl_r = fl_g = fl_b = fl_v;
    else {
      int   i    = int(floor(fl_h /= 60));
      float fl_f = fl_h - i;
      float fl_p = fl_v * (1 - fl_s);
      float fl_q = fl_v * (1 - fl_f * fl_s);
      float fl_t = fl_v * (1 - (1 - fl_f) * fl_s);

      switch (i) {
        case 0:
          fl_r = fl_v;
          fl_g = fl_t;
          fl_b = fl_p;
          break;
        case 1:
          fl_r = fl_q;
          fl_g = fl_v;
          fl_b = fl_p;
          break;
        case 2:
          fl_r = fl_p;
          fl_g = fl_v;
          fl_b = fl_t;
          break;
        case 3:
          fl_r = fl_p;
          fl_g = fl_q;
          fl_b = fl_v;
          break;
        case 4:
          fl_r = fl_t;
          fl_g = fl_p;
          fl_b = fl_v;
          break;
        default:
          fl_r = fl_v;
          fl_g = fl_p;
          fl_b = fl_q;
          break;
      }
    }

    r = byte(std::clamp(fl_r * 255, 0.f, 255.f));
    g = byte(std::clamp(fl_g * 255, 0.f, 255.f));
    b = byte(std::clamp(fl_b * 255, 0.f, 255.f));
    a = byte(std::clamp(fl_a, 0.f, 255.f));
  }

  inline void get_hsv(float& fl_h, float& fl_s, float& fl_v) {
    float fl_r = r / 255.f;
    float fl_g = g / 255.f;
    float fl_b = b / 255.f;

    float fl_k = 0.f;
    if (fl_g < fl_b) {
      float temp = fl_g;
      fl_g       = fl_b;
      fl_b       = temp;
      fl_k       = -1.f;
    }
    if (fl_r < fl_g) {
      float temp = fl_r;
      fl_r       = fl_g;
      fl_g       = temp;
      fl_k       = -2.f / 6.f - fl_k;
    }

    float chroma = fl_r - (fl_g < fl_b ? fl_g : fl_b);
    fl_h         = fabsf(fl_k + (fl_g - fl_b) / (6.f * chroma + FLT_EPSILON)) * 360;
    fl_s         = chroma / (fl_r + FLT_EPSILON) * 100;
    fl_v         = fl_r * 100;
  }

  inline color_t HueShift(float flShift) {
    float fl_h, fl_s, fl_v;
    get_hsv(fl_h, fl_s, fl_v);
    color_t out;
    out.set_hsv(fmodf(fl_h + flShift, 360.f), fl_s, fl_v, a);
    return out;
  }

  inline bool operator==(color_t other) const {
    return r == other.r && g == other.g && b == other.b && a == other.a;
  }

  inline bool operator!=(color_t other) const {
    return r != other.r || g != other.g || b != other.b || a != other.a;
  }

  inline std::string to_hex() const { return fmt::format("\x7{:02x}{:02x}{:02x}", r, g, b); }

  inline std::string to_hex_a() const {
    return fmt::format("\x8{:02x}{:02x}{:02x}{:02x}", r, g, b, a);
  }

  inline color_t alpha(byte to) const { return {r, g, b, to}; }

  inline int brightness() const { return r + g + b; }
};