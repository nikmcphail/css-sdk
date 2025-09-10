#pragma once

#include <vector>

struct addresses_t {
  struct {
    struct {
      uintptr_t get_bone_position;
    } functions;

    struct {
      std::vector<uintptr_t> datamaps = {};
    } structures;
  } client;

  struct {
    struct {
    } functions;
  } engine;

  bool collect_addresses();
};