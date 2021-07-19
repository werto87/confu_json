#include "confu_json/to_json.hxx"
#include "test/constant.hxx"
#include <catch2/catch.hpp>
#include <optional>
#include <utility>
using namespace boost::json;
using namespace confu_json;
TEST_CASE ("Nested to_json", "[to_json]")
{
  auto nested = shared_class::Nested{};
  nested.answer = 42;
  std::cout << to_json (nested) << std::endl;
}

TEST_CASE ("Student optionals null", "[to_json]")
{
  auto student = shared_class::Student{};
  std::cout << to_json (student) << std::endl;
}

TEST_CASE ("Student optionals have value", "[to_json]")
{
  auto student = shared_class::Student{};
  student.nothingInt = 42;
  student.nothingBool = true;
  student.nothingString = "huhu";
  student.nested.answer = 42;
  student.nestedOptional = shared_class::Nested{ 42 };
  std::cout << to_json (student) << std::endl;
}

TEST_CASE ("NestedPair", "[to_json]")
{
  auto nestedPair = shared_class::NestedPair{};
  nestedPair.nestedPair.first = shared_class::Nested{ 1337 };
  nestedPair.nestedPair.second = shared_class::Nested{ 42 };
  nestedPair.i = 5;
  std::cout << to_json (nestedPair) << std::endl;
}

TEST_CASE ("NestedPairOptional", "[to_json]")
{
  auto nestedPairOptional = shared_class::NestedPairOptional{};
  nestedPairOptional.nestedPairOptional.first = shared_class::Nested{ 1337 };
  nestedPairOptional.nestedPairOptional.second = shared_class::Nested{ 42 };
  std::cout << to_json (nestedPairOptional) << std::endl;
}

TEST_CASE ("NestedPairOptional non value", "[to_json]")
{
  auto nestedPairOptional = shared_class::NestedPairOptional{};
  nestedPairOptional.nestedPairOptional.first = shared_class::Nested{ 1337 };
  std::cout << to_json (nestedPairOptional) << std::endl;
}

TEST_CASE ("NestedVector to_json", "[to_json]")
{
  auto nestedVector = shared_class::NestedVector{};
  nestedVector.nestedVector.push_back (shared_class::Nested{ 42 });
  nestedVector.intVector.push_back (1);
  std::cout << to_json (nestedVector) << std::endl;
}

TEST_CASE ("NestedVectorOptional to_json", "[to_json]")
{
  auto nestedVectorOptional = shared_class::NestedVectorOptional{};
  nestedVectorOptional.nestedVectorOptional.push_back (shared_class::Nested{ 42 });
  nestedVectorOptional.nestedVectorOptional.push_back (shared_class::Nested{ 55 });
  nestedVectorOptional.intNestedVectorOptional.push_back (1);
  nestedVectorOptional.intNestedVectorOptional.push_back (2);
  nestedVectorOptional.stringNestedVectorOptional.push_back (std::string{ "huhu" });
  nestedVectorOptional.stringNestedVectorOptional.push_back (std::string{ "fox" });
  std::cout << to_json (nestedVectorOptional) << std::endl;
}

TEST_CASE ("NestedVectorOptional to_json with nullptr", "[to_json]")
{
  auto nestedVectorOptional = shared_class::NestedVectorOptional{};
  nestedVectorOptional.nestedVectorOptional.push_back (shared_class::Nested{ 42 });
  nestedVectorOptional.nestedVectorOptional.push_back ({});
  nestedVectorOptional.intNestedVectorOptional.push_back (1);
  nestedVectorOptional.intNestedVectorOptional.push_back ({});
  nestedVectorOptional.stringNestedVectorOptional.push_back (std::string{ "huhu" });
  nestedVectorOptional.stringNestedVectorOptional.push_back (boost::optional<std::string>{});
  std::cout << to_json (nestedVectorOptional) << std::endl;
}

TEST_CASE ("NestedPairVector to_json", "[to_json]")
{
  auto nestedPairVector = shared_class::NestedPairVector{};
  nestedPairVector.nestedPairVector.push_back (std::pair<shared_class::Nested, shared_class::Nested>{ shared_class::Nested{ 42 }, shared_class::Nested{ 42 } });
  nestedPairVector.nestedPairVector.push_back (std::pair<shared_class::Nested, shared_class::Nested>{ shared_class::Nested{ 32 }, shared_class::Nested{ 32 } });
  std::cout << to_json (nestedPairVector) << std::endl;
}

TEST_CASE ("NestedPairOptionalVector to_json", "[to_json]")
{
  auto nestedPairOptionalVector = shared_class::NestedPairOptionalVector{};
  nestedPairOptionalVector.nestedPairOptionalVector.push_back (std::pair<shared_class::Nested, boost::optional<shared_class::Nested>>{ shared_class::Nested{ 42 }, shared_class::Nested{ 42 } });
  nestedPairOptionalVector.nestedPairOptionalVector.push_back (std::pair<shared_class::Nested, boost::optional<shared_class::Nested>>{ shared_class::Nested{ 32 }, boost::optional<shared_class::Nested>{} });
  std::cout << to_json (nestedPairOptionalVector) << std::endl;
}

TEST_CASE ("Enum", "[to_json]")
{
  auto withEnum = shared_class::WithEnum{};
  std::cout << to_json (withEnum) << std::endl;
}

TEST_CASE ("EnumOptional", "[to_json]")
{
  auto withEnumOptional = shared_class::WithEnumOptional{};
  std::cout << to_json (withEnumOptional) << std::endl;
  withEnumOptional = shared_class::WithEnumOptional{};
  withEnumOptional.playerRoleOptional = shared_class::PlayerRole::defend;
  std::cout << to_json (withEnumOptional) << std::endl;
}

TEST_CASE ("WithEnumPair", "[to_json]")
{
  auto withEnumPair = shared_class::WithEnumPair{};
  withEnumPair.withEnumPair.second = shared_class::PlayerRole::defend;
  std::cout << to_json (withEnumPair) << std::endl;
}

TEST_CASE ("WithEnumPairOptional", "[to_json]")
{
  auto withEnumPairOptional = shared_class::WithEnumPairOptional{};
  std::cout << to_json (withEnumPairOptional) << std::endl;
  withEnumPairOptional = shared_class::WithEnumPairOptional{};
  withEnumPairOptional.withEnumPairOptional.second = shared_class::PlayerRole::defend;
  std::cout << to_json (withEnumPairOptional) << std::endl;
}

TEST_CASE ("WithEnumVector", "[to_json]")
{
  auto withEnumVector = shared_class::WithEnumVector{};
  std::cout << to_json (withEnumVector) << std::endl;
  withEnumVector = shared_class::WithEnumVector{};
  withEnumVector.withEnumVector.push_back (shared_class::PlayerRole::defend);
  withEnumVector.withEnumVector.push_back (shared_class::PlayerRole::attack);
  std::cout << to_json (withEnumVector) << std::endl;
}

TEST_CASE ("WithEnumVectorOptional", "[to_json]")
{
  auto withEnumVectorOptional = shared_class::WithEnumVectorOptional{};
  std::cout << to_json (withEnumVectorOptional) << std::endl;
  withEnumVectorOptional = shared_class::WithEnumVectorOptional{};
  withEnumVectorOptional.withEnumVectorOptional.push_back (shared_class::PlayerRole::defend);
  withEnumVectorOptional.withEnumVectorOptional.push_back (std::nullopt);
  std::cout << to_json (withEnumVectorOptional) << std::endl;
}

TEST_CASE ("WithEnumPairVector", "[to_json]")
{
  auto withEnumPairVector = shared_class::WithEnumPairVector{};
  std::cout << to_json (withEnumPairVector) << std::endl;
  withEnumPairVector = shared_class::WithEnumPairVector{};
  withEnumPairVector.withEnumPairVector = std::vector<std::pair<shared_class::PlayerRole, shared_class::PlayerRole>> (2);
  std::cout << to_json (withEnumPairVector) << std::endl;
}

TEST_CASE ("WithEnumPairOptionalVector", "[to_json]")
{
  auto withEnumPairOptionalVector = shared_class::WithEnumPairOptionalVector{};
  std::cout << to_json (withEnumPairOptionalVector) << std::endl;
  withEnumPairOptionalVector = shared_class::WithEnumPairOptionalVector{};
  auto withValue = std::pair<shared_class::PlayerRole, std::optional<shared_class::PlayerRole>>{};
  withValue.second = shared_class::PlayerRole::defend;
  withEnumPairOptionalVector.withEnumPairOptionalVector.push_back (withValue);
  auto withMissingvalue = std::pair<shared_class::PlayerRole, std::optional<shared_class::PlayerRole>>{};
  withMissingvalue.second = std::nullopt;
  withEnumPairOptionalVector.withEnumPairOptionalVector.push_back (withMissingvalue);
  std::cout << to_json (withEnumPairOptionalVector) << std::endl;
}

TEST_CASE ("VectorWithPairOfInt", "[to_json]")
{
  auto vectorWithPairOfInt = shared_class::VectorWithPairOfInt{};
  std::cout << to_json (vectorWithPairOfInt) << std::endl;
  vectorWithPairOfInt.vectorWithPairOfInt.push_back (std::make_pair (1, 2));
  std::cout << to_json (vectorWithPairOfInt) << std::endl;
}
TEST_CASE ("CreateAccount", "[to_json]")
{
  auto createAccount = shared_class::CreateAccount{};
  createAccount.accountName = "aa";
  createAccount.password = "aa";
  std::cout << to_json (createAccount) << std::endl;
}

TEST_CASE ("UsersInGameLobby", "[to_json]")
{
  auto usersInGameLobby = shared_class::UsersInGameLobby{};
  std::cout << to_json (usersInGameLobby) << std::endl;
  usersInGameLobby.maxUserSize = 2;
  usersInGameLobby.name = "huhu";
  usersInGameLobby.users = std::vector<shared_class::UserInGameLobby> (2);
  usersInGameLobby.users.at (0).accountName = "aa";
  usersInGameLobby.users.at (1).accountName = "bb";
  std::cout << to_json (usersInGameLobby) << std::endl;
}
