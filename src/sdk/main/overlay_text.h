#pragma once

#include "vector3.h"

class overlay_text_t {
public:
  overlay_text_t() {
    next_overlay_text = 0;
    origin.initialize();
    use_origin    = false;
    line_offset   = 0;
    x_pos         = 0;
    y_pos         = 0;
    text[0]       = 0;
    end_time      = 0.0f;
    server_count  = -1;
    creation_tick = -1;
    r = g = b = a = 255;
  }

  vector3_t       origin;
  bool            use_origin;
  int             line_offset;
  float           x_pos;
  float           y_pos;
  char            text[512];
  float           end_time;
  int             creation_tick;
  int             server_count;
  int             r;
  int             g;
  int             b;
  int             a;
  overlay_text_t* next_overlay_text;
};