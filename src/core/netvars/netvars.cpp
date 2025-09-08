#include "netvars.h"

#include "src/core/core.h"
#include "src/library/hash.h"

#include "src/sdk/main/recv.h"
#include "src/sdk/main/datamap.h"
#include "src/sdk/main/client_class.h"

#include "src/sdk/interfaces/base_client_dll.h"

#include <iomanip>

int netvars::get_offset(recv_table_t* table, const char* netvar) {
  auto u_hash = hash::hash_32(netvar);
  for (int i = 0; i < table->prop_count; i++) {
    recv_prop_t* prop = &table->props[i];
    if (u_hash == hash::hash_32(prop->var_name))
      return prop->offset;

    if (auto data_table = prop->data_table) {
      if (auto offset = get_offset(data_table, netvar))
        return offset + prop->offset;
    }
  }
  return 0;
}

int netvars::get_net_var(const char* class_name, const char* netvar) {
  auto u_hash = hash::hash_32(class_name);
  for (auto current_node = core::g_interfaces.base_client->get_all_classes(); current_node;
       current_node      = current_node->next) {
    if (u_hash == hash::hash_32(current_node->network_name))
      return get_offset(current_node->table, netvar);
  }

  return 0;
}

int netvars::get_data_var(const char* class_name, const char* field_name) {
  for (auto& addr : core::g_addresses.client.structures.datamaps) {
    datamap_t* map = reinterpret_cast<address_t&>(addr).rel32<datamap_t*>(13);
    if (!map || !map->dataClassName)
      continue;

    if (hash::hash_32(class_name) != hash::hash_32(map->dataClassName))
      continue;

    for (int i = 0; i < map->dataNumFields; i++) {
      typedescription_t* entry = &map->dataDesc[i];
      if (!entry || !entry->fieldName)
        continue;

      if (hash::hash_32(field_name) == hash::hash_32(entry->fieldName))
        return entry->fieldOffset[0];
    }

    // walk into base maps
    for (auto base = map->baseMap; base; base = base->baseMap) {
      for (int i = 0; i < base->dataNumFields; i++) {
        typedescription_t* entry = &base->dataDesc[i];
        if (!entry || !entry->fieldName)
          continue;

        if (hash::hash_32(field_name) == hash::hash_32(entry->fieldName))
          return entry->fieldOffset[0];
      }
    }
  }

  return 0;
}

recv_prop_t* netvars::get_prop(recv_table_t* table, const char* netvar) {
  auto u_hash = hash::hash_32(netvar);
  for (int i = 0; i < table->prop_count; i++) {
    recv_prop_t* prop = &table->props[i];
    if (u_hash == hash::hash_32(prop->var_name))
      return prop;

    if (auto data_table = prop->data_table) {
      if ((prop = get_prop(data_table, netvar)))
        return prop;
    }
  }

  return nullptr;
}

recv_prop_t* netvars::get_net_prop(const char* class_name, const char* netvar) {
  auto u_hash = hash::hash_32(class_name);
  for (auto current_node = core::g_interfaces.base_client->get_all_classes(); current_node;
       current_node      = current_node->next) {
    if (u_hash == hash::hash_32(current_node->network_name))
      return get_prop(current_node->table, netvar);
  }

  return nullptr;
}

void netvars::dump_table(std::ofstream& out, recv_table_t* table, int indent) {
  std::string pad(indent * 2, ' '); // 2 spaces per indent

  for (int i = 0; i < table->prop_count; i++) {
    recv_prop_t* prop = &table->props[i];
    if (!prop || !prop->var_name || !std::strlen(prop->var_name))
      continue;

    out << pad << std::setw(40 - indent * 2) << std::left << prop->var_name << " | Offset: 0x"
        << std::hex << prop->offset << std::dec << "\n";

    if (prop->data_table) {
      dump_table(out, prop->data_table, indent + 1);
    }
  }
}

// public function to dump all netvars
void netvars::dump_net_vars(const char* file_path) {
  std::ofstream out(file_path);
  if (!out.is_open())
    return;

  for (auto current_node = core::g_interfaces.base_client->get_all_classes(); current_node;
       current_node      = current_node->next) {
    if (!current_node->table || !current_node->network_name)
      continue;

    out << "Class: " << current_node->network_name << "\n";
    out << std::string(60, '-') << "\n";
    dump_table(out, current_node->table, 1);
    out << "\n\n";
  }
}

void netvars::dump_data_map(std::ofstream& out, datamap_t* map, int indent) {
  if (!map || !map->dataNumFields || map->dataNumFields > 200 || !map->dataDesc ||
      !map->dataClassName)
    return;

  std::string pad(indent * 2, ' ');
  out << pad << "Class: " << map->dataClassName << "\n";
  out << pad << std::string(60, '-') << "\n";

  for (int i = 0; i < map->dataNumFields; i++) {
    typedescription_t* entry = &map->dataDesc[i];
    if (!entry || !entry->fieldName)
      continue;

    out << pad << "  " << std::setw(40 - indent * 2) << std::left << entry->fieldName
        << " | Offset: 0x" << std::hex << entry->fieldOffset[0] << std::dec << "\n";
  }

  // recurse into base class datamap
  if (map->baseMap) {
    dump_data_map(out, map->baseMap, indent + 1);
  }

  out << "\n";
}

void netvars::dump_all_data_maps(const char* file_path) {
  std::ofstream out(file_path);
  if (!out.is_open())
    return;

  // loop over all stored datamap addresses
  for (auto& addr : core::g_addresses.client.structures.datamaps) {
    datamap_t* map = reinterpret_cast<address_t&>(addr).rel32<datamap_t*>(13);
    dump_data_map(out, map, 0);
  }
}

void netvars::dump_class_ids(const char* file_path) {
  std::ofstream out(file_path);
  if (!out.is_open())
    return;

  out << "#pragma once\n\n";
  out << "enum cs_class_ids_e {\n";

  for (auto current_node = core::g_interfaces.base_client->get_all_classes(); current_node;
       current_node      = current_node->next) {
    if (!current_node->network_name)
      continue;

    // Use the actual engine-assigned ID
    out << "    " << current_node->network_name << " = " << current_node->id << ",\n";
  }

  out << "};\n";
}