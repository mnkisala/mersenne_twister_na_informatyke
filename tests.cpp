#include <catch.hpp>
#include <mersenne_twister/mersenne_twister.hpp>

#include <vector>

TEST_CASE("wyniki sie nie powtarzaja (pierwsze 10)", "32bit")
{
  auto generator = MT::mt19937(1);

  std::vector<uint32_t> wyniki;
  for(size_t i = 0; i < 10; i++)
  {
    auto wynik = generator.next();
    auto wyszukanie = std::find(wyniki.begin(), wyniki.end(), wynik);
    REQUIRE(wyszukanie == wyniki.end()); /* std::find zwraca iterator koncowy, jezeli nie znajdzie
                                            danego elementu w kolekcji */
    wyniki.push_back(wynik);
  }
}

TEST_CASE("wyniki sa takie same dla tego samego seedu", "32bit")
{
  auto a = MT::mt19937(1);
  auto b = MT::mt19937(1);

  /* sprawdza 10 pierwszych wynikow */
  for(size_t i = 0; i < 10; i++)
    REQUIRE(a.next() == b.next());
}
 
TEST_CASE("wyniki sa takie same dla tego samego seedu, mieszajac oba w kazdym kroku", "32bit")
{
  auto a = MT::mt19937(1);
  auto b = MT::mt19937(1);

  /* sprawdza 10 pierwszych wynikow */
  for(size_t i = 0; i < 10; i++)
  {
    REQUIRE(a.next() == b.next());
    a.twist();
    b.twist();
  }
}
 
TEST_CASE("wyniki sie nie powtarzaja (pierwsze 10) x64", "64bit")
{
  auto generator = MT::mt19937_64(1);

  std::vector<uint64_t> wyniki;
  for(size_t i = 0; i < 10; i++)
  {
    auto wynik = generator.next();
    auto wyszukanie = std::find(wyniki.begin(), wyniki.end(), wynik);
    REQUIRE(wyszukanie == wyniki.end()); /* std::find zwraca iterator koncowy, jezeli nie znajdzie
                                            danego elementu w kolekcji */
    wyniki.push_back(wynik);
  }
}

TEST_CASE("wyniki sa takie same dla tego samego seedu x64", "64bit")
{
  auto a = MT::mt19937_64(1);
  auto b = MT::mt19937_64(1);

  /* sprawdza 10 pierwszych wynikow */
  for(size_t i = 0; i < 10; i++)
    REQUIRE(a.next() == b.next());
}
 
TEST_CASE("wyniki sa takie same dla tego samego seedu, mieszajac oba w kazdym kroku x64", "64bit")
{
  auto a = MT::mt19937_64(1);
  auto b = MT::mt19937_64(1);

  /* sprawdza 10 pierwszych wynikow */
  for(size_t i = 0; i < 10; i++)
  {
    REQUIRE(a.next() == b.next());
    a.twist();
    b.twist();
  }
}
