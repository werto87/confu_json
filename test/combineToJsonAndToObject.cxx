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