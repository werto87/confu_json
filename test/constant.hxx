#ifndef FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7
#define FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/optional/optional_io.hpp>

BOOST_FUSION_DEFINE_STRUCT ((shared_class), Nested, (long, answer))
BOOST_FUSION_DEFINE_STRUCT ((shared_class), Student, (long, answer) (bool, happy) (std::string, name) (boost::optional<int>, nothingInt) (boost::optional<bool>, nothingBool) (boost::optional<std::string>, nothingString) (shared_class::Nested, nested) (boost::optional<shared_class::Nested>, nestedOptional))
BOOST_FUSION_DEFINE_STRUCT ((shared_class), NestedVector, (std::vector<int>, intVector) (std::vector<shared_class::Nested>, nestedVector))
namespace shared_class
{
struct NestedPair
{
  std::pair<shared_class::Nested, shared_class::Nested> nestedPair{};
  int i{};
};
}
BOOST_FUSION_ADAPT_STRUCT (shared_class::NestedPair, nestedPair, i)

namespace shared_class
{
struct NestedPairOptional
{
  std::pair<shared_class::Nested, boost::optional<shared_class::Nested>> nestedPairOptional{};
};
}
BOOST_FUSION_ADAPT_STRUCT (shared_class::NestedPairOptional, nestedPairOptional)

namespace shared_class
{
struct NestedPairVector
{
  std::vector<std::pair<shared_class::Nested, shared_class::Nested>> nestedPairVector{};
  int i{};
};
}
BOOST_FUSION_ADAPT_STRUCT (shared_class::NestedPairVector, nestedPairVector)

namespace shared_class
{
struct NestedVectorOptional
{
  std::vector<boost::optional<int>> intNestedVectorOptional{};
  std::vector<boost::optional<std::string>> stringNestedVectorOptional{};
  std::vector<boost::optional<shared_class::Nested>> nestedVectorOptional{};
};
}
BOOST_FUSION_ADAPT_STRUCT (shared_class::NestedVectorOptional, intNestedVectorOptional, stringNestedVectorOptional, nestedVectorOptional)

namespace shared_class
{
struct NestedPairOptionalVector
{
  std::vector<std::pair<shared_class::Nested, boost::optional<shared_class::Nested>>> nestedPairOptionalVector{};
};
}
BOOST_FUSION_ADAPT_STRUCT (shared_class::NestedPairOptionalVector, nestedPairOptionalVector)

#endif /* FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7 */
