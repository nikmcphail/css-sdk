#include "utils.h"

#include <Windows.h>
#include <Psapi.h>
#include "fmt/core.h"

std::vector<uintptr_t> utils::find_all_pattern_in_memory(const char* module_name,
                                                         const char* pattern) {
  uintptr_t mod = (uintptr_t)GetModuleHandleA(module_name);
  if (!mod)
    return {};

  uint8_t* base = (uint8_t*)mod;

  static std::vector<uintptr_t> patterns = {};
  patterns.clear();

  static auto pattern_to_byte = [](const char* pattern) {
    auto       bytes = std::vector<int>{};
    const auto start = const_cast<char*>(pattern);
    const auto end   = const_cast<char*>(pattern) + std::strlen(pattern);

    for (auto current = start; current < end; ++current) {
      if (*current == '?') {
        ++current;

        if (*current == '?')
          ++current;

        bytes.push_back(-1);
      } else {
        bytes.push_back(std::strtoul(current, &current, 16));
      }
    }
    return bytes;
  };

  const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
  const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(
      reinterpret_cast<std::uint8_t*>(base) + dos_header->e_lfanew);

  const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
  const auto pattern_bytes = pattern_to_byte(pattern);
  const auto scan_bytes    = reinterpret_cast<std::uint8_t*>(base);

  const auto s = pattern_bytes.size();
  const auto d = pattern_bytes.data();

  for (auto i = 0ul; i < size_of_image - s; ++i) {
    auto found = true;

    for (auto j = 0ul; j < s; ++j) {
      if (scan_bytes[i + j] != d[j] && d[j] != -1) {
        found = false;
        break;
      }
    }

    if (found)
      patterns.push_back((uintptr_t)(&scan_bytes[i]));
  }

  return patterns;
}

address_t utils::find_pattern_in_memory(const char* module_name, const char* pattern) {
  uintptr_t mod = (uintptr_t)GetModuleHandleA(module_name);
  if (!mod)
    return {};

  uint8_t* base = (uint8_t*)mod;

  static auto pattern_to_byte = [](const char* pattern) {
    auto       bytes = std::vector<int>{};
    const auto start = const_cast<char*>(pattern);
    const auto end   = const_cast<char*>(pattern) + std::strlen(pattern);

    for (auto current = start; current < end; ++current) {
      if (*current == '?') {
        ++current;

        if (*current == '?')
          ++current;

        bytes.push_back(-1);
      } else {
        bytes.push_back(std::strtoul(current, &current, 16));
      }
    }
    return bytes;
  };

  const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(base);
  const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(
      reinterpret_cast<std::uint8_t*>(base) + dos_header->e_lfanew);

  const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
  const auto pattern_bytes = pattern_to_byte(pattern);
  const auto scan_bytes    = reinterpret_cast<std::uint8_t*>(base);

  const auto s = pattern_bytes.size();
  const auto d = pattern_bytes.data();

  for (auto i = 0ul; i < size_of_image - s; ++i) {
    auto found = true;

    for (auto j = 0ul; j < s; ++j) {
      if (scan_bytes[i + j] != d[j] && d[j] != -1) {
        found = false;
        break;
      }
    }

    if (found) {
      return address_t{&scan_bytes[i]};
    }
  }

  return {};
}

std::string utils::get_module_offset(uintptr_t address) {
  HMODULE module;
  if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                             GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                         LPCSTR(address), &module))
    return fmt::format("{:#x}", address);

  uintptr_t base = uintptr_t(module);
  if (char buffer[MAX_PATH];
      GetModuleBaseName(GetCurrentProcess(), module, buffer, sizeof(buffer) / sizeof(char)))
    return fmt::format("{}+{:#x}", buffer, address - base);

  return fmt::format("{:#x}+{:#x}", base, address - base);
}

ULONG64 utils::get_export(const char* module, const char* exp) {
  return (ULONG64)GetProcAddress(GetModuleHandleA(module), exp);
}

std::vector<byte> utils::pattern_to_byte(const char* pattern) {
  std::vector<byte> _pattern = {};

  const auto start = const_cast<char*>(pattern);
  const auto end   = const_cast<char*>(pattern) + strlen(pattern);
  for (char* current = start; current < end; ++current)
    _pattern.push_back(byte(std::strtoul(current, &current, 16)));

  return _pattern;
}