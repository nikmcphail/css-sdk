#pragma once

#include "src/sdk/interfaces/base_interface.h"

#define MAX_EVENT_NAME_LENGTH 32
#define MAX_EVENT_BITS        9
#define MAX_EVENT_NUMBER      (1 << MAX_EVENT_BITS)
#define MAX_EVENT_BYTES       1024

class key_values_t;
class game_event_t;
class bf_read_t;
class bf_write_t;

class i_game_event_t {
public:
  virtual ~i_game_event_t() {};
  virtual const char* get_name() const                                                      = 0;
  virtual bool        is_reliable() const                                                   = 0;
  virtual bool        is_local() const                                                      = 0;
  virtual bool        is_empty(const char* key_name = nullptr)                              = 0;
  virtual bool        get_bool(const char* key_name = nullptr, bool default_value = false)  = 0;
  virtual int         get_int(const char* key_name = nullptr, int default_value = 0)        = 0;
  virtual float       get_float(const char* key_name = nullptr, float default_value = 0.0f) = 0;
  virtual const char* get_string(const char* key_name      = nullptr,
                                 const char* default_value = "")                            = 0;
  virtual void        set_bool(const char* key_name, bool value)                            = 0;
  virtual void        set_int(const char* key_name, int value)                              = 0;
  virtual void        set_float(const char* key_name, float value)                          = 0;
  virtual void        set_string(const char* key_name, const char* value)                   = 0;
};

class i_game_event_listener_2_t {
public:
  virtual ~i_game_event_listener_2_t(void) {};
  virtual void fire_game_event(game_event_t* event) = 0;
};

class i_game_event_manager_2_t : public i_base_interface_t {
public:
  virtual ~i_game_event_manager_2_t(void) {};
  virtual int  load_events_from_file(const char* file_name)                          = 0;
  virtual void reset()                                                               = 0;
  virtual bool add_listener(i_game_event_listener_2_t* listener, const char* name,
                            bool bServerSide)                                        = 0;
  virtual bool find_listener(i_game_event_listener_2_t* listener, const char* name)  = 0;
  virtual void remove_listener(i_game_event_listener_2_t* listener)                  = 0;
  virtual game_event_t* create_event(const char* name, bool force = false)           = 0;
  virtual bool          fire_event(game_event_t* event, bool dont_broadcast = false) = 0;
  virtual bool          fire_event_client_side(game_event_t* event)                  = 0;
  virtual game_event_t* duplicate_event(game_event_t* event)                         = 0;
  virtual void          free_event(game_event_t* event)                              = 0;
  virtual bool          serialize_event(game_event_t* event, bf_write_t* buf)        = 0;
  virtual game_event_t* unserialize_event(bf_read_t* buf)                            = 0;
};