#pragma once

#include <cstdint>
#include <string.h>

namespace hash {
  inline constexpr uint32_t u_hash_32  = 0x811C9DC5;
  inline constexpr uint32_t u_prime_32 = 0x1000193;
  inline constexpr uint64_t u_hash_64  = 0xcbf29ce484222325;
  inline constexpr uint64_t u_prime_64 = 0x100000001b3;

  // compile-time hashes
  constexpr uint32_t hash_32_const(const char*    szString,
                                   const uint32_t uValue = u_hash_32) noexcept {
    return (szString[0] == '\0')
               ? uValue
               : hash_32_const(&szString[1], (uValue ^ uint32_t(szString[0])) * u_prime_32);
  }

  constexpr uint64_t hash_64_const(const char*    szString,
                                   const uint64_t uValue = u_hash_64) noexcept {
    return (szString[0] == '\0')
               ? uValue
               : hash_64_const(&szString[1], (uValue ^ uint64_t(szString[0])) * u_prime_64);
  }

  // runtime hashes
  inline uint32_t hash_32(const char* szString) {
    uint32_t uHashed = u_hash_32;

    for (size_t i = 0U; i < strlen(szString); ++i) {
      uHashed ^= szString[i];
      uHashed *= u_prime_32;
    }

    return uHashed;
  }

  inline uint64_t hash_64(const char* szString) {
    uint64_t uHashed = u_hash_64;

    for (size_t i = 0U; i < strlen(szString); ++i) {
      uHashed ^= szString[i];
      uHashed *= u_prime_64;
    }

    return uHashed;
  }
} // namespace hash