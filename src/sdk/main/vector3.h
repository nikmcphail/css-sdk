#pragma once

#include <math.h>

class vector2_t;

class vector3_t {
public:
  float x, y, z;

  vector3_t();

  vector3_t(float ix, float iy, float iz);

  explicit vector3_t(float XYZ);

  vector3_t(const float* v);

  void initialize(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);

  vector2_t& as_vector_2d();

  const vector2_t& as_vector_2d() const;

  float length() const;

  __forceinline float length_sqr();

  float length_2d(void) const;

  float length_2d_sqr(void) const;

  bool is_zero(float tolerance = 0.01f) const;

  float dot(const vector3_t& other) const;

  float dist_to(const vector3_t& other);

  float normalize_in_place();

  float operator[](int i) const;

  float& operator[](int i);

  bool operator==(const vector3_t& v) const;

  bool operator!=(const vector3_t& v) const;

  __forceinline vector3_t& operator+=(const vector3_t& v);

  __forceinline vector3_t& operator-=(const vector3_t& v);

  __forceinline vector3_t& operator*=(const vector3_t& v);

  __forceinline vector3_t& operator*=(float s);

  __forceinline vector3_t& operator/=(const vector3_t& v);

  __forceinline vector3_t& operator/=(float s);

  __forceinline vector3_t& operator+=(float fl); ///< broadcast add
  __forceinline vector3_t& operator-=(float fl); ///< broadcast sub

  vector3_t& operator=(const vector3_t& v);

  vector3_t operator-(void) const;

  vector3_t operator+(const vector3_t& v) const;

  vector3_t operator-(const vector3_t& v) const;

  vector3_t operator*(const vector3_t& v) const;

  vector3_t operator/(const vector3_t& v) const;

  vector3_t operator*(float fl) const;

  vector3_t operator/(float fl) const;
};

__forceinline float vector_normalize(vector3_t& vec) {
  float sqr_len = vec.length_sqr() + 1.0e-10f;
  float inv_len = 1.0f / sqr_len;

  vec.x *= inv_len;
  vec.y *= inv_len;
  vec.z *= inv_len;

  return sqr_len * inv_len;
}

__forceinline void vector_subtract(const vector3_t& a, const vector3_t& b, vector3_t& c) {
  c.x = a.x - b.x;
  c.y = a.y - b.y;
  c.z = a.z - b.z;
}

__forceinline void vector_add(const vector3_t& a, const vector3_t& b, vector3_t& c) {
  c.x = a.x + b.x;
  c.y = a.y + b.y;
  c.z = a.z + b.z;
}

__forceinline void vector_multiply(const vector3_t& a, float b, vector3_t& c) {
  c.x = a.x * b;
  c.y = a.y * b;
  c.z = a.z * b;
}

__forceinline void vector_multiply(const vector3_t& a, const vector3_t& b, vector3_t& c) {
  c.x = a.x * b.x;
  c.y = a.y * b.y;
  c.z = a.z * b.z;
}

inline void vector_scale(const vector3_t& in, float scale, vector3_t& result) {
  vector_multiply(in, scale, result);
}

__forceinline void vector_divide(const vector3_t& a, float b, vector3_t& c) {
  float oob = 1.0f / b;
  c.x       = a.x * oob;
  c.y       = a.y * oob;
  c.z       = a.z * oob;
}

__forceinline void vector_divide(const vector3_t& a, const vector3_t& b, vector3_t& c) {
  c.x = a.x / b.x;
  c.y = a.y / b.y;
  c.z = a.z / b.z;
}

inline void vector_clear(vector3_t& a) { a.x = a.y = a.z = 0.0f; }

__forceinline void vector_copy(const vector3_t& src, vector3_t& dst) {
  dst.x = src.x;
  dst.y = src.y;
  dst.z = src.z;
}

inline vector3_t::vector3_t() { x = y = z = 0.0f; }

inline vector3_t::vector3_t(float ix, float iy, float iz) {
  x = ix;
  y = iy;
  z = iz;
}

inline vector3_t::vector3_t(float XYZ) { x = y = z = XYZ; }

inline vector3_t::vector3_t(const float* v) {
  x = v[0];
  y = v[1];
  z = v[2];
}

inline void vector3_t::initialize(float ix, float iy, float iz) {
  x = ix;
  y = iy;
  z = iz;
}

inline vector2_t&       vector3_t::as_vector_2d() { return *(vector2_t*)this; }
inline const vector2_t& vector3_t::as_vector_2d() const { return *(const vector2_t*)this; }

inline float vector3_t::length() const { return (float)sqrtf(x * x + y * y + z * z); }
inline float vector3_t::length_sqr() { return (x * x + y * y + z * z); }
inline float vector3_t::length_2d(void) const { return (float)sqrtf(x * x + y * y); }
inline float vector3_t::length_2d_sqr(void) const { return (x * x + y * y); }

inline bool vector3_t::is_zero(float tolerance) const {
  return (x > -tolerance && x < tolerance && y > -tolerance && y < tolerance &&
          z > -tolerance && z < tolerance);
}

inline float vector3_t::dot(const vector3_t& other) const {
  return (x * other.x + y * other.y + z * other.z);
}

inline float vector3_t::dist_to(const vector3_t& other) {
  vector3_t delta;
  vector_subtract(*this, other, delta);
  return delta.length();
}

inline float vector3_t::normalize_in_place() { return vector_normalize(*this); }

inline float  vector3_t::operator[](int i) const { return ((float*)this)[i]; }
inline float& vector3_t::operator[](int i) { return ((float*)this)[i]; }

inline bool vector3_t::operator==(const vector3_t& v) const {
  return (v.x == x) && (v.y == y) && (v.z == z);
}

inline bool vector3_t::operator!=(const vector3_t& v) const {
  return (v.x != x) && (v.y != y) && (v.z != z);
}

inline vector3_t& vector3_t::operator+=(const vector3_t& v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

inline vector3_t& vector3_t::operator-=(const vector3_t& v) {
  x -= v.x;
  y -= v.y;
  z -= v.z;
  return *this;
}

inline vector3_t& vector3_t::operator*=(const vector3_t& v) {
  x *= v.x;
  y *= v.y;
  z *= v.z;
  return *this;
}

inline vector3_t& vector3_t::operator*=(float fl) {
  x *= fl;
  y *= fl;
  z *= fl;
  return *this;
}

inline vector3_t& vector3_t::operator/=(const vector3_t& v) {
  x /= v.x;
  y /= v.y;
  z /= v.z;
  return *this;
}

inline vector3_t& vector3_t::operator/=(float s) {
  float oos = 1.0f / s;
  x *= oos;
  y *= oos;
  z *= oos;
  return *this;
}

inline vector3_t& vector3_t::operator+=(float fl) {
  x += fl;
  y += fl;
  z += fl;
  return *this;
}

inline vector3_t& vector3_t::operator-=(float fl) {
  x -= fl;
  y -= fl;
  z -= fl;
  return *this;
}

inline vector3_t& vector3_t::operator=(const vector3_t& v) {
  x = v.x;
  y = v.y;
  z = v.z;
  return *this;
}

inline vector3_t vector3_t::operator-(void) const { return vector3_t(-x, -y, -z); }

inline vector3_t vector3_t::operator+(const vector3_t& v) const {
  vector3_t res;
  vector_add(*this, v, res);
  return res;
}

inline vector3_t vector3_t::operator-(const vector3_t& v) const {
  vector3_t res;
  vector_subtract(*this, v, res);
  return res;
}

inline vector3_t vector3_t::operator*(const vector3_t& v) const {
  vector3_t res;
  vector_multiply(*this, v, res);
  return res;
}

inline vector3_t vector3_t::operator/(const vector3_t& v) const {
  vector3_t res;
  vector_divide(*this, v, res);
  return res;
}

inline vector3_t vector3_t::operator*(float fl) const {
  vector3_t res;
  vector_multiply(*this, fl, res);
  return res;
}

inline vector3_t vector3_t::operator/(float fl) const {
  vector3_t res;
  vector_divide(*this, fl, res);
  return res;
}

class __declspec(align(16)) vector3_a_t : public vector3_t {
public:
  float w;

  inline vector3_a_t(void) {}
  inline vector3_a_t(float X, float Y, float Z) { initialize(X, Y, Z); }

  explicit vector3_a_t(const vector3_t& other) { initialize(other.x, other.y, other.z); }

  vector3_a_t& operator=(const vector3_t& other) {
    initialize(other.x, other.y, other.z);
    return *this;
  }
};