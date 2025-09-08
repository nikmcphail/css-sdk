#pragma once

#include "interface.h"

struct app_system_info_t {
  const char* module_name;
  const char* interface_name;
};

enum init_return_val_e {
  INIT_FAILED = 0,
  INIT_OK,

  INIT_LAST_VAL,
};

enum app_system_tier_e {
  APP_SYSTEM_TIER0 = 0,
  APP_SYSTEM_TIER1,
  APP_SYSTEM_TIER2,
  APP_SYSTEM_TIER3,

  APP_SYSTEM_TIER_OTHER,
};

class i_app_system_t {
public:
  virtual bool              connect(create_interface_fn factory) = 0;
  virtual void              disconnect();
  virtual void*             query_interface(const char* interface_name) = 0;
  virtual init_return_val_e init()                                      = 0;
  virtual void              shutdown()                                  = 0;
};