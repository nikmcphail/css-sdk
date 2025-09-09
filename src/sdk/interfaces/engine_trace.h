#pragma once

#include "../main/ray.h"
#include "../main/trace.h"
#include "../main/trace_filter.h"

#include "src/library/utils.h"

class iv_engine_trace_t {
public:
  void trace_ray(const ray_t& ray, uint64_t mask, i_trace_filter_t* filter, trace_t* trace) {
    typedef void(__fastcall * trace_ray_fn)(void*, const ray_t&, uint64_t, i_trace_filter_t*,
                                            trace_t*);
    return utils::get_virtual_function<trace_ray_fn>(this, 4)(this, ray, mask, filter, trace);
  }
};