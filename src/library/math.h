#pragma once

#include <Windows.h>

class vector3_t;
class qangle_t;
class vector2_t;
class view_matrix_t;
class matrix_3x4_t;

namespace math {
  constexpr float PI = 3.14159265358979323846f;
  constexpr float radian_to_degrees(const double x) { return x * (180.f / PI); }
  constexpr float degrees_to_radian(const float x) { return x * (PI / 180.f); }
  float           random_float(float min_val, float max_val);
  void            random_seed(int seed);
  int             random_int(int min_val, int max_val);
  double          plat_float_time();
}; // namespace math