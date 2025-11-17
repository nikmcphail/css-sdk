#pragma once

#include <cstddef>
#include <vector>

#include <Windows.h>

class patch_t {
private:
  const char*       module      = nullptr;
  const char*       signature   = nullptr;
  int               offset      = 0x0;
  std::vector<byte> patch       = {};
  std::vector<byte> original    = {};
  size_t            size        = 0;
  void*             address     = 0;
  bool              is_patched  = false;
  const char*       description = nullptr;

  void write(std::vector<byte>& bytes);

public:
  patch_t(const char* module, const char* signature, int offset, const char* patch,
          const char* _desc);

  bool initialize();
  void unload();
};

class patches_t {
private:
  bool failed = false;

public:
  bool initialize();
  void unload();

  std::vector<patch_t> patches = {};
};