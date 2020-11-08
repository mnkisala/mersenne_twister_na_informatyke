#pragma once

#include <array>

#include <cstddef>
#include <cinttypes>
 
namespace MT
{
  template<typename Type, 
           size_t W, size_t N, size_t M, size_t R,
           Type A,
           Type U, Type D,
           Type S, Type B,
           Type T, Type C,
           Type L>
  class MersenneTwister
  {
    public:
      using type = Type;

    private:
      std::array<Type, N> numbers;
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
        value ^= (value >> 1);
        return value;
      }
       
    public: 
      MersenneTwister(Type seed)
        : index(N)
      {
        numbers[0] = seed;
        for(size_t i = 1; i < N; i++)
          numbers[i] = (69069 * numbers[i-1]) & first_w_bits_mask;
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
         
        index++;
         
        return temper(y) & first_w_bits_mask;
      }
  };

  using mt19937 = MersenneTwister<uint32_t,
                                  32, 624, 397, 31,
                                  0x9907B0DF,
                                  11, 0xFFFFFFFF,
                                  7 , 0x9D2C5680,
                                  15, 0xEFC60000,
                                  18>;
   
  using mt19937_64 = MersenneTwister<uint64_t, 
                                     64, 312, 156, 31,
                                     0xB5026F5AA96619E9,
                                     29, 0x5555555555555555,
                                     17, 0x71D67FFFEDA60000,
                                     37, 0xFFF7EEE000000000,
                                     43>;
   
}
