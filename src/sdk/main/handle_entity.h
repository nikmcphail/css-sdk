#pragma once

class base_handle_t;

class i_handle_entity_t {
public:
  virtual ~i_handle_entity_t() {}
  virtual void                 set_ref_e_handle(const base_handle_t& handle) = 0;
  virtual const base_handle_t& get_ref_e_handle() const                      = 0;
};