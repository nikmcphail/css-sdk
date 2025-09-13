#pragma once

#include "../main/base_handle.h"
#include "src/core/core.h"

class i_client_entity_t;
class client_class_t;
class i_client_networkable_t;
class i_client_unknown_t;

class i_client_entity_list_t {
public:
  virtual i_client_networkable_t* get_client_networkable(int ent_num)                   = 0;
  virtual i_client_networkable_t* get_client_networkable_from_handle(base_handle_t ent) = 0;
  virtual i_client_unknown_t*     get_client_unknown_from_handle(base_handle_t ent)     = 0;
  virtual i_client_entity_t*      get_client_entity(int ent_num)                        = 0;
  virtual i_client_entity_t*      get_client_entity_from_handle(base_handle_t ent)      = 0;
  virtual int                     number_of_entities(bool include_non_networkable)      = 0;
  virtual int                     get_highest_entity_index(void)                        = 0;
  virtual void                    set_max_entities(int max_ents)                        = 0;
  virtual int                     get_max_entities()                                    = 0;
};

inline i_handle_entity_t* base_handle_t::get() const {
  return reinterpret_cast<i_handle_entity_t*>(
      core::g_interfaces.entity_list->get_client_entity_from_handle(index));
}