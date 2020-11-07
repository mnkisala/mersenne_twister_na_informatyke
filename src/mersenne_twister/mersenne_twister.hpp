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
           Type L>
  class MersenneTwister
  {
    public:
      using type = Type; /* przydatne odbicie */

    private:
      std::array<Type, N> numbers;
      size_t index;

      static constexpr Type lower_mask = (1u << R) - 1;
      static constexpr Type upper_mask = ~lower_mask;
      const Type w_bits_mask = ([]() -> Type
        {
          Type out = 0;
          for(size_t i = 0; i < W; i++)
            out |= (1u << i);
          return out;
        })();

    public:
      MersenneTwister(Type seed)
        : index(N)
      {
        numbers[0] = seed;
        for(size_t i = 1; i < N; i++)
          numbers[i] = (69069 * numbers[i-1]) & w_bits_mask;
      }
         
      void twist()
      {
        for(size_t i = 0; i < N; i++)
        {
          Type x = (numbers[i] & upper_mask) + (numbers[i+1 % N] & lower_mask);
          Type xA = x >> 1;
          if(x % 2 != 0) 
            xA ^= A;

          numbers[i] = numbers[(i + M) % N] ^ xA;
        }

        index = 0;
      }
       
      Type next()
      {
        if(index == N)
          twist();

        Type y = numbers[index];
        y ^= (y >> U) & D;
        y ^= (y << S) & B;
        y ^= (y << T) & C;
        y ^= (y >> 1);
        
        index++;

        return y & w_bits_mask;
      }
  };

  using mt19937 = MersenneTwister<uint32_t,
                                  32, 624, 397, 31,
                                  0x9907B0DF,
                                  11, 0xFFFFFFFF,
                                  7 , 0x9D2C5680,
                                  15, 0xEFC60000,
                                  18>;
}
