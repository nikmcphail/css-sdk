#pragma once

class i_client_unknown_t;
class client_think_handle_ptr_t;
typedef client_think_handle_ptr_t client_think_handle_t;

class i_client_thinkable_t {
public:
  virtual i_client_unknown_t*   get_i_client_unknown()                        = 0;
  virtual void                  client_think()                                = 0;
  virtual client_think_handle_t get_think_handle()                            = 0;
  virtual void                  set_think_handle(client_think_handle_t think) = 0;
  virtual void                  release();
};