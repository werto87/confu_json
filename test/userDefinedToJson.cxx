#include "confu_json/to_json.hxx"
#include "test/constant.hxx"
#include <catch2/catch.hpp>
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