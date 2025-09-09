#pragma once

#include "base_interface.h"

class i_game_console_t : public i_base_interface_t {
public:
  virtual void activate()                      = 0;
  virtual void initialize()                    = 0;
  virtual void hide()                          = 0;
  virtual void clear()                         = 0;
  virtual bool is_console_visible()            = 0;
  virtual void set_parent(unsigned int parent) = 0; // vgui:VPANEL
};