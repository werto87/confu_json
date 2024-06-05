//
// Created by walde on 22.02.24.
//

#include "confu_json/to_json.hxx"
#include "confu_json/to_object.hxx"
#include "test/constant.hxx"
#include <catch2/catch.hpp>
#include <durak/gameData.hxx>
#include <login_matchmaking_game_shared/matchmakingGameSerialization.hxx>
#include <login_matchmaking_game_shared/userMatchmakingSerialization.hxx>
using namespace confu_json;

struct OptionalInt
{
  std::optional<int> myOpInt{};
};
BOOST_FUSION_ADAPT_STRUCT (OptionalInt, myOpInt)
TEST_CASE ("playground", "[playground]")
{
  auto original = OptionalInt{};
  original.myOpInt = 42;
  auto tmp = to_json (original);
  std::cout << to_json (to_object<OptionalInt> (tmp)) << std::endl;
  std::cout << tmp << std::endl;
}
