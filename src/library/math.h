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

  void vector_transform(const vector3_t& in, const matrix_3x4_t& matrix, vector3_t& out);
  void angle_vector(const qangle_t& angles, vector3_t* forward);
  void angle_vectors(const qangle_t& from, vector3_t* forward, vector3_t* right = NULL,
                     vector3_t* up = NULL);
  void vector_angles(const vector3_t& forward, qangle_t& angles);
}; // namespace math