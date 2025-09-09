#pragma once

#include <algorithm>
#include <sstream>
#include "fmt/core.h"

using byte = unsigned char;
struct color_t {
  byte r = 255, g = 255, b = 255, a = 255;

  color_t() = default;

  // RGB / RGBA constructor
  constexpr color_t(byte red, byte green, byte blue, byte alpha = 255)
      : r(red), g(green), b(blue), a(alpha) {}

  // Hex constructor (#RRGGBB or #RRGGBBAA)
  explicit color_t(const std::string& hex) {
    if (hex.size() == 7 && hex[0] == '#') { // #RRGGBB
      unsigned int      value = 0;
      std::stringstream ss;
      ss << std::hex << hex.substr(1);
      ss >> value;

      r = byte((value >> 16) & 0xFF);
      g = byte((value >> 8) & 0xFF);
      b = byte(value & 0xFF);
      a = 255;
    } else if (hex.size() == 9 && hex[0] == '#') { // #RRGGBBAA
      unsigned int      value = 0;
      std::stringstream ss;
      ss << std::hex << hex.substr(1);
      ss >> value;

      r = byte((value >> 24) & 0xFF);
      g = byte((value >> 16) & 0xFF);
      b = byte((value >> 8) & 0xFF);
      a = byte(value & 0xFF);
    }
    // else → keep default (white)
  }

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

const color_t COLOR_RED_LIGHT    = color_t(255, 128, 128);
const color_t COLOR_RED_BALANCED = color_t(220, 80, 80);
const color_t COLOR_RED_DARK     = color_t(150, 30, 30);

const color_t COLOR_ORANGE_LIGHT    = color_t(255, 180, 120);
const color_t COLOR_ORANGE_BALANCED = color_t(230, 120, 40);
const color_t COLOR_ORANGE_DARK     = color_t(160, 70, 20);

const color_t COLOR_YELLOW_LIGHT    = color_t(255, 255, 170);
const color_t COLOR_YELLOW_BALANCED = color_t(240, 220, 70);
const color_t COLOR_YELLOW_DARK     = color_t(170, 150, 30);

const color_t COLOR_GREEN_LIGHT    = color_t(150, 255, 150);
const color_t COLOR_GREEN_BALANCED = color_t(80, 200, 80);
const color_t COLOR_GREEN_DARK     = color_t(30, 120, 30);

const color_t COLOR_BLUE_LIGHT    = color_t(150, 200, 255);
const color_t COLOR_BLUE_BALANCED = color_t(70, 120, 220);
const color_t COLOR_BLUE_DARK     = color_t(30, 60, 150);

const color_t COLOR_PURPLE_LIGHT    = color_t(200, 150, 255);
const color_t COLOR_PURPLE_BALANCED = color_t(140, 70, 200);
const color_t COLOR_PURPLE_DARK     = color_t(90, 30, 130);

const color_t COLOR_VIOLET_LIGHT    = color_t(255, 150, 255);
const color_t COLOR_VIOLET_BALANCED = color_t(200, 70, 200);
const color_t COLOR_VIOLET_DARK     = color_t(120, 30, 120);

const color_t COLOR_WHITE = color_t(255, 255, 255);
const color_t COLOR_BLACK = color_t(0, 0, 0);
const color_t COLOR_GRAY  = color_t(127, 127, 127);
