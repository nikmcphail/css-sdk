#pragma once

#include "app_system.h"
#include "../misc/analog_code.h"
#include "../misc/button_code.h"
#include "../misc/input_enums.h"

class i_steam_controller_t;

typedef __int64 controller_action_set_handle_t;

class i_input_system_t : public i_app_system_t {
public:
  virtual void                 attach_to_window(void* wnd)                                  = 0;
  virtual void                 detach_from_window()                                         = 0;
  virtual void                 enable_input(bool enable)                                    = 0;
  virtual void                 enable_message_pump(bool enable)                             = 0;
  virtual void                 poll_input_state()                                           = 0;
  virtual int                  get_poll_tick() const                                        = 0;
  virtual bool                 is_button_down(button_code_e code) const                     = 0;
  virtual int                  get_button_pressed_tick(button_code_e code) const            = 0;
  virtual int                  get_button_released_tick(button_code_e code) const           = 0;
  virtual int                  get_analog_value(analog_code_e code) const                   = 0;
  virtual int                  get_analog_delta(analog_code_e code) const                   = 0;
  virtual int                  get_event_count() const                                      = 0;
  virtual const input_event_t* get_event_data() const                                       = 0;
  virtual void                 post_user_event(const input_event_t& event)                  = 0;
  virtual int                  get_joystick_count() const                                   = 0;
  virtual void                 enable_joystick_input(int joystick, bool enable)             = 0;
  virtual void                 enable_joystick_diagonal_pov(int joystick, bool enable)      = 0;
  virtual void                 sample_devices(void)                                         = 0;
  virtual void                 set_rumble(float left_motor, float right_motor, int user_id) = 0;
  virtual void                 stop_rumble(void)                                            = 0;
  virtual void                 reset_input_state()                                          = 0;
  virtual void                 set_primary_user_id(int user_id)                             = 0;
  virtual const char*          button_code_to_string(button_code_e code) const              = 0;
  virtual const char*          analog_code_to_string(analog_code_e code) const              = 0;
  virtual button_code_e        string_to_button_code(const char* p_string) const            = 0;
  virtual analog_code_e        string_to_analog_code(const char* p_string) const            = 0;
  virtual void                 sleep_until_input(int max_sleep_time_ms = -1)                = 0;
  virtual button_code_e        virtual_key_to_button_code(int virtual_key) const            = 0;
  virtual int                  button_code_to_virtual_key(button_code_e code) const         = 0;
  virtual button_code_e        scan_code_to_button_code(int param) const                    = 0;
  virtual int                  get_poll_count() const                                       = 0;
  virtual void                 set_cursor_position(int x, int y)                            = 0;
  virtual void*                get_haptics_interface_address() const                        = 0;
  virtual void                 set_novint_pure(bool pure)                                   = 0;
  virtual bool                 get_raw_mouse_accumulators(int& x, int& y)                   = 0;
  virtual void                 set_console_text_mode(bool console_text_mode)                = 0;
  virtual i_steam_controller_t* steam_controller_interface()                                = 0;
  virtual __int32               get_num_steam_controllers_connected()                       = 0;
  virtual bool                  is_steam_controller_active()                                = 0;
  virtual bool                  is_steam_controller_connected()                             = 0;
  virtual int                   get_stam_controler_index_for_slot(int slot)                 = 0;
  virtual bool                  get_radial_menu_stick_values(int slot, float& x, float& y)  = 0;
  virtual void                  activate_steam_controller_action_set_for_slot(__int64           slot,
                                                                              game_action_set_e action_set) = 0;
  virtual controller_action_set_handle_t
  get_action_set_handle(game_action_set_e action_set)                                  = 0;
  virtual controller_action_set_handle_t get_action_set_handle(const char* action_set) = 0;
  virtual controller_action_origin_e
  get_steam_controller_action_origin(const char* action, game_action_set_e action_set) = 0;
  virtual controller_action_origin_e
  get_steam_controller_action_origin(const char*                    action,
                                     controller_action_set_handle_t action_set_handle) = 0;
  virtual const wchar_t*
  get_steam_controller_font_character_for_action_origin(controller_action_origin_e origin) = 0;
  virtual const wchar_t*
  get_steam_controller_description_for_action_origin(controller_action_origin_e origin) = 0;
  virtual void set_skip_controller_initilization(bool skip)                             = 0;
};