#pragma once

#include <stddef.h>

#define FCVAR_NONE                    0
#define FCVAR_UNREGISTERED            (1 << 0)
#define FCVAR_DEVELOPMENTONLY         (1 << 1)
#define FCVAR_GAMEDLL                 (1 << 2)
#define FCVAR_CLIENTDLL               (1 << 3)
#define FCVAR_HIDDEN                  (1 << 4)
#define FCVAR_PROTECTED               (1 << 5)
#define FCVAR_SPONLY                  (1 << 6)
#define FCVAR_ARCHIVE                 (1 << 7)
#define FCVAR_NOTIFY                  (1 << 8)
#define FCVAR_USERINFO                (1 << 9)
#define FCVAR_CHEAT                   (1 << 14)
#define FCVAR_PRINTABLEONLY           (1 << 10)
#define FCVAR_UNLOGGED                (1 << 11)
#define FCVAR_NEVER_AS_STRING         (1 << 12)
#define FCVAR_REPLICATED              (1 << 13)
#define FCVAR_DEMO                    (1 << 16)
#define FCVAR_DONTRECORD              (1 << 17)
#define FCVAR_RELOAD_MATERIALS        (1 << 20)
#define FCVAR_RELOAD_TEXTURES         (1 << 21)
#define FCVAR_NOT_CONNECTED           (1 << 22)
#define FCVAR_MATERIAL_SYSTEM_THREAD  (1 << 23)
#define FCVAR_ARCHIVE_XBOX            (1 << 24)
#define FCVAR_ACCESSIBLE_FROM_THREADS (1 << 25)
#define FCVAR_SERVER_CAN_EXECUTE      (1 << 28)
#define FCVAR_SERVER_CANNOT_QUERY     (1 << 29)
#define FCVAR_CLIENTCMD_CAN_EXECUTE   (1 << 30)
#define FCVAR_EXEC_DESPITE_DEFAULT    (1 << 31)
#define FCVAR_INTERNAL_USE            (1 << 15)
#define FCVAR_ALLOWED_IN_COMPETITIVE  (1 << 18)
#define FCVAR_MATERIAL_THREAD_MASK                                                             \
  (FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD)

class i_convar_t;
class convar_t;
class command_t;
class con_command_t;
class con_command_base_t;

class con_command_base_accessor_t {
public:
  virtual bool register_con_command_base(con_command_base_t* var) = 0;
};

typedef void (*fn_command_callback_void_t)(void);
typedef void (*fn_command_callback_t)(const command_t& command);

#define COMMAND_COMPLETION_MAXITEMS    64
#define COMMAND_COMPLETION_ITEM_LENGTH 64

typedef int (*fn_command_completion_callback_t)(
    const char* partial,
    char        commands[COMMAND_COMPLETION_MAXITEMS][COMMAND_COMPLETION_ITEM_LENGTH]);

class i_command_callback_t {
public:
  virtual void command_callback(const command_t& command) = 0;
};

class i_command_completion_callback_t {
public:
  virtual int command_completion_callback(const char* partial,
                                          void*&      commands) = 0; // CUtlVector
};

class con_command_base_t {
public:
  virtual ~con_command_base_t(void)                                                      = 0;
  virtual bool        is_command(void) const                                             = 0;
  virtual bool        is_flag_set(int flag) const                                        = 0;
  virtual void        add_flags(int flags)                                               = 0;
  virtual const char* get_name(void) const                                               = 0;
  virtual const char* get_help_text(void) const                                          = 0;
  virtual bool        is_registered(void) const                                          = 0;
  virtual void*       get_dll_identifier() const                                         = 0;
  virtual void create_base(const char* name, const char* help_string = 0, int flags = 0) = 0;
  virtual void init()                                                                    = 0;

  con_command_base_t* next;
  bool                registered;
  const char*         name;
  const char*         help_string;
  int                 flags;

protected:
  static con_command_base_t*          con_command_bases;
  static con_command_base_accessor_t* accessor;
};

enum { COMMAND_MAX_ARGC = 64, COMMAND_MAX_LENGTH = 512 };

class command_t {
public:
  int          arg_c() const;
  const char** arg_v() const;
  const char*  arg_s() const;
  const char*  get_command_string() const;
  const char*  operator[](int index) const;
  const char*  arg(int index) const;

  int         arg_c_count;
  int         arg_v_size;
  char        arg_s_buffer[COMMAND_MAX_LENGTH];
  char        arg_v_buffer[COMMAND_MAX_LENGTH];
  const char* pp_argv[COMMAND_MAX_ARGC];
};
inline int          command_t::arg_c() const { return arg_c_count; }
inline const char** command_t::arg_v() const {
  return arg_c_count ? (const char**)pp_argv : NULL;
}
inline const char* command_t::arg_s() const {
  return arg_v_size ? &arg_s_buffer[arg_v_size] : "";
}
inline const char* command_t::get_command_string() const {
  return arg_c_count ? arg_s_buffer : "";
}
inline const char* command_t::operator[](int index) const { return arg(index); }
inline const char* command_t::arg(int index) const {
  if (index < 0 || index >= arg_c_count)
    return "";
  return pp_argv[index];
}

typedef void (*fn_change_callback_t)(i_convar_t* var, const char* old_value,
                                     float old_float_value);

class i_convar_t {
public:
  virtual void        set_value(const char* value) = 0;
  virtual void        set_value(float value)       = 0;
  virtual void        set_value(int value)         = 0;
  virtual const char* get_name(void) const         = 0;
  virtual bool        is_flag_set(int flag) const  = 0;
};

class con_command_t : public con_command_base_t {
public:
  virtual ~con_command_t(void)        = 0;
  virtual bool is_command(void) const = 0;
  virtual int  auto_complete_suggest(const char* partial, void*& commands); // CUtlVector
  virtual bool can_auto_complete(void)      = 0;
  virtual void dispatch(command_t& command) = 0;

private:
  union {
    fn_command_callback_void_t command_callback_v1_func;
    fn_command_callback_t      command_callback_func;
    i_command_callback_t*      command_callback_ptr;
  };

  union {
    fn_command_completion_callback_t completion_callback_func;
    i_command_completion_callback_t* completion_callback_ptr;
  };

  bool has_completion_callbackc : 1;
  bool using_new_command_callback : 1;
  bool using_command_callback_interface : 1;
};

class convar_t : public con_command_base_t, public i_convar_t {
public:
  virtual ~convar_t(void) {};
  virtual bool        is_flag_set(int flag) const = 0;
  virtual const char* get_help_text(void) const   = 0;
  virtual bool        is_registered(void) const   = 0;
  virtual const char* get_name(void) const        = 0;
  virtual void        add_flags(int flags)        = 0;
  virtual bool        is_command(void) const      = 0;

  inline float       get_float(void) const;
  inline int         get_int(void) const;
  inline bool        get_bool() const { return !!get_int(); }
  inline char const* get_string(void) const;

  virtual void set_value(const char* value) = 0;
  virtual void set_value(float value)       = 0;
  virtual void set_value(int value)         = 0;

private:
  virtual void internal_set_value(const char* value)                         = 0;
  virtual void internal_set_float_value(float new_value, bool force = false) = 0;
  virtual void internal_set_int_value(int value)                             = 0;
  virtual bool clamp_value(float& value)                                     = 0;
  virtual void change_string_value(const char* temp_value, float old_value)  = 0;
  virtual void init()                                                        = 0;

  int get_flags() { return parent->flags; }

public:
  convar_t*            parent;
  const char*          default_value;
  char*                psz_string;
  int                  string_length;
  float                float_value;
  int                  int_value;
  bool                 has_min;
  float                min_val;
  bool                 has_max;
  float                max_val;
  bool                 has_comp_min;
  float                comp_min_val;
  bool                 has_comp_max;
  float                comp_max_val;
  bool                 competitive_restrictions;
  fn_change_callback_t change_callback;
};

inline float convar_t::get_float(void) const { return parent->float_value; }

inline int convar_t::get_int(void) const { return parent->int_value; }

inline const char* convar_t::get_string(void) const {
  if (flags & FCVAR_NEVER_AS_STRING)
    return "FCVAR_NEVER_AS_STRING";

  return (parent->psz_string) ? parent->psz_string : "";
}