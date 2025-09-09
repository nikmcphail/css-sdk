#pragma once

#include <basetsd.h>
#include <cstdint>
#include <vector>
#include <string>
#include "address.h"

namespace utils {
  template <typename T> T get_virtual_function(void* base, std::uint16_t index) noexcept {
    return (*static_cast<T**>(base))[index];
  }

  std::vector<uintptr_t> find_all_pattern_in_memory(const char* module_name,
                                                    const char* pattern);

  std::string get_module_offset(uintptr_t address);

  inline std::string get_module_offset(void* address) {
    return get_module_offset(uintptr_t(address));
  }

  address_t find_pattern_in_memory(const char* module_name, const char* pattern);

  ULONG64 get_export(const char* module, const char* exp);
} // namespace utils