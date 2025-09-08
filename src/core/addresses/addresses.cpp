#include "addresses.h"

#include "src/library/utils.h"

bool addresses_t::collect_addresses() {
  {}

  {
    this->client.structures.datamaps = utils::find_all_pattern_in_memory(
        "client.dll", "C7 05 ?? ?? ?? ?? ?? ?? ?? ?? 48 89 ?? ?? ?? ?? ?? C3");
    if (this->client.structures.datamaps.empty())
      return false;
  }

  {}

  return true;
}