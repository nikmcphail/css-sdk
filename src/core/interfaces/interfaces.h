#pragma once

class i_cvar_t;
class i_base_client_dll_t;
class i_game_console_t;
class i_client_entity_list_t;
class i_engine_trace_t;
class iv_engine_client_t;
class i_input_system_t;
class i_game_event_manager_2_t;
class i_view_render_beams_t;
class IDirect3DDevice9;
class client_state_t;
class i_surface_t;
class global_vars_base_t;
class i_prediction_t;

class interfaces_t {
public:
  i_cvar_t*                 cvar{nullptr};
  i_base_client_dll_t*      base_client{nullptr};
  i_game_console_t*         game_console{nullptr};
  i_client_entity_list_t*   entity_list{nullptr};
  i_engine_trace_t*         engine_trace{nullptr};
  iv_engine_client_t*       engine_client{nullptr};
  i_input_system_t*         input_system{nullptr};
  i_game_event_manager_2_t* game_event{nullptr};
  i_view_render_beams_t*    render_beams{nullptr};
  IDirect3DDevice9*         directx_device{nullptr};
  client_state_t*           client_state{nullptr};
  i_surface_t*              surface{nullptr};
  global_vars_base_t*       global_vars{nullptr};
  i_prediction_t*           prediction{nullptr};

  bool collect_interfaces();
};