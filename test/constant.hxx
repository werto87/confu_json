#ifndef FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7
#define FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/optional/optional_io.hpp>

namespace shared_class
{

enum struct PlayerRole
{
  attack,
  defend,
  assistAttacker,
  waiting
};
}

BOOST_FUSION_DEFINE_STRUCT ((shared_class), WithEnum, (shared_class::PlayerRole, playerRole))
BOOST_FUSION_DEFINE_STRUCT ((shared_class), WithEnumOptional, (std::optional<shared_class::PlayerRole>, playerRoleOptional))

namespace shared_class
{
struct WithEnumPair
{
  std::pair<shared_class::PlayerRole, shared_class::PlayerRole> withEnumPair{};
};
}

BOOST_FUSION_ADAPT_STRUCT (shared_class::WithEnumPair, withEnumPair)

namespace shared_class
{
struct WithEnumPairOptional
{
  std::pair<shared_class::PlayerRole, std::optional<shared_class::PlayerRole>> withEnumPairOptional{};
};
}

BOOST_FUSION_ADAPT_STRUCT (shared_class::WithEnumPairOptional, withEnumPairOptional)

BOOST_FUSION_DEFINE_STRUCT ((shared_class), WithEnumVector, (std::vector<shared_class::PlayerRole>, withEnumVector))
BOOST_FUSION_DEFINE_STRUCT ((shared_class), WithEnumVectorOptional, (std::vector<std::optional<shared_class::PlayerRole>>, withEnumVectorOptional))

namespace shared_class
{
struct WithEnumPairVector
{
  std::vector<std::pair<shared_class::PlayerRole, shared_class::PlayerRole>> withEnumPairVector{};
};
}

BOOST_FUSION_ADAPT_STRUCT (shared_class::WithEnumPairVector, withEnumPairVector)

namespace shared_class
{
struct WithEnumPairOptionalVector
{
  std::vector<std::pair<shared_class::PlayerRole, std::optional<shared_class::PlayerRole>>> withEnumPairOptionalVector{};
};
}

BOOST_FUSION_ADAPT_STRUCT (shared_class::WithEnumPairOptionalVector, withEnumPairOptionalVector)

namespace shared_class
{
struct VectorWithPairOfInt
{
  std::vector<std::pair<int, int>> vectorWithPairOfInt{};
};
}

BOOST_FUSION_ADAPT_STRUCT (shared_class::VectorWithPairOfInt, vectorWithPairOfInt)

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

BOOST_FUSION_DEFINE_STRUCT ((shared_class), CreateAccount, (std::string, accountName) (std::string, password))
#endif /* FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7 */
