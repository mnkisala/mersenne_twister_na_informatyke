#pragma once

#include <array>

#include <cstddef>
#include <cinttypes>
 
namespace MT
{
  template<typename Type, 
           Type W, Type N, Type M, Type R,
           Type A,
           Type U, Type D,
           Type S, Type B,
           Type T, Type C,
           Type L, 
           Type LOWER_MASK,
           Type UPPER_MASK>
  class MersenneTwister
  {
    public:
      /* przydatne odbicia */
      using type = Type;
    private:
      std::array<Type, N> numbers;
      size_t index = N + 1;
    public:
      MersenneTwister(Type seed)
        : index(N)
      {
        numbers[0] = seed;
        for(size_t i = 1; i < N; i++)
        {
          /* gotta find out what the fuck is up with this number*/
          numbers[i] = 69069 * numbers[i-1];
        }
      }
         
      void twist()
      {
        for(size_t i = 0; i < N; i++)
        {
          Type x = (numbers[i] & UPPER_MASK) + (numbers[i+1 % N] & LOWER_MASK);
          Type xA = x >> 1;
          if(x % 2 != 0) 
          {
            xA ^= A;
          }

          numbers[i] = numbers[(i + M) % N] ^ xA;
        }

        index = 0;
      }
       
      Type next()
      {
        if(index == N)
        {
          twist();
        }

        Type y = numbers[index];
        y ^= (y >> U) & D;
        y ^= (y << S) & B;
        y ^= (y << T) & C;
        y ^= (y >> 1);
        
        index++;

        return y;
      }
  };

  constexpr uint32_t mt19937_lower_mask = (1u << 31) - 1;
  constexpr uint32_t mt19937_upper_mask = ~mt19937_lower_mask;
  using mt19937 = MersenneTwister<uint32_t,
                                  32, 624, 397, 31,
                                  0x9907B0DF,
                                  11, 0xFFFFFFFF,
                                  7 , 0x9D2C5680,
                                  15, 0xEFC60000,
                                  18,
                                  mt19937_lower_mask,
                                  mt19937_upper_mask>;
}
