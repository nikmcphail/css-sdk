#pragma once

#include "client_unknown.h"
#include "client_renderable.h"
#include "client_networkable.h"
#include "client_thinkable.h"

class mouth_info_t;
struct spatialization_info_t;

class i_client_entity_t : public i_client_unknown_t,
                          public i_client_renderable_t,
                          public i_client_networkable_t,
                          public i_client_thinkable_t {
public:
  virtual void             release(void)                                         = 0;
  virtual const vector3_t& get_abs_origin(void) const                            = 0;
  virtual const qangle_t&  get_abs_angles(void) const                            = 0;
  virtual mouth_info_t*    get_mouth(void)                                       = 0;
  virtual bool             get_sound_spatialization(spatialization_info_t& info) = 0;

  template <typename t> inline t* as() { return reinterpret_cast<t*>(this); }
};