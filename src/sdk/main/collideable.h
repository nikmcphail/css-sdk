#pragma once

#include "client_unknown.h"
#include "ray.h"
#include "trace.h"
#include "../misc/solid_type.h"

class vector3_t;
class qangle_t;
class matrix_3x4_t;
class i_client_unknown_t;
struct model_t;

class i_collideable_t {
public:
  virtual void*            get_entity_handle()                                           = 0;
  virtual const vector3_t& obb_mins_pre_scaled() const                                   = 0;
  virtual const vector3_t& obb_maxs_pre_scaled() const                                   = 0;
  virtual const vector3_t& obb_mins() const                                              = 0;
  virtual const vector3_t& obb_maxs() const                                              = 0;
  virtual void             world_space_trigger_bounds(vector3_t* world_mins,
                                                      vector3_t* world_maxs) const       = 0;
  virtual bool test_collision(const ray_t& ray, unsigned int contents_mask, trace_t& tr) = 0;
  virtual bool test_hitboxes(const ray_t& ray, unsigned int contents_mask, trace_t& tr)  = 0;
  virtual int  get_collision_model_index()                                               = 0;
  virtual const model_t*      get_collision_model()                                      = 0;
  virtual const vector3_t&    get_collision_origin() const                               = 0;
  virtual const qangle_t&     get_collision_angles() const                               = 0;
  virtual const matrix_3x4_t& collision_to_world_transform() const                       = 0;
  virtual solid_type_e        get_solid() const                                          = 0;
  virtual int                 get_solid_flags() const                                    = 0;
  virtual i_client_unknown_t* get_i_client_unknown()                                     = 0;
  virtual int                 get_collision_group() const                                = 0;
  virtual void world_space_surrounding_bounds(vector3_t* mins, vector3_t* maxs)          = 0;
  virtual bool should_touch_trigger(int trigger_solid_flags) const                       = 0;
  virtual const matrix_3x4_t* get_root_parent_to_world_transform() const                 = 0;
};