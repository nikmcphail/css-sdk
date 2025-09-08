#pragma once

#include "app_system.h"
#include "../main/convar.h"
#include "../misc/color.h"

typedef int cvar_dll_identifier_t;

class i_console_display_func_t {
public:
  virtual void color_print(const color_t& clr, const char* message) = 0;
  virtual void print(const char* message)                           = 0;
  virtual void dprint(const char* message)                          = 0;
};

class i_cvar_query_t : public i_app_system_t {
public:
  virtual bool are_convars_linkable(const convar_t* child, const convar_t* parent) = 0;
};

class i_cvar_t : public i_app_system_t {
public:
  virtual cvar_dll_identifier_t allocate_dll_identifier()                                = 0;
  virtual void                  register_con_command(con_command_base_t* command_base)   = 0;
  virtual void                  unregister_con_command(con_command_base_t* command_base) = 0;
  virtual void                  unregister_con_commands(cvar_dll_identifier_t id)        = 0;
  virtual const char*           get_command_line_value(const char* variable_name)        = 0;
  virtual con_command_base_t*   find_command_base(const char* name)                      = 0;
  virtual const con_command_base_t* find_command_base(const char* name) const            = 0;
  virtual convar_t*                 find_var(const char* var_name)                       = 0;
  virtual const convar_t*           find_var(const char* var_name) const                 = 0;
  virtual con_command_t*            find_command(const char* name)                       = 0;
  virtual const con_command_t*      find_command(const char* name) const                 = 0;
  virtual con_command_base_t*       get_commands(void)                                   = 0;
  virtual const con_command_base_t* get_commands(void) const                             = 0;
  virtual void install_global_change_callback(fn_change_callback_t callback)             = 0;
  virtual void remove_global_change_callback(fn_change_callback_t callback)              = 0;
  virtual void call_global_change_callbacks(convar_t* var, const char* old_string,
                                            float old_float_value)                       = 0;
  virtual void install_console_display_func(i_console_display_func_t* display_func)      = 0;
  virtual void remove_console_display_func(i_console_display_func_t* display_func)       = 0;
  virtual void console_color_printf(const color_t& color, const char* format, ...) const = 0;
  virtual void console_printf(const char* format, ...) const                             = 0;
  virtual void console_dprintf(const char* format, ...) const                            = 0;
  virtual void revert_flagges_convars(int flag)                                          = 0;
  virtual void install_cvar_query(i_cvar_query_t* query)                                 = 0;
  virtual bool is_material_thread_set_allowed() const                                    = 0;
  virtual void queue_material_thread_set_value(convar_t* convar, const char* value)      = 0;
  virtual void queue_material_thread_set_value(convar_t* convar, int value)              = 0;
  virtual void queue_material_thread_set_value(convar_t* convar, float value)            = 0;
  virtual bool has_queued_material_thread_convar_sets() const                            = 0;
  virtual int  process_queued_material_thread_convar_sets()                              = 0;

  class i_cvar_iterator_internal {
  public:
    virtual ~i_cvar_iterator_internal() {};
    virtual void                set_first(void) = 0;
    virtual void                next(void)      = 0;
    virtual bool                is_valid(void)  = 0;
    virtual con_command_base_t* get(void)       = 0;
  };

  class iterator_t {
  public:
    inline iterator_t(i_cvar_t* cvar);
    inline ~iterator_t(void);
    inline void                set_first(void);
    inline void                next(void);
    inline bool                is_valid(void);
    inline con_command_base_t* get(void);

  private:
    i_cvar_iterator_internal* iter;
  };

  virtual i_cvar_iterator_internal* factory_internal_iterator(void) = 0;
};

inline i_cvar_t::iterator_t::iterator_t(i_cvar_t* cvar) {
  iter = cvar->factory_internal_iterator();
}

inline i_cvar_t::iterator_t::~iterator_t(void) {
  // delete iter;
}

inline void i_cvar_t::iterator_t::set_first(void) { iter->set_first(); }

inline void i_cvar_t::iterator_t::next(void) { iter->next(); }

inline bool i_cvar_t::iterator_t::is_valid(void) { return iter->is_valid(); }

inline con_command_base_t* i_cvar_t::iterator_t::get(void) { return iter->get(); }