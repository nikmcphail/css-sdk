#pragma once

#include "../misc/beam.h"

class i_view_render_beams_t {
public:
  virtual void init_beams(void)     = 0;
  virtual void shutdown_beams(void) = 0;
  virtual void clear_beams(void)    = 0;

  // Updates the state of the temp ent beams
  virtual void update_temp_ent_beams() = 0;

  virtual void draw_beam(base_entity_t* beam, i_trace_filter_t* beam_trace_filter = NULL) = 0;
  virtual void draw_beam(beam_t* beam)                                                    = 0;

  virtual void kill_dead_beams(base_entity_t* ent) = 0;

  // New interfaces!
  virtual beam_t* create_beam_ents(beam_info_t& info)          = 0;
  virtual beam_t* create_beam_ent_point(beam_info_t& info)     = 0;
  virtual beam_t* create_beam_points(beam_info_t& info)        = 0;
  virtual beam_t* create_beam_ring(beam_info_t& info)          = 0;
  virtual beam_t* create_beam_ring_point(beam_info_t& info)    = 0;
  virtual beam_t* create_beam_circle_points(beam_info_t& info) = 0;
  virtual beam_t* create_beam_follow(beam_info_t& info)        = 0;

  virtual void free__beam(beam_t* beam)                          = 0;
  virtual void update_beam_info(beam_t* beam, beam_info_t& info) = 0;

  // These will go away!
  virtual void create_beam_ents(int start_ent, int end_ent, int model_index, int halo_index,
                                float halo_scale, float life, float width, float end_width,
                                float fade_length, float amplitude, float brightness,
                                float speed, int start_frame, float frame_rate, float r,
                                float g, float b, int type = -1)               = 0;
  virtual void create_beam_ent_point(int start_ent, const vector3_t* start, int end_entity,
                                     const vector3_t* end, int model_index, int halo_index,
                                     float halo_scale, float life, float width, float end_width,
                                     float fade_length, float amplitude, float brightness,
                                     float speed, int start_frame, float frame_rate, float r,
                                     float g, float b)                         = 0;
  virtual void create_beam_points(vector3_t& start, vector3_t& end, int model_index,
                                  int halo_index, float halo_scale, float life, float width,
                                  float end_width, float fade_length, float amplitude,
                                  float brightness, float speed, int start_frame,
                                  float frame_rate, float r, float g, float b) = 0;
  virtual void create_beam_ring(int start_ent, int end_ent, int model_index, int halo_index,
                                float halo_scale, float life, float width, float end_width,
                                float fade_length, float amplitude, float brightness,
                                float speed, int start_frame, float frame_rate, float r,
                                float g, float b, int flags = 0)               = 0;
  virtual void create_beam_ring_point(const vector3_t& center, float start_radius,
                                      float end_radius, int model_index, int halo_index,
                                      float halo_scale, float life, float width,
                                      float end_width, float fade_length, float amplitude,
                                      float brightness, float speed, int start_frame,
                                      float frame_rate, float r, float g, float b,
                                      int flags = 0)                           = 0;
  virtual void create_beam_circle_points(int type, vector3_t& start, vector3_t& end,
                                         int model_index, int halo_index, float halo_scale,
                                         float life, float width, float end_width,
                                         float fade_length, float amplitude, float brightness,
                                         float speed, int start_frame, float frame_rate,
                                         float r, float g, float b)            = 0;
  virtual void create_beam_follow(int start_ent, int model_index, int halo_index,
                                  float halo_scale, float life, float width, float end_width,
                                  float fade_length, float r, float g, float b,
                                  float brightness)                            = 0;
};