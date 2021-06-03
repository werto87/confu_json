#ifndef A2E0641F_EBD5_4C94_9A72_19B4473D5677
#define A2E0641F_EBD5_4C94_9A72_19B4473D5677

#include "confu_json/concept.hxx"
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/mpl/range_c.hpp>

namespace confu_json
{

template <class T> boost::json::object to_json (T const &t);

template <class T>
bool
handleOptional (boost::json::object &result, T const &t, std::string const &memberName)
{
  using optionalType = std::remove_reference_t<decltype (t.value ())>;
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
          result[memberName] = t.value ();
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
  using pairTypeFirst = std::remove_reference_t<decltype (member.first)>;
  using pairTypeSecond = std::remove_reference_t<decltype (member.second)>;
  array pairArray;
  if constexpr (IsOptional<pairTypeFirst>)
    {
      if constexpr (boost::fusion::traits::is_sequence<pairTypeFirst>::value)
        {
          object wrapper;
          if (handleOptional (wrapper, member.first, typeNameWithOutNamespace (pairTypeFirst{})))
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
          if (handleOptional (wrapper, member.first, typeNameWithOutNamespace (pairTypeFirst{})))
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
          wrapper[typeNameWithOutNamespace (pairTypeFirst{})] = to_json (member.first);
          pairArray.emplace_back (wrapper);
        }
      else
        {
          pairArray.emplace_back (member.first);
        }
    }
  if constexpr (IsOptional<pairTypeSecond>)
    {
      if constexpr (boost::fusion::traits::is_sequence<pairTypeSecond>::value)
        {
          object wrapper;
          if (handleOptional (wrapper, member.second, typeNameWithOutNamespace (pairTypeSecond{})))
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
          if (handleOptional (wrapper, member.second, typeNameWithOutNamespace (pairTypeSecond{})))
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
          wrapper[typeNameWithOutNamespace (pairTypeSecond{})] = to_json (member.second);
          pairArray.emplace_back (wrapper);
        }
      else
        {
          pairArray.emplace_back (member.second);
        }
    }
  result[memberName] = pairArray;
}

template <class T>
boost::json::object
to_json (T const &t)
{
  using namespace boost::json;
  object obj; // construct an empty object
  boost::fusion::for_each (boost::mpl::range_c<unsigned, 0, boost::fusion::result_of::size<T>::value> (), [&] (auto index) {
    using currentType = std::remove_reference_t<decltype (boost::fusion::at_c<index> (t))>;
    auto &member = boost::fusion::at_c<index> (t);
    auto memberName = boost::fusion::extension::struct_member_name<T, index>::call ();
    if constexpr (boost::fusion::traits::is_sequence<currentType>::value)
      {
        if constexpr (IsOptional<currentType>)
          {
            handleOptional (obj, member, memberName);
          }
        else if constexpr (IsPair<currentType>)
          {
            handlePair (obj, member, memberName);
          }
        else
          {
            obj[memberName] = to_json (member);
          }
      }
    else if constexpr (IsOptional<currentType>)
      {
        handleOptional (obj, member, memberName);
      }
    else if constexpr (IsArray<currentType>)
      {
        using elementType = std::remove_reference_t<decltype (member.front ())>;
        array result;
        for (auto const &element : member)
          {
            object tmp;
            if constexpr (IsOptional<elementType>)
              {
                using optionalType = std::remove_reference_t<decltype (element.value ())>;
                if constexpr (boost::fusion::traits::is_sequence<optionalType>::value)
                  {
                    if (handleOptional (tmp, element, typeNameWithOutNamespace (elementType{})))
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
                        result.emplace_back (element.value ());
                      }
                    else
                      {
                        result.push_back (nullptr);
                      }
                  }
              }
            else if constexpr (IsPair<elementType>)
              {
                handlePair (tmp, element, typeNameWithOutNamespace (elementType{}));
                result.push_back (tmp.at (typeNameWithOutNamespace (elementType{})).as_array ());
              }
            else if constexpr (boost::fusion::traits::is_sequence<elementType>::value)
              {
                tmp[typeNameWithOutNamespace (elementType{})] = to_json (element);
                result.push_back (tmp);
              }
            else
              {
                result.emplace_back (element);
              }
          }
        obj[memberName] = result;
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
