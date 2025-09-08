#pragma once

#include <vector>

struct addresses_t {
  struct {
    struct {
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