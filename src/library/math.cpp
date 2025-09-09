#include "math.h"
#include "utils.h"

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