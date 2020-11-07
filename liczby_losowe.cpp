#include <iostream>
 
#include <mersenne_twister/mersenne_twister.hpp>

int main()
{
  MT::mt19937::type seed;
  std::cout << "podaj seed ( 0 = time(NULL) ): ";
  std::cin >> seed;
  if(seed == 0) seed = time(NULL);
   
  auto generator = MT::mt19937(seed);

  size_t n;
  std::cout << "ile liczb pseudolosowych wygenerowac: ";
  std::cin >> n;

  for(size_t i = 0; i < n; i++)
    std::cout << generator.next() << '\n';
}
