#pragma once

class vector3_t;
class qangle_t;
class overlay_text_t;
struct color_t;

// Do not use this as a main means to render, if you try to draw too much with it you will
// experience MASSIVE fps loss. Also, make sure to clear overlays before drawing. (Also, I'm
// pretty sure a lot of these functions just don't do anything?)

class iv_debug_overlay_t {
public:
  virtual void add_entity_text_overlay(int ent_index, int line_offset, float duration, int r,
                                       int g, int b, int a, const char* format, ...) = 0;
  virtual void add_box_overlay(const vector3_t& origin, const vector3_t& mins,
                               const vector3_t& max, qangle_t const& orientation, int r, int g,
                               int b, int a, float duration)                         = 0;
  virtual void add_triangle_overlay(const vector3_t& point_one, const vector3_t& point_two,
                                    const vector3_t& point_three, int r, int g, int b, int a,
                                    bool no_depth_test, float duration)              = 0;
  virtual void add_line_overlay(const vector3_t& origin, const vector3_t& destination, int r,
                                int g, int b, bool no_depth_test, float duration)    = 0;
  virtual void add_text_overlay(const vector3_t& origin, float duration, const char* format,
                                ...)                                                 = 0;
  virtual void add_text_overlay(const vector3_t& origin, int line_offset, float duration,
                                const char* format, ...)                             = 0;
  virtual void add_screen_text_overlay(float x_pos, float y_pos, float duration, int r, int g,
                                       int b, int a, const char* text)               = 0;
  virtual void add_swept_box_overlay(const vector3_t& start, const vector3_t& end,
                                     const vector3_t& mins, const vector3_t& max,
                                     const qangle_t& angles, int r, int g, int b, int a,
                                     float duration)                                 = 0;
  virtual void add_grid_overlay(const vector3_t& origin)                             = 0;
  virtual int  screen_position(const vector3_t& point, vector3_t& screen)            = 0;
  virtual int  screen_position(float x_pos, float y_pos, vector3_t& screen)          = 0;

  virtual overlay_text_t* get_first(void)                   = 0;
  virtual overlay_text_t* get_next(overlay_text_t* current) = 0;
  virtual void            clear_dead_overlays(void)         = 0;
  virtual void            clear_all_overlays()              = 0;

  virtual void add_text_overlay_rgb(const vector3_t& origin, int line_offset, float duration,
                                    float r, float g, float b, float alpha, const char* format,
                                    ...)                                                 = 0;
  virtual void add_text_overlay_rgb(const vector3_t& origin, int line_offset, float duration,
                                    int r, int g, int b, int a, const char* format, ...) = 0;

  virtual void add_line_overlay_alpha(const vector3_t& origin, const vector3_t& destination,
                                      int r, int g, int b, int a, bool no_depth_test,
                                      float duration) = 0;
  virtual void add_box_overlay_2(const vector3_t& origin, const vector3_t& mins,
                                 const vector3_t& max, qangle_t const& orientation,
                                 const color_t& face_color, const color_t& edge_color,
                                 float duration)      = 0;

  virtual void add_screen_text_overlay_2(float x_pos, float y_pos, int line, float duration,
                                         int r, int g, int b, int a, const char* text) = 0;

  // misyl: compat.
  // must be a 2 otherwise msvc will dump overloads in the middle of the vtable
  inline void add_screen_text_overlay(float x_pos, float y_pos, int line, float duration, int r,
                                      int g, int b, int a, const char* text) {
    this->add_screen_text_overlay_2(x_pos, y_pos, line, duration, r, g, b, a, text);
  }

private:
  inline void add_text_overlay(const vector3_t& origin, int line_offset, float duration, int r,
                               int g, int b, int a, const char* format, ...) {
  } /* catch improper use of bad interface. Needed because '0' duration can be resolved by
       compiler to NULL format string (i.e., compiles but calls wrong function) */
};