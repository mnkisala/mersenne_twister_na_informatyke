#pragma once

#include <array>

#include <cstddef>
#include <cinttypes>
 
namespace MT
{
  constexpr uint32_t W = 32;
  constexpr uint32_t N = 624;
  constexpr uint32_t M = 397;
  constexpr uint32_t R = 31;

  constexpr uint32_t A = 0x9907B0DF;

  constexpr uint32_t U = 11;
  constexpr uint32_t D = 0xFFFFFFFF;

  constexpr uint32_t S = 7;
  constexpr uint32_t B = 0x9D2C5680;
   
  constexpr uint32_t T = 15;
  constexpr uint32_t C = 0xEFC60000;

  constexpr uint32_t L = 18;

  constexpr uint32_t LOWER_MASK = (1u << R) - 1;
  constexpr uint32_t UPPER_MASK = ~LOWER_MASK;

  class MersenneTwister
  {
    private:
      std::array<uint32_t, N> numbers;
      size_t index = N + 1;
    public:
      MersenneTwister(uint32_t seed);
      void twist();
      uint32_t next();
  };
}
