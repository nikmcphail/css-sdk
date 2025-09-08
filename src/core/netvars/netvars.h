#pragma once

#include <fstream>

class recv_table_t;
class recv_prop_t;
class datamap_t;

namespace netvars {
  int get_offset(recv_table_t* table, const char* netvar);

  int get_net_var(const char* class_name, const char* netvar);

  int get_data_var(const char* class_name, const char* field_name);

  recv_prop_t* get_prop(recv_table_t* table, const char* netvar);

  recv_prop_t* get_net_prop(const char* class_name, const char* netvar);

  void dump_table(std::ofstream& out, recv_table_t* table, int indent = 0);

  void dump_net_vars(const char* file_path);

  void dump_data_map(std::ofstream& out, datamap_t* map, int indent = 0);

  void dump_all_data_maps(const char* file_path);

  void dump_class_ids(const char* file_path);
} // namespace netvars

#define NETVAR(_name, type, table, name)                                                       \
  inline type& _name() {                                                                       \
    static int offset = netvars::get_net_var(table, name);                                     \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset);                                 \
  }

#define NETVAR_OFF(_name, type, table, name, _offset)                                          \
  inline type& _name() {                                                                       \
    static int offset = netvars::get_net_var(table, name) + _offset;                           \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset);                                 \
  }

#define NETVAR_ARRAY(_name, type, table, name)                                                 \
  inline type& _name(int index) {                                                              \
    static int offset = netvars::get_net_var(table, name);                                     \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset + index * sizeof(type));          \
  }

#define NETVAR_ARRAY_OFF(_name, type, table, name, _offset)                                    \
  inline type& _name(int index) {                                                              \
    static int offset = netvars::get_net_var(table, name) + _offset;                           \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset + index * sizeof(type));          \
  }

#define DATAMAP(_name, type, table, name)                                                      \
  inline type& _name() {                                                                       \
    static int offset = netvars::get_data_var(table, name);                                    \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset);                                 \
  }

#define DATAMAP_OFF(_name, type, table, name, _offset)                                         \
  inline type& _name() {                                                                       \
    static int offset = netvars::get_data_var(table, name) + _offset;                          \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset);                                 \
  }

#define DATAMAP_ARRAY(_name, type, table, name)                                                \
  inline type& _name(int index) {                                                              \
    static int offset = netvars::get_data_var(table, name);                                    \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset + index * sizeof(type));          \
  }

#define DATAMAP_ARRAY_OFF(_name, type, table, name, _offset)                                   \
  inline type& _name(int index) {                                                              \
    static int offset = netvars::get_data_var(table, name) + _offset;                          \
    return *reinterpret_cast<type*>(uintptr_t(this) + offset + index * sizeof(type));          \
  }