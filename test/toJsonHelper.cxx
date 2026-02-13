#include "confu_json/to_json.hxx"
#include "confu_json/to_object.hxx"
#include "test/constant.hxx"
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <optional>
#include <vector>
using namespace boost::json;
using namespace confu_json;

TEST_CASE ("to_json_array", "[helper]") { REQUIRE (boost::json::serialize (to_json_array (std::vector<matchmaking_game::StartGame> (5))) == R"([{"StartGame":{"players":[],"gameOption":null,"ratedGame":false}},{"StartGame":{"players":[],"gameOption":null,"ratedGame":false}},{"StartGame":{"players":[],"gameOption":null,"ratedGame":false}},{"StartGame":{"players":[],"gameOption":null,"ratedGame":false}},{"StartGame":{"players":[],"gameOption":null,"ratedGame":false}}])"); }
