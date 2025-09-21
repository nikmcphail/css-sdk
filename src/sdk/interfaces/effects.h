#pragma once

#include "prediction_system.h"

#include <Windows.h>

class vector3_t;
class qangle_t;

class i_effects_t : public i_prediction_system_t {
public:
  virtual void beam(const vector3_t& start, const vector3_t& end, int model_index,
                    int halo_index, unsigned char frame_start, unsigned char frame_rate,
                    float life, unsigned char width, unsigned char end_width,
                    unsigned char fade_length, unsigned char noise, unsigned char red,
                    unsigned char green, unsigned char blue, unsigned char brightness,
                    unsigned char speed) = 0;

  virtual void smoke(const vector3_t& origin, int model_index, float scale,
                     float frame_rate)                                           = 0;
  virtual void sparks(const vector3_t& origin, int magnitude = 1, int trail_length = 1,
                      const vector3_t* direction = NULL)                         = 0;
  virtual void dust(const vector3_t& origin, const vector3_t& direction, float size,
                    float speed)                                                 = 0;
  virtual void muzzle_flash(const vector3_t& origin, const qangle_t& angles, float scale,
                            int type)                                            = 0;
  virtual void metal_sparks(const vector3_t& origin, const vector3_t& direction) = 0;
  virtual void energy_splash(const vector3_t& origin, const vector3_t& direction,
                             bool explosive = false)                             = 0;
  virtual void ricochet(const vector3_t& origin, const vector3_t& direction)     = 0;

  virtual float time()                                 = 0;
  virtual bool  is_server()                            = 0;
  virtual void  suppress_effects_sounds(bool suppress) = 0;
};