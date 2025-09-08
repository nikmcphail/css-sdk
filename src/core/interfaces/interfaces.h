#pragma once

class i_cvar_t;
class i_base_client_dll_t;

class interfaces_t {
public:
  i_cvar_t*            cvar{nullptr};
  i_base_client_dll_t* base_client{nullptr};

  bool collect_interfaces();
};