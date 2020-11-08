#pragma once

#include <array>

#include <cstddef>
#include <cinttypes>
 
namespace MT
{
  template<typename Type, 
           size_t W, size_t N, size_t M, size_t R,
           Type A,
           size_t F,
           size_t U, Type D,
           size_t S, Type B,
           size_t T, Type C,
           size_t L>
  class MersenneTwister
  {
    public:
      using type = Type;

    private:
      std::array<Type, N> state;
      size_t index;

      static constexpr Type lower_mask = (static_cast<Type>(1) << R) - 1;
      static constexpr Type upper_mask = ~lower_mask;
       
      /* Maska bitowa ktora po bitowym AND z jakas liczba
         pozostawia pierwsze W bitow tej liczby. Wygenerowanie jej w 
         taki sposob jest bardziej eleganckim rozwiazaniem niz
         proszenie uzytkownika API o wprowadzenie jej recznie */
      const Type first_w_bits_mask  = ([]()
        {
          Type out = 0;
          for(size_t i = 0; i < W; i++)
            out |= (static_cast<Type>(1) << i);
          return out;
        })(); 
       
    private:
      /* aplikuje maski temperujace */
      static Type temper(Type value)
      {
        value ^= (value >> U) & D;
        value ^= (value << S) & B;
        value ^= (value << T) & C;
        value ^= (value >> L);
        return value;
      }
       
    public: MersenneTwister(Type seed)
        : index(N)
      {
        state[0] = seed & first_w_bits_mask;
        for(size_t i = 1; i < N; i++)
          state[i] = (F * (state[i-1] ^ state[i-1] >> (W - 2)) + i) & first_w_bits_mask;
      }
         
      void twist()
      {
        for(size_t i = 0; i < N; i++)
        {
          Type x = (state[i] & upper_mask) + (state[i+1 % N] & lower_mask);
          Type xA = x >> 1;
          if(x % 2 != 0) 
            xA ^= A;

          state[i] = state[(i + M) % N] ^ xA;
        }

        index = 0;
      }
       
      Type next()
      {
        if(index == N)
          twist();
         
        return temper(state[index++]) & first_w_bits_mask;
      }
  };

  using mt19937 = MersenneTwister<uint32_t,
                                  32, 624, 397, 31,
                                  0x9907B0DF,
                                  1812433253,
                                  11, 0xFFFFFFFF,
                                  7 , 0x9D2C5680,
                                  15, 0xEFC60000,
                                  18>;
   
  using mt19937_64 = MersenneTwister<uint64_t, 
                                     64, 312, 156, 31,
                                     0xB5026F5AA96619E9,
                                     1812433253,
                                     29, 0x5555555555555555,
                                     17, 0x71D67FFFEDA60000,
                                     37, 0xFFF7EEE000000000,
                                     43>;
   
}
