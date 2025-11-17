#include "patches.h"
#include "src/core/core.h"
#include "src/library/utils.h"
#include "src/sdk/main/color.h"

#include <Windows.h>
#include <cstring>
#include <memoryapi.h>
#include <winnt.h>

patch_t::patch_t(const char* mod, const char* sig, int off, const char* _patch,
                 const char* desc) {
  module      = mod;
  description = desc;
  signature   = sig;
  offset      = off;

  auto pat = utils::pattern_to_byte(sig);
  patch    = pat;
  size     = pat.size();
  original.resize(size);
}

void patch_t::write(std::vector<byte>& bytes) {
  DWORD new_protect, old_protect;
  VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &new_protect);
  memcpy(address, bytes.data(), size);
  VirtualProtect(address, size, new_protect, &old_protect);
}

bool patch_t::initialize() {
  if (is_patched)
    return true;

  uintptr_t add = utils::find_pattern_in_memory(module, signature);
  address       = LPVOID(add);
  if (!address) {
    return false;
  }

  address = LPVOID(uintptr_t(address) + offset);

  DWORD new_protect, old_protect;
  VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &new_protect);
  memcpy(original.data(), address, size);
  VirtualProtect(address, size, new_protect, &old_protect);

  write(patch);

  core::sdk_custom(COLOR_PURPLE_BALANCED, "Patch", "%s successful!", description);

  return is_patched = true;
}

void patch_t::unload() {
  if (!is_patched)
    return;

  write(original);

  core::sdk_custom(COLOR_PURPLE_BALANCED, "Patch", "%s unpatched.", description);
  is_patched = false;
}

bool patches_t::initialize() {
  patches = {
      // Add patches here with patch_t constructor.
  };

  for (auto& patch : patches) {
    if (!patch.initialize()) {
      failed = true;
    }
  }

  return !failed;
}

void patches_t::unload() {
  for (auto& patch : patches)
    patch.unload();
}