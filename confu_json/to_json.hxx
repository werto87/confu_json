//
// Copyright (c) 2021 Waldemar Schneider (w-schneider1987 at web dot de)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef A2E0641F_EBD5_4C94_9A72_19B4473D5677
#define A2E0641F_EBD5_4C94_9A72_19B4473D5677

#include "confu_json/concept.hxx"
#include "confu_json/util.hxx"
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/back.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/size.hpp>
#include <magic_enum.hpp>

namespace confu_json
{
template <class T> void handlePair (boost::json::object &result, T const &member, std::string const &memberName);
template <class T> bool handleOptional (boost::json::object &result, T const &t, std::string const &memberName);
template <class T> boost::json::object to_json (T const &t);

template <typename> struct Debug;

template <class T>
void
handleArray (boost::json::array &result, T const &t)
{
  using elementType = std::decay_t<decltype (t.front ())>;
  using namespace boost::json;
  for (auto const &element : t)
    {
      object tmp;
      if constexpr (is_std_or_boost_optional<elementType> ())
        {
          using optionalType = std::decay_t<decltype (element.value ())>;
          if constexpr (boost::fusion::traits::is_sequence<optionalType>::value)
            {
              if (handleOptional (tmp, element, std::string{ type_name<elementType> () }))
                {
                  result.push_back (tmp);
                }
              else
                {
                  result.push_back (nullptr);
                }
            }
          else
            {
              if (element.has_value ())
                {
                  if constexpr (std::is_enum_v<optionalType>)
                    {
                      tmp[std::string{ type_name<optionalType> () }] = std::string{ magic_enum::enum_name (element.value ()) };
                      std::cout << tmp << std::endl;
                      result.emplace_back (tmp);
                    }
                  else
                    {
                      result.emplace_back (element.value ());
                    }
                }
              else
                {
                  result.push_back (nullptr);
                }
            }
        }
      else if constexpr (is_std_pair<elementType>::value)
        {
          handlePair (tmp, element, std::string{ type_name<elementType> () });
          result.push_back (tmp.at (std::string{ type_name<elementType> () }).as_array ());
        }
      else if constexpr (boost::fusion::traits::is_sequence<elementType>::value)
        {
          tmp[std::string{ type_name<elementType> () }] = to_json (element);
          result.push_back (tmp);
        }
      else if constexpr (is_std_vector<elementType>::value)
        {
          using namespace boost::json;
          array tmpArray;
          handleArray (tmpArray, element);
          result.push_back (tmpArray);
        }
      else
        {
          if constexpr (std::is_enum_v<elementType>)
            {
              tmp[std::string{ type_name<elementType> () }] = std::string{ magic_enum::enum_name (element) };
              result.push_back (tmp);
            }
          else
            {
              result.emplace_back (element);
            }
        }
    }
}

template <class T>
bool
handleOptional (boost::json::object &result, T const &t, std::string const &memberName)
{
  using optionalType = typename std::decay<decltype (t.value ())>::type;
  if constexpr (boost::fusion::traits::is_sequence<optionalType>::value)
    {
      if (t.has_value ())
        {
          result[memberName] = to_json (t.value ());
          return true;
        }
      else
        {
          result[memberName] = nullptr;
          return false;
        }
    }
  else
    {
      if (t.has_value ())
        {
          if constexpr (std::is_enum_v<optionalType>)
            {
              result[memberName] = std::string{ magic_enum::enum_name (t.value ()) };
            }
          else
            {
              if constexpr (is_std_vector<optionalType>::value)
                {
                  // handle optional case when vector is optional
                  using namespace boost::json;
                  array tmp;
                  handleArray (tmp, t.value ());
                  result[memberName] = tmp;
                }
              else
                {
                  result[memberName] = t.value ();
                }
            }
          return true;
        }
      else
        {
          result[memberName] = nullptr;
          return false;
        }
    }
}

template <class T>
void
handlePair (boost::json::object &result, T const &member, std::string const &memberName)
{
  using namespace boost::json;
  using pairTypeFirst = std::decay_t<decltype (member.first)>;
  using pairTypeSecond = std::decay_t<decltype (member.second)>;
  array pairArray;
  if constexpr (is_std_or_boost_optional<pairTypeFirst> ())
    {
      if constexpr (boost::fusion::traits::is_sequence<pairTypeFirst>::value) // looks fishy how can the type be optional and fusion sequence
        {
          object wrapper;
          if (handleOptional (wrapper, member.first, std::string{ type_name<pairTypeFirst> () }))
            {
              pairArray.emplace_back (wrapper);
            }
          else
            {
              pairArray.emplace_back (nullptr);
            }
        }
      else
        {
          object wrapper;
          if (handleOptional (wrapper, member.first, std::string{ type_name<pairTypeFirst> () }))
            {
              pairArray.emplace_back (wrapper);
            }
          else
            {
              pairArray.emplace_back (nullptr);
            }
        }
    }
  else
    {
      if constexpr (boost::fusion::traits::is_sequence<pairTypeFirst>::value)
        {
          object wrapper;
          wrapper[std::string{ type_name<pairTypeFirst> () }] = to_json (member.first);
          pairArray.emplace_back (wrapper);
        }
      else
        {
          if constexpr (std::is_enum_v<pairTypeFirst>)
            {
              object wrapper;
              wrapper[std::string{ type_name<pairTypeSecond> () }] = std::string{ magic_enum::enum_name (member.first) };
              pairArray.emplace_back (wrapper);
            }
          else
            {
              pairArray.emplace_back (member.first);
            }
        }
    }
  if constexpr (is_std_or_boost_optional<pairTypeSecond> ())
    {
      if constexpr (boost::fusion::traits::is_sequence<pairTypeSecond>::value) // looks fishy how can the type be optional and fusion sequence
        {
          object wrapper;
          if (handleOptional (wrapper, member.second, std::string{ type_name<pairTypeSecond> () }))
            {
              pairArray.emplace_back (wrapper);
            }
          else
            {
              pairArray.emplace_back (nullptr);
            }
        }
      else
        {
          object wrapper;
          if (handleOptional (wrapper, member.second, std::string{ type_name<pairTypeSecond> () }))
            {
              pairArray.emplace_back (wrapper);
            }
          else
            {
              pairArray.emplace_back (nullptr);
            }
        }
    }
  else
    {
      if constexpr (boost::fusion::traits::is_sequence<pairTypeSecond>::value)
        {
          object wrapper;
          wrapper[std::string{ type_name<pairTypeSecond> () }] = to_json (member.second);
          pairArray.emplace_back (wrapper);
        }
      else
        {
          if constexpr (std::is_enum_v<pairTypeSecond>)
            {
              object wrapper;
              wrapper[std::string{ type_name<pairTypeSecond> () }] = std::string{ magic_enum::enum_name (member.second) };
              pairArray.emplace_back (wrapper);
            }
          else
            {
              pairArray.emplace_back (member.second);
            }
        }
    }
  result[memberName] = pairArray;
}

template <class T>
boost::json::object
to_json (T const &t)
{
  using namespace boost::json;
  object obj{};
  boost::fusion::for_each (boost::mpl::range_c<unsigned, 0, boost::fusion::result_of::size<T>::value> (), [&] (auto index) {
    using currentType = typename std::decay<decltype (boost::fusion::at_c<index> (t))>::type;
    auto &member = boost::fusion::at_c<index> (t);
    auto memberName = boost::fusion::extension::struct_member_name<T, index>::call ();
    if constexpr (is_std_or_boost_optional<currentType> ())
      {
        handleOptional (obj, member, memberName);
      }
    else if constexpr (std::is_enum_v<currentType>)
      {
        obj[memberName] = std::string{ magic_enum::enum_name (member) };
      }
    else if constexpr (is_std_vector<currentType>::value)
      {
        array result;
        handleArray (result, member);
        obj[memberName] = result;
      }
    else if constexpr (is_std_pair<currentType>::value)
      {
        handlePair (obj, member, memberName);
      }
    else if constexpr (boost::fusion::traits::is_sequence<currentType>::value)
      {
        obj[memberName] = to_json (member);
      }
    else
      {
        obj[memberName] = member;
      }
  });
  return obj;
}
}

#endif /* A2E0641F_EBD5_4C94_9A72_19B4473D5677 */
