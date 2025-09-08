#pragma once

class i_cvar_t;

class interfaces_t {
public:
  i_cvar_t* cvar{nullptr};

  bool collect_interfaces();
};