#pragma once

#include "handle_entity.h"

class i_collideable_t;
class i_client_networkable_t;
class i_client_renderable_t;
class i_client_entity_t;
class base_entity_t;
class i_client_thinkable_t;

class i_client_unknown_t : public i_handle_entity_t {
public:
  virtual i_collideable_t*        get_collideable()        = 0;
  virtual i_client_networkable_t* get_client_networkable() = 0;
  virtual i_client_renderable_t*  get_client_renderable()  = 0;
  virtual i_client_entity_t*      get_i_client_entity()    = 0;
  virtual base_entity_t*          get_base_entity()        = 0;
  virtual i_client_thinkable_t*   get_client_thinkable()   = 0;
};