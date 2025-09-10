#include "addresses.h"

#include "src/library/utils.h"

bool addresses_t::collect_addresses() {
  {
    this->client.functions.get_bone_position = utils::find_pattern_in_memory(
        "client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 8B DA");
  }

  {
    this->client.structures.datamaps = utils::find_all_pattern_in_memory(
        "client.dll", "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 48 89 ?? ?? ?? ?? ?? C3");
    if (this->client.structures.datamaps.empty())
      return false;
  }

  {}

  return true;
}