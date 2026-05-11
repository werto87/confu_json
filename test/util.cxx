#include "confu_json/to_json.hxx"
#include "confu_json/to_object.hxx"
#include "test/constant.hxx"
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <optional>
#include <vector>
using namespace boost::json;
using namespace confu_json;

TEST_CASE ("type_name", "[combination]")
{
  SECTION ("Nested") { REQUIRE (type_name<shared_class::Nested> () == "Nested"); }
  SECTION ("CreateAccount") { REQUIRE (type_name<shared_class::CreateAccount> () == "CreateAccount"); }
  SECTION ("std::string") { REQUIRE (type_name<std::string> () == "string"); }

}