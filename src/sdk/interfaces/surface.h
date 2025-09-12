#pragma once

#include <Windows.h>
#include "src/library/utils.h"

class i_surface_t {
public:
  HCURSOR unlock_cursor() {
    return utils::get_virtual_function<HCURSOR(__fastcall*)(i_surface_t*)>(this, 61)(this);
  }
};