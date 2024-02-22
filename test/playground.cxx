//
// Created by walde on 22.02.24.
//

#include "confu_json/to_json.hxx"
#include "confu_json/to_object.hxx"
#include "test/constant.hxx"
#include <catch2/catch.hpp>
#include <login_matchmaking_game_shared/matchmakingGameSerialization.hxx>
#include <login_matchmaking_game_shared/userMatchmakingSerialization.hxx>
using namespace confu_json;

TEST_CASE ("playground", "[playground]")
{

  //  boost::hana::for_each (matchmaking_game::matchmakingGame, [&] (const auto &x) {
  //        boost::json::error_code ec{};
  //        auto cards=durak::GameOption{};
  auto card = durak::Card{};
  //  card.value

  to_object<durak::Card> (to_json (card));
  //        if (ec) std::cout << "read_json error: " << ec.message () << std::endl;
  //        return;
  //  });
}