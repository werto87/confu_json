#include "confu_json/to_json.hxx"
#include "confu_json/to_object.hxx"
#include "test/constant.hxx"
#include <catch2/catch.hpp>
using namespace boost::json;
using namespace confu_json;
TEST_CASE ("Nested combination", "[combination]")
{
  auto nested = shared_class::Nested{};
  nested.answer = 42;
  REQUIRE (nested.answer == to_object<shared_class::Nested> (to_json (nested)).answer);
}

TEST_CASE ("Student optionals null combination", "[combination]")
{
  auto student = shared_class::Student{};
  auto studentTest = to_object<shared_class::Student> (to_json (student));
  REQUIRE (student.answer == studentTest.answer);
  REQUIRE (student.happy == studentTest.happy);
  REQUIRE (student.name == studentTest.name);
  REQUIRE (student.nothingInt == studentTest.nothingInt);
  REQUIRE (student.nothingBool == studentTest.nothingBool);
  REQUIRE (student.nothingString == studentTest.nothingString);
  REQUIRE (student.nested.answer == studentTest.nested.answer);
  REQUIRE (student.nestedOptional.has_value () == studentTest.nestedOptional.has_value ());
}

TEST_CASE ("Student optionals have value combination", "[combination]")
{
  auto student = shared_class::Student{};
  student.nothingInt = 42;
  student.nothingBool = true;
  student.nothingString = "huhu";
  student.nested.answer = 42;
  student.nestedOptional = shared_class::Nested{ 42 };
  auto studentTest = to_object<shared_class::Student> (to_json (student));
  REQUIRE (student.answer == studentTest.answer);
  REQUIRE (student.happy == studentTest.happy);
  REQUIRE (student.name == studentTest.name);
  REQUIRE (student.nothingInt == studentTest.nothingInt);
  REQUIRE (student.nothingBool == studentTest.nothingBool);
  REQUIRE (student.nothingString == studentTest.nothingString);
  REQUIRE (student.nested.answer == studentTest.nested.answer);
  REQUIRE (student.nestedOptional.has_value () == studentTest.nestedOptional.has_value ());
}

TEST_CASE ("NestedPair combination", "[combination]")
{
  auto nestedPair = shared_class::NestedPair{};
  nestedPair.nestedPair.first = shared_class::Nested{ 1337 };
  nestedPair.nestedPair.second = shared_class::Nested{ 42 };
  nestedPair.i = 5;
  auto nestedPairTest = to_object<shared_class::NestedPair> (to_json (nestedPair));
  REQUIRE (nestedPair.nestedPair.first.answer == nestedPairTest.nestedPair.first.answer);
  REQUIRE (nestedPair.nestedPair.second.answer == nestedPairTest.nestedPair.second.answer);
  REQUIRE (nestedPair.i == nestedPairTest.i);
}

TEST_CASE ("NestedPairOptional combination", "[combination]")
{
  auto nestedPairOptional = shared_class::NestedPairOptional{};
  nestedPairOptional.nestedPairOptional.first = shared_class::Nested{ 1337 };
  nestedPairOptional.nestedPairOptional.second = shared_class::Nested{ 42 };
  auto nestedPairOptionalTest = to_object<shared_class::NestedPairOptional> (to_json (nestedPairOptional));
  REQUIRE (nestedPairOptional.nestedPairOptional.first.answer == nestedPairOptionalTest.nestedPairOptional.first.answer);
  REQUIRE (nestedPairOptional.nestedPairOptional.second->answer == nestedPairOptionalTest.nestedPairOptional.second->answer);
}

TEST_CASE ("NestedPairOptional non value combination", "[combination]")
{
  auto nestedPairOptional = shared_class::NestedPairOptional{};
  nestedPairOptional.nestedPairOptional.first = shared_class::Nested{ 1337 };
  auto nestedPairOptionalTest = to_object<shared_class::NestedPairOptional> (to_json (nestedPairOptional));
  REQUIRE (nestedPairOptional.nestedPairOptional.first.answer == nestedPairOptionalTest.nestedPairOptional.first.answer);
  REQUIRE (nestedPairOptional.nestedPairOptional.second.has_value () == nestedPairOptionalTest.nestedPairOptional.second.has_value ());
}

TEST_CASE ("NestedVector combination", "[combination]")
{
  auto nestedVector = shared_class::NestedVector{};
  nestedVector.nestedVector.push_back (shared_class::Nested{ 42 });
  nestedVector.intVector.push_back (1);
  auto nestedVectorTest = to_object<shared_class::NestedVector> (to_json (nestedVector));
  REQUIRE (nestedVector.nestedVector.at (0).answer == nestedVectorTest.nestedVector.at (0).answer);
  REQUIRE (nestedVector.intVector == nestedVectorTest.intVector);
}

TEST_CASE ("NestedVectorOptional combination", "[combination]")
{
  auto nestedVectorOptional = shared_class::NestedVectorOptional{};
  nestedVectorOptional.nestedVectorOptional.push_back (shared_class::Nested{ 42 });
  nestedVectorOptional.nestedVectorOptional.push_back (shared_class::Nested{ 55 });
  nestedVectorOptional.intNestedVectorOptional.push_back (1);
  nestedVectorOptional.intNestedVectorOptional.push_back (2);
  nestedVectorOptional.stringNestedVectorOptional.push_back (std::string{ "huhu" });
  nestedVectorOptional.stringNestedVectorOptional.push_back (std::string{ "fox" });
  auto nestedVectorOptionalTest = to_object<shared_class::NestedVectorOptional> (to_json (nestedVectorOptional));
  REQUIRE (nestedVectorOptional.nestedVectorOptional.at (0).value ().answer == nestedVectorOptionalTest.nestedVectorOptional.at (0).value ().answer);
  REQUIRE (nestedVectorOptional.nestedVectorOptional.at (1).value ().answer == nestedVectorOptionalTest.nestedVectorOptional.at (1).value ().answer);
  REQUIRE (nestedVectorOptional.intNestedVectorOptional.at (0).value () == nestedVectorOptionalTest.intNestedVectorOptional.at (0).value ());
  REQUIRE (nestedVectorOptional.intNestedVectorOptional.at (1).value () == nestedVectorOptionalTest.intNestedVectorOptional.at (1).value ());
  REQUIRE (nestedVectorOptional.stringNestedVectorOptional.at (0).value () == nestedVectorOptionalTest.stringNestedVectorOptional.at (0).value ());
  REQUIRE (nestedVectorOptional.stringNestedVectorOptional.at (1).value () == nestedVectorOptionalTest.stringNestedVectorOptional.at (1).value ());
}

TEST_CASE ("NestedVectorOptional with nullptr combination", "[combination]")
{
  auto nestedVectorOptional = shared_class::NestedVectorOptional{};
  nestedVectorOptional.nestedVectorOptional.push_back (shared_class::Nested{ 42 });
  nestedVectorOptional.nestedVectorOptional.push_back ({});
  nestedVectorOptional.intNestedVectorOptional.push_back (1);
  nestedVectorOptional.intNestedVectorOptional.push_back ({});
  nestedVectorOptional.stringNestedVectorOptional.push_back (std::string{ "huhu" });
  nestedVectorOptional.stringNestedVectorOptional.push_back (boost::optional<std::string>{});
  auto nestedVectorOptionalTest = to_object<shared_class::NestedVectorOptional> (to_json (nestedVectorOptional));
  REQUIRE (nestedVectorOptional.nestedVectorOptional.at (0).value ().answer == nestedVectorOptionalTest.nestedVectorOptional.at (0).value ().answer);
  REQUIRE (nestedVectorOptional.nestedVectorOptional.at (1).has_value () == nestedVectorOptionalTest.nestedVectorOptional.at (1).has_value ());
  REQUIRE (nestedVectorOptional.intNestedVectorOptional.at (0).value () == nestedVectorOptionalTest.intNestedVectorOptional.at (0).value ());
  REQUIRE (nestedVectorOptional.intNestedVectorOptional.at (1).has_value () == nestedVectorOptionalTest.intNestedVectorOptional.at (1).has_value ());
  REQUIRE (nestedVectorOptional.stringNestedVectorOptional.at (0).value () == nestedVectorOptionalTest.stringNestedVectorOptional.at (0).value ());
  REQUIRE (nestedVectorOptional.stringNestedVectorOptional.at (1).has_value () == nestedVectorOptionalTest.stringNestedVectorOptional.at (1).has_value ());
}

TEST_CASE ("NestedPairVector combination", "[combination]")
{
  auto nestedPairVector = shared_class::NestedPairVector{};
  nestedPairVector.nestedPairVector.push_back (std::pair<shared_class::Nested, shared_class::Nested>{ shared_class::Nested{ 42 }, shared_class::Nested{ 42 } });
  nestedPairVector.nestedPairVector.push_back (std::pair<shared_class::Nested, shared_class::Nested>{ shared_class::Nested{ 32 }, shared_class::Nested{ 32 } });
  auto nestedPairVectorTest = to_object<shared_class::NestedPairVector> (to_json (nestedPairVector));
  REQUIRE (nestedPairVector.nestedPairVector.at (0).first.answer == nestedPairVectorTest.nestedPairVector.at (0).first.answer);
  REQUIRE (nestedPairVector.nestedPairVector.at (0).second.answer == nestedPairVectorTest.nestedPairVector.at (0).second.answer);
  REQUIRE (nestedPairVector.nestedPairVector.at (1).first.answer == nestedPairVectorTest.nestedPairVector.at (1).first.answer);
  REQUIRE (nestedPairVector.nestedPairVector.at (1).second.answer == nestedPairVectorTest.nestedPairVector.at (1).second.answer);
}

TEST_CASE ("NestedPairOptionalVector combination", "[combination]")
{
  auto nestedPairOptionalVector = shared_class::NestedPairOptionalVector{};
  nestedPairOptionalVector.nestedPairOptionalVector.push_back (std::pair<shared_class::Nested, boost::optional<shared_class::Nested>>{ shared_class::Nested{ 42 }, shared_class::Nested{ 42 } });
  nestedPairOptionalVector.nestedPairOptionalVector.push_back (std::pair<shared_class::Nested, boost::optional<shared_class::Nested>>{ shared_class::Nested{ 32 }, boost::optional<shared_class::Nested>{} });
  auto nestedPairOptionalVectorTest = to_object<shared_class::NestedPairOptionalVector> (to_json (nestedPairOptionalVector));
  REQUIRE (nestedPairOptionalVector.nestedPairOptionalVector.at (0).first.answer == nestedPairOptionalVectorTest.nestedPairOptionalVector.at (0).first.answer);
  REQUIRE (nestedPairOptionalVector.nestedPairOptionalVector.at (0).second->answer == nestedPairOptionalVectorTest.nestedPairOptionalVector.at (0).second->answer);
  REQUIRE (nestedPairOptionalVector.nestedPairOptionalVector.at (1).first.answer == nestedPairOptionalVectorTest.nestedPairOptionalVector.at (1).first.answer);
  REQUIRE (nestedPairOptionalVector.nestedPairOptionalVector.at (1).second.has_value () == nestedPairOptionalVectorTest.nestedPairOptionalVector.at (1).second.has_value ());
}

TEST_CASE ("Enum combination", "[combination]")
{
  auto withEnum = shared_class::WithEnum{};
  auto withEnumTest = to_object<shared_class::WithEnum> (to_json (withEnum));
  REQUIRE (withEnum.playerRole == withEnumTest.playerRole);
}

TEST_CASE ("EnumOptional combination", "[combination]")
{
  auto withEnumOptional = shared_class::WithEnumOptional{};
  auto withEnumOptionalTest = to_object<shared_class::WithEnumOptional> (to_json (withEnumOptional));
  REQUIRE (withEnumOptional.playerRoleOptional == withEnumOptionalTest.playerRoleOptional);
  REQUIRE_FALSE (withEnumOptionalTest.playerRoleOptional.has_value ());
}

TEST_CASE ("EnumOptional value combination", "[combination]")
{
  auto withEnumOptional = shared_class::WithEnumOptional{};
  withEnumOptional.playerRoleOptional = shared_class::PlayerRole::defend;
  auto withEnumOptionalTest = to_object<shared_class::WithEnumOptional> (to_json (withEnumOptional));
  REQUIRE (withEnumOptional.playerRoleOptional.value () == shared_class::PlayerRole::defend);
  REQUIRE (withEnumOptionalTest.playerRoleOptional.has_value ());
  REQUIRE (withEnumOptionalTest.playerRoleOptional.value () == shared_class::PlayerRole::defend);
}
TEST_CASE ("WithEnumPair combination", "[combination]")
{
  auto withEnumPair = shared_class::WithEnumPair{};
  withEnumPair.withEnumPair.first = shared_class::PlayerRole::waiting;
  withEnumPair.withEnumPair.second = shared_class::PlayerRole::defend;
  auto withEnumPairTest = to_object<shared_class::WithEnumPair> (to_json (withEnumPair));
  REQUIRE (withEnumPair.withEnumPair.first == withEnumPairTest.withEnumPair.first);
  REQUIRE (withEnumPair.withEnumPair.second == withEnumPairTest.withEnumPair.second);
}

TEST_CASE ("WithEnumPairOptional combination", "[combination]")
{
  auto withEnumPairOptional = shared_class::WithEnumPairOptional{};
  withEnumPairOptional.withEnumPairOptional.first = shared_class::PlayerRole::waiting;
  withEnumPairOptional.withEnumPairOptional.second = shared_class::PlayerRole::defend;
  auto withEnumPairOptionalTest = to_object<shared_class::WithEnumPairOptional> (to_json (withEnumPairOptional));
  REQUIRE (withEnumPairOptional.withEnumPairOptional.first == withEnumPairOptionalTest.withEnumPairOptional.first);
  REQUIRE (withEnumPairOptionalTest.withEnumPairOptional.second.has_value ());
  REQUIRE (withEnumPairOptional.withEnumPairOptional.second == withEnumPairOptionalTest.withEnumPairOptional.second);
}

TEST_CASE ("WithEnumPairOptional with value combination", "[combination]")
{
  auto withEnumPairOptional = shared_class::WithEnumPairOptional{};
  withEnumPairOptional.withEnumPairOptional.first = shared_class::PlayerRole::waiting;
  withEnumPairOptional.withEnumPairOptional.second = std::nullopt;
  auto withEnumPairOptionalTest = to_object<shared_class::WithEnumPairOptional> (to_json (withEnumPairOptional));
  REQUIRE (withEnumPairOptional.withEnumPairOptional.first == withEnumPairOptionalTest.withEnumPairOptional.first);
  REQUIRE_FALSE (withEnumPairOptionalTest.withEnumPairOptional.second.has_value ());
}

TEST_CASE ("WithEnumVector combination", "[combination]")
{
  auto withEnumVector = shared_class::WithEnumVector{};
  auto withEnumVectorTest = to_object<shared_class::WithEnumVector> (to_json (withEnumVector));
  REQUIRE (withEnumVectorTest.withEnumVector.empty ());
  withEnumVector = shared_class::WithEnumVector{};
  withEnumVector.withEnumVector = std::vector<shared_class::PlayerRole> (1);
  withEnumVectorTest = to_object<shared_class::WithEnumVector> (to_json (withEnumVector));
  REQUIRE_FALSE (withEnumVectorTest.withEnumVector.empty ());
}

TEST_CASE ("WithEnumVectorOptional combination", "[combination]")
{
  auto withEnumVectorOptional = shared_class::WithEnumVectorOptional{};
  auto withEnumVectorOptionalTest = to_object<shared_class::WithEnumVectorOptional> (to_json (withEnumVectorOptional));
  REQUIRE (withEnumVectorOptionalTest.withEnumVectorOptional.empty ());
  withEnumVectorOptional = shared_class::WithEnumVectorOptional{};
  withEnumVectorOptional.withEnumVectorOptional.push_back (shared_class::PlayerRole::defend);
  withEnumVectorOptional.withEnumVectorOptional.push_back (std::nullopt);
  withEnumVectorOptionalTest = to_object<shared_class::WithEnumVectorOptional> (to_json (withEnumVectorOptional));
  REQUIRE_FALSE (withEnumVectorOptionalTest.withEnumVectorOptional.empty ());
  REQUIRE (withEnumVectorOptionalTest.withEnumVectorOptional.at (0).has_value ());
  REQUIRE_FALSE (withEnumVectorOptionalTest.withEnumVectorOptional.at (1).has_value ());
}

TEST_CASE ("WithEnumPairVector combination", "[combination]")
{
  auto withEnumPairVector = shared_class::WithEnumPairVector{};
  auto withEnumPairVectorTest = to_object<shared_class::WithEnumPairVector> (to_json (withEnumPairVector));
  REQUIRE (withEnumPairVectorTest.withEnumPairVector.empty ());
  withEnumPairVector = shared_class::WithEnumPairVector{};
  withEnumPairVector.withEnumPairVector.push_back (std::pair<shared_class::PlayerRole, shared_class::PlayerRole>{ shared_class::PlayerRole::waiting, shared_class::PlayerRole::assistAttacker });
  withEnumPairVector.withEnumPairVector.push_back (std::pair<shared_class::PlayerRole, shared_class::PlayerRole>{});
  withEnumPairVectorTest = to_object<shared_class::WithEnumPairVector> (to_json (withEnumPairVector));
  REQUIRE (withEnumPairVectorTest.withEnumPairVector.size () == 2);
  REQUIRE (withEnumPairVectorTest.withEnumPairVector.front ().first == shared_class::PlayerRole::waiting);
  REQUIRE (withEnumPairVectorTest.withEnumPairVector.front ().second == shared_class::PlayerRole::assistAttacker);
}

TEST_CASE ("WithEnumPairOptionalVector combination", "[combination]")
{
  auto withEnumPairOptionalVector = shared_class::WithEnumPairOptionalVector{};
  auto withEnumPairOptionalVectorTest = to_object<shared_class::WithEnumPairOptionalVector> (to_json (withEnumPairOptionalVector));
  REQUIRE (withEnumPairOptionalVectorTest.withEnumPairOptionalVector.empty ());
  withEnumPairOptionalVector = shared_class::WithEnumPairOptionalVector{};
  withEnumPairOptionalVector.withEnumPairOptionalVector.push_back (std::pair<shared_class::PlayerRole, std::optional<shared_class::PlayerRole>>{ shared_class::PlayerRole::waiting, shared_class::PlayerRole::assistAttacker });
  withEnumPairOptionalVector.withEnumPairOptionalVector.push_back (std::pair<shared_class::PlayerRole, std::optional<shared_class::PlayerRole>>{ shared_class::PlayerRole::waiting, std::nullopt });
  REQUIRE (withEnumPairOptionalVector.withEnumPairOptionalVector.size () == 2);
  REQUIRE (withEnumPairOptionalVector.withEnumPairOptionalVector.at (0).first == shared_class::PlayerRole::waiting);
  REQUIRE (withEnumPairOptionalVector.withEnumPairOptionalVector.at (0).second == shared_class::PlayerRole::assistAttacker);
  REQUIRE (withEnumPairOptionalVector.withEnumPairOptionalVector.at (1).first == shared_class::PlayerRole::waiting);
  REQUIRE_FALSE (withEnumPairOptionalVector.withEnumPairOptionalVector.at (1).second.has_value ());
}

TEST_CASE ("CreateAccount combination", "[combination]")
{
  auto createAccount = shared_class::CreateAccount{};
  createAccount.accountName = "aa";
  createAccount.password = "aa";
  auto createAccountTest = to_object<shared_class::CreateAccount> (to_json (createAccount));
  REQUIRE (createAccount.accountName == createAccountTest.accountName);
  REQUIRE (createAccount.password == createAccountTest.password);
}

TEST_CASE ("UsersInGameLobby combination", "[test]")
{
  auto jsonAsText = std::string{ R"foo({"name":"huhu","users":[{"UserInGameLobby":{"accountName":"aa"}},{"UserInGameLobby":{"accountName":"bb"}}],"maxUserSize":2})foo" };
  error_code ec{};
  auto value = read_json (jsonAsText, ec);
  auto usersInGameLobby = to_object<shared_class::UsersInGameLobby> (value);
  std::cout << ec.message () << std::endl;
  REQUIRE (usersInGameLobby.maxUserSize == 2);
}

TEST_CASE ("DurakTimers", "[to_json]")
{
  auto durakTimers = shared_class::DurakTimers{};
  durakTimers.runningTimeUserTimePointMilliseconds.push_back (std::make_pair ("some string", 42));
  auto durakTimersTest = to_object<shared_class::DurakTimers> (to_json (durakTimers));
  REQUIRE (durakTimers.runningTimeUserTimePointMilliseconds.at (0).first == durakTimersTest.runningTimeUserTimePointMilliseconds.at (0).first);
  REQUIRE (durakTimers.runningTimeUserTimePointMilliseconds.at (0).second == durakTimersTest.runningTimeUserTimePointMilliseconds.at (0).second);
}

TEST_CASE ("OptionalVectorHasValue", "[combine]")
{
  auto optionalVector = shared_class::OptionalVector{ { { "huhu" } }, { { 42 } }, { { shared_class::Nested{} } } };
  std::cout << to_json (optionalVector);
  auto optionalVectorTest = to_object<shared_class::OptionalVector> (to_json (optionalVector));
  REQUIRE (optionalVectorTest.optionalVectorInt.has_value ());
  REQUIRE (optionalVectorTest.optionalVectorString.has_value ());
  REQUIRE (optionalVectorTest.optionalVectorNested.has_value ());
  REQUIRE (optionalVector.optionalVectorString.value () == optionalVectorTest.optionalVectorString.value ());
  REQUIRE (optionalVector.optionalVectorInt.value () == optionalVectorTest.optionalVectorInt.value ());
  REQUIRE (optionalVector.optionalVectorNested.value ().at (0).answer == optionalVectorTest.optionalVectorNested.value ().at (0).answer);
}

TEST_CASE ("OptionalVector", "[combine]")
{
  auto optionalVector = shared_class::OptionalVector{};
  std::cout << to_json (optionalVector);
  auto optionalVectorTest = to_object<shared_class::OptionalVector> (to_json (optionalVector));
  REQUIRE_FALSE (optionalVectorTest.optionalVectorInt.has_value ());
  REQUIRE_FALSE (optionalVectorTest.optionalVectorString.has_value ());
  REQUIRE_FALSE (optionalVectorTest.optionalVectorNested.has_value ());
}