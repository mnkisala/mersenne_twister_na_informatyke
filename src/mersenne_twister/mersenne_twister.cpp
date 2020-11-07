#include "mersenne_twister.hpp"

namespace MT
{
  MersenneTwister::MersenneTwister(uint32_t seed)
    : index(N)
  {
    numbers[0] = seed;
    for(size_t i = 1; i < N; i++)
    {
      /* gotta find out what the fuck is up with this number*/
      numbers[i] = 69069 * numbers[i-1];
    }
  }
   
  void MersenneTwister::twist()
  {
    for(size_t i = 0; i < N; i++)
    {
      uint32_t x = (numbers[i] & UPPER_MASK) + (numbers[i+1 % N] & LOWER_MASK);
      uint32_t xA = x >> 1;
      if(x % 2 != 0) 
      {
        xA ^= A;
      }

      numbers[i] = numbers[(i + M) % N] ^ xA;
    }

    index = 0;
  }

  uint32_t MersenneTwister::next()
  {
    if(index == N)
    {
      twist();
    }

    uint32_t y = numbers[index];
    y ^= (y >> U) & D;
    y ^= (y << S) & B;
    y ^= (y << T) & C;
    y ^= (y >> 1);
    
    index++;

    return y;
  }
}
