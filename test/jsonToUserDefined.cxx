#include "confu_json/confu_json.hxx"
#include "test/constant.hxx"
#include <catch2/catch.hpp>
using namespace boost::json;
using namespace confu_json;
namespace test
{
TEST_CASE ("durak::Type", "[test]")
{
  object obj;
  obj["answer"] = 42;
  obj["happy"] = true;
  obj["name"] = "";
  obj["nothingInt"] = nullptr;
  obj["nothingBool"] = nullptr;
  obj["nothingString"] = nullptr;
  obj["nested"] = { { "answer", 1337 } };
  obj["nestedOptional"] = nullptr;
  std::stringstream is{};
  error_code ec{};
  is << obj;
  auto value = read_json (is, ec);
  std::cout << "object to serilalize: " << obj << std::endl;
  std::cout << std::boolalpha;
  std::cout << to_object<shared_class::Student> (value).answer << std::endl;
  std::cout << to_object<shared_class::Student> (value).happy << std::endl;
  std::cout << to_object<shared_class::Student> (value).name << std::endl;
  std::cout << to_object<shared_class::Student> (value).nothingInt << std::endl;
  std::cout << to_object<shared_class::Student> (value).nothingBool << std::endl;
  std::cout << to_object<shared_class::Student> (value).nothingString << std::endl;
  std::cout << to_object<shared_class::Student> (value).nested.answer << std::endl;
  std::cout << to_object<shared_class::Student> (value).nestedOptional.has_value () << std::endl;
  object objWithValue;                                     // construct an empty object
  objWithValue["answer"] = 42;                             // insert int
  objWithValue["happy"] = true;                            // insert a bool
  objWithValue["name"] = "Boost";                          // insert a string
  objWithValue["nothingInt"] = 55;                         // insert a null
  objWithValue["nothingBool"] = true;                      // insert a null
  objWithValue["nothingString"] = "optionalString";        // insert a null
  objWithValue["nested"] = { { "answer", 1337 } };         // insert a object
  objWithValue["nestedOptional"] = { { "answer", 1337 } }; // insert a object
  is.clear ();
  is << objWithValue;
  std::cout << "object to serilalize: " << objWithValue << std::endl;
  value = read_json (is, ec);
  std::cout << to_object<shared_class::Student> (value).nothingInt << std::endl;
  std::cout << to_object<shared_class::Student> (value).nothingBool << std::endl;
  std::cout << to_object<shared_class::Student> (value).nothingString << std::endl;
  std::cout << to_object<shared_class::Student> (value).nested.answer << std::endl;
  std::cout << to_object<shared_class::Student> (value).nestedOptional.has_value () << std::endl;
  std::cout << to_object<shared_class::Student> (value).nestedOptional->answer << std::endl;
  std::cout << std::noboolalpha;
}

TEST_CASE ("pair", "[test]")
{
  array arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  object obj3;
  obj3["Nested"] = { { "answer", 123 } };
  arr.emplace_back (obj);
  arr.emplace_back (obj3);
  object obj2;
  obj2["nestedPair"] = arr;
  obj2["i"] = 42;
  std::stringstream is{};
  error_code ec{};
  is << obj2;
  auto value = read_json (is, ec);
  std::cout << obj2 << std::endl;
  std::cout << to_object<shared_class::NestedPair> (value).i << std::endl;
  std::cout << to_object<shared_class::NestedPair> (value).nestedPair.first.answer << std::endl;
  std::cout << to_object<shared_class::NestedPair> (value).nestedPair.second.answer << std::endl;
}

TEST_CASE ("pairOptional with value", "[test]")
{
  array arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  object obj3;
  obj3["Nested"] = { { "answer", 123 } };
  arr.emplace_back (obj);
  arr.emplace_back (obj3);
  object obj2;
  obj2["nestedPairOptional"] = arr;
  std::stringstream is{};
  error_code ec{};
  is << obj2;
  auto value = read_json (is, ec);
  std::cout << obj2 << std::endl;
  std::cout << std::boolalpha;
  std::cout << to_object<shared_class::NestedPairOptional> (value).nestedPairOptional.first.answer << std::endl;
  std::cout << to_object<shared_class::NestedPairOptional> (value).nestedPairOptional.second.has_value () << std::endl;
  std::cout << to_object<shared_class::NestedPairOptional> (value).nestedPairOptional.second.value ().answer << std::endl;
}

TEST_CASE ("pairOptional without value", "[test]")
{
  array arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  object obj3;

  arr.emplace_back (obj);
  arr.emplace_back (nullptr);
  object obj2;
  obj2["nestedPairOptional"] = arr;
  std::stringstream is{};
  error_code ec{};
  is << obj2;
  auto value = read_json (is, ec);
  std::cout << obj2 << std::endl;
  std::cout << std::boolalpha;
  std::cout << to_object<shared_class::NestedPairOptional> (value).nestedPairOptional.first.answer << std::endl;
  std::cout << to_object<shared_class::NestedPairOptional> (value).nestedPairOptional.second.has_value () << std::endl;
  // std::cout << to_object<shared_class::NestedPairOptional> (value).nestedPairOptional.second.value ().answer << std::endl;
}

TEST_CASE ("vector", "[test]")
{
  array arr;
  arr.emplace_back (42);
  arr.emplace_back (43);
  object obj2;
  obj2["intVector"] = arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  array arr2;
  arr2.emplace_back (obj);
  arr2.emplace_back (obj);
  obj2["nestedVector"] = arr2;
  std::stringstream is{};
  error_code ec{};
  is << obj2;
  auto value = read_json (is, ec);
  std::cout << obj2 << std::endl;
  std::cout << std::boolalpha;
  std::cout << to_object<shared_class::NestedVector> (value).intVector.at (0) << std::endl;
  std::cout << to_object<shared_class::NestedVector> (value).intVector.at (1) << std::endl;
  std::cout << to_object<shared_class::NestedVector> (value).nestedVector.at (0).answer << std::endl;
  std::cout << to_object<shared_class::NestedVector> (value).nestedVector.at (1).answer << std::endl;
}

TEST_CASE ("NestedVectorOptional", "[test]")
{
  // TODO [pair] think about if it makes sense to have something like
  // [{"Nested":{"answer":42}},{"Nested":{"answer":42}}]
  // maybe we can get rid of the name
  // TODO add new header for convinience

  array arr;
  arr.emplace_back (42);
  arr.emplace_back (43);
  object obj2;
  obj2["intNestedVectorOptional"] = arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  array arr3;
  arr3.emplace_back ("huhu");
  arr3.emplace_back ("huhu321");
  obj2["stringNestedVectorOptional"] = arr3;
  array arr2;
  arr2.emplace_back (obj);
  arr2.emplace_back (obj);
  obj2["nestedVectorOptional"] = arr2;

  std::stringstream is{};
  error_code ec{};
  is << obj2;
  auto value = read_json (is, ec);
  std::cout << obj2 << std::endl;
  std::cout << std::boolalpha;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).intNestedVectorOptional.at (0).value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).intNestedVectorOptional.at (1).value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).stringNestedVectorOptional.at (0).value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).stringNestedVectorOptional.at (1).value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).nestedVectorOptional.at (0).value ().answer << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).nestedVectorOptional.at (1).value ().answer << std::endl;
}

TEST_CASE ("NestedVectorOptional with nullptr", "[test]")
{
  array arr;
  arr.emplace_back (42);
  arr.emplace_back (nullptr);
  object obj2;
  obj2["intNestedVectorOptional"] = arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  array arr3;
  arr3.emplace_back ("huhu");
  arr3.emplace_back (nullptr);
  obj2["stringNestedVectorOptional"] = arr3;
  array arr2;
  arr2.emplace_back (obj);
  arr2.emplace_back (nullptr);
  obj2["nestedVectorOptional"] = arr2;
  std::stringstream is{};
  error_code ec{};
  is << obj2;
  auto value = read_json (is, ec);
  std::cout << obj2 << std::endl;
  std::cout << std::boolalpha;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).intNestedVectorOptional.at (0).value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).intNestedVectorOptional.at (1).has_value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).stringNestedVectorOptional.at (0).value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).stringNestedVectorOptional.at (1).has_value () << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).nestedVectorOptional.at (0).value ().answer << std::endl;
  std::cout << to_object<shared_class::NestedVectorOptional> (value).nestedVectorOptional.at (1).has_value () << std::endl;
}

TEST_CASE ("nestedPairVector", "[test]")
{
  object wrapper;
  array vectorWithPairs;

  array arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  object obj3;
  obj3["Nested"] = { { "answer", 123 } };
  arr.emplace_back (obj);
  arr.emplace_back (obj3);
  array arr3;
  arr3.emplace_back (arr);
  arr3.emplace_back (arr);
  vectorWithPairs.push_back (obj);
  vectorWithPairs.push_back (obj);
  wrapper["nestedPairVector"] = arr3;
  std::stringstream is{};
  error_code ec{};
  is << wrapper;
  auto value = read_json (is, ec);
  std::cout << wrapper << std::endl;
  std::cout << to_object<shared_class::NestedPairVector> (value).nestedPairVector.at (0).first.answer << std::endl;
  std::cout << to_object<shared_class::NestedPairVector> (value).nestedPairVector.at (0).second.answer << std::endl;
  std::cout << to_object<shared_class::NestedPairVector> (value).nestedPairVector.at (1).first.answer << std::endl;
  std::cout << to_object<shared_class::NestedPairVector> (value).nestedPairVector.at (1).second.answer << std::endl;
}

TEST_CASE ("nestedPairVectorOptional", "[test]")
{
  object wrapper;
  array vectorWithPairs;

  array arr;
  object obj;
  obj["Nested"] = { { "answer", 42 } };
  object obj3;
  obj3["Nested"] = { { "answer", 123 } };
  arr.emplace_back (obj);
  arr.emplace_back (obj3);
  array arr2;
  arr2.emplace_back (obj);
  arr2.emplace_back (nullptr);
  array arr3;
  arr3.emplace_back (arr);
  arr3.emplace_back (arr2);
  vectorWithPairs.push_back (obj);
  vectorWithPairs.push_back (obj);
  wrapper["nestedPairOptionalVector"] = arr3;
  std::stringstream is{};
  error_code ec{};
  is << wrapper;
  auto value = read_json (is, ec);
  std::cout << wrapper << std::endl;
  std::cout << to_object<shared_class::NestedPairOptionalVector> (value).nestedPairOptionalVector.at (0).first.answer << std::endl;
  std::cout << to_object<shared_class::NestedPairOptionalVector> (value).nestedPairOptionalVector.at (0).second.value ().answer << std::endl;
  std::cout << to_object<shared_class::NestedPairOptionalVector> (value).nestedPairOptionalVector.at (1).first.answer << std::endl;
  std::cout << to_object<shared_class::NestedPairOptionalVector> (value).nestedPairOptionalVector.at (1).second.has_value () << std::endl;
}

}
