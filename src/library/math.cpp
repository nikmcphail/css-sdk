#include "math.h"
#include "utils.h"

#include "src/sdk/main/vector3.h"
#include "src/sdk/main/matrix_3x4.h"
#include "src/sdk/main/qangle.h"

void sin_cos(float radians, float* sine, float* cosine) {
  *sine   = sinf(radians);
  *cosine = cosf(radians);
}

float math::random_float(float min_val, float max_val) {
  static ULONG64 random_float_address = utils::get_export("vstdlib.dll", "RandomFloat");
  static auto    func                 = (float (*)(float, float))random_float_address;
  return func(min_val, max_val);
}

void math::random_seed(int seed) {
  static ULONG64 random_seed_address = utils::get_export("vstdlib.dll", "RandomSeed");
  static auto    func                = (void (*)(int))random_seed_address;
  return func(seed);
}

int math::random_int(int min_val, int max_val) {
  static ULONG64 random_int_address = utils::get_export("vstdlib.dll", "RandomInt");
  static auto    func               = (int (*)(int, int))random_int_address;
  return func(min_val, max_val);
}

double math::plat_float_time() {
  static ULONG64 plat_float_time_address = utils::get_export("tier0.dll", "Plat_FloatTime");
  static auto    func                    = (double (*)())plat_float_time_address;
  return func();
}

void math::vector_transform(const vector3_t& in, const matrix_3x4_t& matrix, vector3_t& out) {
  for (auto i = 0; i < 3; i++)
    out[i] = in.dot(matrix[i]) + matrix[i][3];
}

void math::angle_vector(const qangle_t& angles, vector3_t* forward) {
  float sp, sy, cp, cy;
  sin_cos(degrees_to_radian(angles[1]), &sy, &cy);
  sin_cos(degrees_to_radian(angles[0]), &sp, &cp);

  forward->x = cp * cy;
  forward->y = cp * sy;
  forward->z = -sp;
}

void math::angle_vectors(const qangle_t& from, vector3_t* forward, vector3_t* right,
                         vector3_t* up) {
  float sp, sy, sr, cp, cy, cr;

  sin_cos(degrees_to_radian(from.x), &sp, &cp);
  sin_cos(degrees_to_radian(from.y), &sy, &cy);
  sin_cos(degrees_to_radian(from.z), &sr, &cr);

  if (forward) {
    forward->x = cp * cy;
    forward->y = cp * sy;
    forward->z = -sp;
  }

  if (right) {
    right->x = -1 * sr * sp * cy + -1 * cr * -sy;
    right->y = -1 * sr * sp * sy + -1 * cr * cy;
    right->z = -1 * sr * cp;
  }

  if (up) {
    up->x = cr * sp * cy + -sr * -sy;
    up->y = cr * sp * sy + -sr * cy;
    up->z = cr * cp;
  }
}

void math::vector_angles(const vector3_t& forward, qangle_t& angles) {
  float tmp, yaw, pitch;

  if (forward[1] == 0 && forward[0] == 0) {
    yaw = 0;
    if (forward[2] > 0)
      pitch = 270;
    else
      pitch = 90;
  } else {
    yaw = (radian_to_degrees(atan2(forward[1], forward[0])));
    if (yaw < 0)
      yaw += 360;

    tmp   = sqrtf(forward[0] * forward[0] + forward[1] * forward[1]);
    pitch = (radian_to_degrees(atan2(-forward[2], tmp)));
    if (pitch < 0)
      pitch += 360;
  }

  angles[0] = pitch;
  angles[1] = yaw;
  angles[2] = 0;
}