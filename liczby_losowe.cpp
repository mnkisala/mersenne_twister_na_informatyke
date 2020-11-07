#include <iostream>
 
#include <mersenne_twister/mersenne_twister.hpp>

int main()
{
  auto generator = MT::MersenneTwister(time(NULL));

  size_t n;
  std::cout << "ile liczb pseudolosowych wygenerowac: ";
  std::cin >> n;

  for(size_t i = 0; i < n; i++)
    std::cout << generator.next() << '\n';
}
