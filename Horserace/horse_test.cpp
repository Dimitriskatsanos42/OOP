#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "horse.hpp"



TEST_CASE("horse racing", "move_forward")
{
  horse h(1,"horse_1", 55, 65, 80);
  REQUIRE(h.move_forward(1,50.0)==true);
  REQUIRE(h.move_forward(4,52.6)==true);
  REQUIRE(h.move_forward(10,60.34)==true);
  REQUIRE(h.move_forward(5,67.45)==false);
  REQUIRE(h.move_forward(1,67.45)==false);
}

TEST_CASE("horse racing 2", "move_forward 2")
{
    horse h(2, "horse_2", 80, 52, 76);
    REQUIRE(h.move_forward(2, 61.34) == false);
    REQUIRE(h.move_forward(1, 78.23) == true);
    REQUIRE(h.move_forward(6, 99.9) == false);
    REQUIRE(h.move_forward(5, 51.99) == true);
    REQUIRE(h.move_forward(9, 60.1) == true);
    REQUIRE(h.move_forward(9, 64.01) == false);
}
