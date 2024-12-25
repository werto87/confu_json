#ifndef FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7
#define FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/detail/adapt_auto.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/map.hpp>
#include <boost/optional/optional_io.hpp>
#include <utility>

namespace user_matchmaking_game
{
class GameOptionBase
{
public:
  virtual ~GameOptionBase () noexcept = default;
};

struct GameOptionWrapper
{
  std::unique_ptr<user_matchmaking_game::GameOptionBase> gameOption{};
};
}

BOOST_FUSION_ADAPT_STRUCT (user_matchmaking_game::GameOptionBase, )
BOOST_FUSION_ADAPT_STRUCT (user_matchmaking_game::GameOptionWrapper, gameOption)

namespace matchmaking_game
{
struct StartGame
{
  std::vector<std::string> players{};
  std::unique_ptr<user_matchmaking_game::GameOptionBase> gameOption{};
  bool ratedGame{};
};

}
BOOST_FUSION_ADAPT_STRUCT (matchmaking_game::StartGame, players, gameOption, ratedGame)

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

struct UniquePtrWithVector
{
  std::unique_ptr<std::vector<int>> uniquePtrVectorInt{};
};
BOOST_FUSION_ADAPT_STRUCT (UniquePtrWithVector, uniquePtrVectorInt)

struct UniquePtrEnum
{
  std::unique_ptr<shared_class::PlayerRole> uniquePtrEnum{};
};
BOOST_FUSION_ADAPT_STRUCT (UniquePtrEnum, uniquePtrEnum)

struct UniquePtrPair
{
  std::unique_ptr<std::pair<int, shared_class::PlayerRole>> uniquePtrPair{};
};
BOOST_FUSION_ADAPT_STRUCT (UniquePtrPair, uniquePtrPair)

struct UniquePtrOptional
{
  std::unique_ptr<std::optional<int>> uniquePtrOptional{};
};
BOOST_FUSION_ADAPT_STRUCT (UniquePtrOptional, uniquePtrOptional)

struct VectorUniquePtr
{
  std::vector<std::unique_ptr<user_matchmaking_game::GameOptionBase>> vectorUniquePtr{};
};
BOOST_FUSION_ADAPT_STRUCT (VectorUniquePtr, vectorUniquePtr)

struct PairUniquePtr
{
  std::pair<std::unique_ptr<user_matchmaking_game::GameOptionBase>, std::unique_ptr<user_matchmaking_game::GameOptionBase>> pairUniquePtr{};
};
BOOST_FUSION_ADAPT_STRUCT (PairUniquePtr, pairUniquePtr)

struct PairUniquePtrAndInt
{
  std::pair<std::unique_ptr<user_matchmaking_game::GameOptionBase>, int> pairUniquePtrAndInt{};
};
BOOST_FUSION_ADAPT_STRUCT (PairUniquePtrAndInt, pairUniquePtrAndInt)

struct PairInt
{
  std::pair<int, int> pairInt{};
};
BOOST_FUSION_ADAPT_STRUCT (PairInt, pairInt)

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
// cppcheck-suppress unknownMacro
BOOST_FUSION_ADAPT_STRUCT (shared_class::NestedPairOptionalVector, nestedPairOptionalVector)
// cppcheck-suppress unknownMacro
BOOST_FUSION_DEFINE_STRUCT ((shared_class), CreateAccount, (std::string, accountName) (std::string, password))
// cppcheck-suppress unknownMacro
BOOST_FUSION_DEFINE_STRUCT ((shared_class), UserInGameLobby, (std::string, accountName))
// cppcheck-suppress unknownMacro
BOOST_FUSION_DEFINE_STRUCT ((shared_class), UsersInGameLobby, (std::string, name) (std::vector<shared_class::UserInGameLobby>, users) (size_t, maxUserSize))

typedef std::vector<std::pair<std::string, long long int>> UserTimeMilliseconds;
// cppcheck-suppress unknownMacro
BOOST_FUSION_DEFINE_STRUCT ((shared_class), DurakTimers, (UserTimeMilliseconds, runningTimeUserTimePointMilliseconds))

namespace shared_class
{
struct OptionalVector
{
  boost::optional<std::vector<std::string>> optionalVectorString{};
  boost::optional<std::vector<int>> optionalVectorInt{};
  boost::optional<std::vector<Nested>> optionalVectorNested{};
};
}
// cppcheck-suppress unknownMacro
BOOST_FUSION_ADAPT_STRUCT (shared_class::OptionalVector, optionalVectorString, optionalVectorInt, optionalVectorNested)
// cppcheck-suppress unknownMacro
BOOST_FUSION_DEFINE_STRUCT ((shared_class), VectorOfVector, (std::vector<std::vector<int>>, vectorOfVector))
// cppcheck-suppress unknownMacro
BOOST_FUSION_DEFINE_STRUCT ((shared_class), OptionalVectorOfVector, (boost::optional<std::vector<std::vector<int>>>, optionalVectorOfVector))
struct GameOption : public user_matchmaking_game::GameOptionBase
{
  int i{};
};
BOOST_FUSION_ADAPT_STRUCT (GameOption, i)
typedef boost::mpl::map<boost::mpl::pair<user_matchmaking_game::GameOptionBase, GameOption>> m;

#endif /* FE334B5B_FA67_454D_A6F5_A1CBF7D02BB7 */
