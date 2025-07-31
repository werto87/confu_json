//
// Copyright (c) 2021 Waldemar Schneider (w-schneider1987 at web dot de)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef F5E56D46_F48D_4E89_B6F1_5D734D665E8D
#define F5E56D46_F48D_4E89_B6F1_5D734D665E8D
#include "concept.hxx"
#include "confu_json/to_json.hxx"
#include "util.hxx"
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/back.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/size.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <magic_enum/magic_enum.hpp>
#include <memory>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <vector>
namespace confu_json
{

template <typename T, typename BaseToDerivedMapping = NotDefinedType> T to_object (boost::json::value const &_value);
template <typename BaseToDerivedMapping = NotDefinedType, typename T, typename U> void handleOptional (T &t, U &_value, std::string const &name);
template <typename BaseToDerivedMapping = NotDefinedType, typename T, typename U> void handleUniquePtr (T &t, U &_value, std::string const &name);
template <typename BaseToDerivedMapping = NotDefinedType, typename T, typename U>
void
handleArray (T &t, U &_value)
{
  using namespace boost::json;
  using someTypeOtherType = std::remove_reference_t<decltype (t.front ())>;
  if constexpr (is_std_or_boost_optional<someTypeOtherType> ())
    {
      using optionalType = std::remove_reference_t<decltype (t.front ().value ())>;
      if constexpr (boost::fusion::traits::is_sequence<optionalType>::value)
        {
          for (value const &element : _value.as_array ())
            {
              if (not element.is_null ())
                {
                  auto temp = someTypeOtherType{};
                  handleOptional<BaseToDerivedMapping> (temp, element, std::string{ type_name<someTypeOtherType> () });
                  t.push_back (temp);
                }
              else
                {
                  t.push_back (someTypeOtherType{});
                }
            }
        }
      else
        {
          for (value const &element : _value.as_array ())
            {
              if (not element.is_null ())
                {
                  if constexpr (std::is_same<bool, optionalType>::value)
                    {
                      t.push_back (element.as_bool ());
                    }
                  else if constexpr (std::is_signed<optionalType>::value)
                    {
                      t.push_back (boost::numeric_cast<optionalType> (element.as_int64 ()));
                    }
                  else if constexpr (std::is_unsigned<optionalType>::value)
                    {
                      t.push_back (element.as_uint64 ());
                    }
                  else if constexpr (is_std_string<optionalType>::value)
                    {
                      if (element.kind () == kind::string) t.push_back (std::string{ element.as_string ().c_str () });
                      else
                        {
                          t.push_back (std::string{});
                        }
                    }
                  else if constexpr (std::is_enum_v<optionalType>)
                    {
                      auto result = std::string{ type_name<optionalType> () };
                      auto enumOptional = magic_enum::enum_cast<optionalType> (element.as_object ().at (result).as_string ().c_str ());
                      if (enumOptional)
                        {
                          t.push_back (enumOptional.value ());
                        }
                      else
                        {
                          std::cout << type_name<optionalType> () << ": not supported enum value: " << _value.as_string ().c_str () << std::endl;
                        }
                    }
                }
              else
                {
                  t.push_back (someTypeOtherType{});
                }
            }
        }
    }
  else if constexpr (is_unique_ptr<someTypeOtherType> ())
    {
      using uniquePtrType = std::remove_reference_t<decltype (*t.front ().get ())>;
      if constexpr (boost::fusion::traits::is_sequence<uniquePtrType>::value)
        {
          for (value const &element : _value.as_array ())
            {
              if (not element.is_null ())
                {
                  auto temp = someTypeOtherType{};
                  handleUniquePtr<BaseToDerivedMapping> (temp, element, std::string{ type_name<someTypeOtherType> () });
                  t.push_back (std::move (temp));
                }
              else
                {
                  t.push_back (nullptr);
                }
            }
        }
      else
        {
          for (value const &element : _value.as_array ())
            {
              if (not element.is_null ())
                {
                  if constexpr (std::is_same<bool, uniquePtrType>::value)
                    {
                      t.push_back (element.as_bool ());
                    }
                  else if constexpr (std::is_signed<uniquePtrType>::value)
                    {
                      t.push_back (boost::numeric_cast<uniquePtrType> (element.as_int64 ()));
                    }
                  else if constexpr (std::is_unsigned<uniquePtrType>::value)
                    {
                      t.push_back (element.as_uint64 ());
                    }
                  else if constexpr (is_std_string<uniquePtrType>::value)
                    {
                      if (element.kind () == kind::string) t.push_back (std::string{ element.as_string ().c_str () });
                      else
                        {
                          t.push_back (std::string{});
                        }
                    }
                  else if constexpr (std::is_enum_v<uniquePtrType>)
                    {
                      auto result = std::string{ type_name<uniquePtrType> () };
                      auto enumOptional = magic_enum::enum_cast<uniquePtrType> (element.as_object ().at (result).as_string ().c_str ());
                      if (enumOptional)
                        {
                          t.push_back (enumOptional.value ());
                        }
                      else
                        {
                          std::cout << type_name<uniquePtrType> () << ": not supported enum value: " << _value.as_string ().c_str () << std::endl;
                        }
                    }
                }
              else
                {
                  t.push_back (someTypeOtherType{});
                }
            }
        }
    }
  else if constexpr (is_std_pair<someTypeOtherType>::value)
    {
      for (auto &element : _value.as_array ())
        {
          auto result = someTypeOtherType{};
          using firstType = std::remove_reference_t<decltype (result.first)>;
          using secondType = std::remove_reference_t<decltype (result.second)>;
          if constexpr (is_std_or_boost_optional<firstType> ())
            {
              if (not element.at (0).is_null ())
                {
                  handleOptional<BaseToDerivedMapping> (result.first, element.at (0), std::string{ type_name<firstType> () });
                }
            }
          else
            {
              if constexpr (std::is_enum_v<firstType>)
                {
                  auto typeName = std::string{ type_name<firstType> () };
                  auto enumOptional = magic_enum::enum_cast<firstType> (element.at (0).at (typeName).as_string ().c_str ());
                  if (enumOptional)
                    {
                      result.first = enumOptional.value ();
                    }
                  else
                    {
                      std::cout << type_name<firstType> () << ": not supported enum value: " << element.as_string ().c_str () << std::endl;
                    }
                }
              else if constexpr (std::is_same<bool, firstType>::value)
                {
                  result.first = element.at (0).as_bool ();
                }
              else if constexpr (std::is_signed<firstType>::value || std::is_unsigned<firstType>::value)
                {
                  result.first = element.at (0).as_int64 ();
                }
              else if constexpr (is_std_string<firstType>::value)
                {
                  if (element.at (0).kind () == kind::string) result.first = element.at (0).as_string ().c_str ();
                }
              else
                {
                  result.first = to_object<firstType, BaseToDerivedMapping> (element.at (0).at (type_name<firstType> ()));
                }
            }
          if constexpr (is_std_or_boost_optional<secondType> ())
            {
              if (not element.at (1).is_null ())
                {
                  handleOptional<BaseToDerivedMapping> (result.second, element.at (1), std::string{ type_name<secondType> () });
                }
            }
          else
            {
              if constexpr (std::is_enum_v<secondType>)
                {
                  auto typeName = std::string{ type_name<secondType> () };
                  auto enumOptional = magic_enum::enum_cast<secondType> (element.at (1).at (typeName).as_string ().c_str ());
                  if (enumOptional)
                    {
                      result.second = enumOptional.value ();
                    }
                  else
                    {
                      std::cout << type_name<secondType> () << ": not supported enum value: " << element.as_string ().c_str () << std::endl;
                    }
                }
              else if constexpr (std::is_same<bool, secondType>::value)
                {
                  result.second = element.at (1).as_bool ();
                }
              else if constexpr (std::is_signed<secondType>::value || std::is_unsigned<secondType>::value)
                {
                  result.second = element.at (1).as_int64 ();
                }
              else if constexpr (is_std_string<secondType>::value)
                {
                  if (element.at (1).kind () == kind::string) result.second = element.at (1).as_string ().c_str ();
                }
              else
                {
                  result.second = to_object<secondType, BaseToDerivedMapping> (element.at (1).at (type_name<secondType> ()));
                }
            }
          t.push_back (result);
        }
    }
  else if constexpr (is_std_vector<someTypeOtherType>::value)
    {
      for (value const &element : _value.as_array ())
        {
          auto tmp = someTypeOtherType{};
          handleArray<BaseToDerivedMapping> (tmp, element);
          t.push_back (tmp);
        }
    }
  else
    {
      if constexpr (boost::fusion::traits::is_sequence<someTypeOtherType>::value)
        {
          for (value const &element : _value.as_array ())
            {
              t.push_back (to_object<someTypeOtherType, BaseToDerivedMapping> (element.as_object ().at (type_name<someTypeOtherType> ())));
            }
        }
      else if constexpr (std::is_enum_v<someTypeOtherType>)
        {
          for (value const &element : _value.as_array ())
            {
              auto result = std::string{ type_name<someTypeOtherType> () };
              auto enumOptional = magic_enum::enum_cast<someTypeOtherType> (element.as_object ().at (result).as_string ().c_str ());
              if (enumOptional)
                {
                  t.push_back (enumOptional.value ());
                }
              else
                {
                  std::cout << type_name<someTypeOtherType> () << ": not supported enum value: " << _value.as_string ().c_str () << std::endl;
                }
            }
        }
      else
        {
          t = value_to<T> (_value);
        }
    }
}

template <typename BaseToDerivedMapping, typename T, typename U>
void
handleOptional (T &t, U &_value, std::string const &name)
{
  using namespace boost::json;
  auto &jsonDataForMember = _value.as_object ().at (name);
  using optionalType = typename std::decay<decltype (t.value ())>::type;
  if constexpr (std::is_same<bool, optionalType>::value)
    {
      t = jsonDataForMember.as_bool ();
    }
  else if constexpr (std::is_signed<optionalType>::value)
    {
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#endif
      t = jsonDataForMember.as_int64 ();
#ifdef _MSC_VER
#pragma warning(pop)
#endif
    }
  else if constexpr (std::is_unsigned<optionalType>::value)
    {
      t = jsonDataForMember.as_uint64 ();
    }
  else if constexpr (is_std_or_boost_optional<optionalType> ())
    {
      if (not jsonDataForMember.is_null ())
        {
          handleOptional<BaseToDerivedMapping> (t, jsonDataForMember, name);
        }
    }
  else if constexpr (is_std_string<optionalType>::value && not is_std_vector<optionalType>::value)
    {
      if (jsonDataForMember.kind () == kind::string) t = jsonDataForMember.as_string ().c_str ();
    }
  else if constexpr (std::is_enum_v<optionalType>)
    {
      if (jsonDataForMember.kind () == kind::string)
        {
          auto result = std::string{ jsonDataForMember.as_string ().c_str () };
          auto enumOptional = magic_enum::enum_cast<optionalType> (result);
          if (enumOptional)
            {
              t = enumOptional.value ();
            }
          else
            {
              std::cout << std::string{ type_name<optionalType> () } << ": not supported enum value: " << jsonDataForMember.as_string ().c_str () << std::endl;
            }
        }
    }
  else if constexpr (boost::fusion::traits::is_sequence<optionalType>::value)
    {
      t = to_object<optionalType, BaseToDerivedMapping> (jsonDataForMember.as_object ());
    }
  else if constexpr (is_std_vector<optionalType>::value)
    {
      auto tmp = optionalType{};
      handleArray<BaseToDerivedMapping> (tmp, jsonDataForMember);
      t = tmp;
    }
}

template <typename BaseToDerivedMapping, typename T, typename U>
void
handleUniquePtr (T &t, U &_value, std::string const &name)
{
  using namespace boost::json;
  auto &jsonDataForMember = _value.as_object ().at (name);
  using uniquePtrType = typename std::decay<decltype (*t.get ())>::type;
  if constexpr (std::is_same<bool, uniquePtrType>::value)
    {
      t = jsonDataForMember.as_bool ();
    }
  else if constexpr (std::is_signed<uniquePtrType>::value)
    {
      t = jsonDataForMember.as_int64 ();
    }
  else if constexpr (std::is_unsigned<uniquePtrType>::value)
    {
      t = jsonDataForMember.as_uint64 ();
    }
  else if constexpr (is_std_or_boost_optional<uniquePtrType> ())
    {
      if (not jsonDataForMember.is_null ())
        {
          if (not jsonDataForMember.as_object ().at ("optional").is_null ())
            {
              auto optionalTmp = uniquePtrType{};
              handleOptional<BaseToDerivedMapping> (optionalTmp, jsonDataForMember, "optional");
              t = std::make_unique<uniquePtrType> (optionalTmp);
            }
          else
            {
              t = std::make_unique<uniquePtrType> (std::nullopt);
            }
        }
    }
  else if constexpr (is_unique_ptr<uniquePtrType> ())
    {
      if (not jsonDataForMember.is_null ())
        {
          handleUniquePtr<BaseToDerivedMapping> (t, jsonDataForMember, name);
        }
    }
  else if constexpr (is_std_string<uniquePtrType>::value && not is_std_vector<uniquePtrType>::value)
    {
      if (jsonDataForMember.kind () == kind::string) t = jsonDataForMember.as_string ().c_str ();
    }
  else if constexpr (std::is_enum_v<uniquePtrType>)
    {
      if (jsonDataForMember.kind () == kind::string)
        {
          auto result = std::string{ jsonDataForMember.as_string ().c_str () };
          auto enumOptional = magic_enum::enum_cast<uniquePtrType> (result);
          if (enumOptional)
            {
              t = std::make_unique<uniquePtrType> (enumOptional.value ());
            }
          else
            {
              std::cout << std::string{ type_name<uniquePtrType> () } << ": not supported enum value: " << jsonDataForMember.as_string ().c_str () << std::endl;
            }
        }
    }
  else if constexpr (boost::fusion::traits::is_sequence<uniquePtrType>::value)
    {
      if constexpr (std::is_same_v<BaseToDerivedMapping, NotDefinedType>)
        {
          t = std::make_unique<uniquePtrType> (to_object<uniquePtrType, BaseToDerivedMapping> (jsonDataForMember.as_object ()));
        }
      else
        {
          if constexpr (boost::mpl::has_key<BaseToDerivedMapping, uniquePtrType>::value)
            {
              using Derived = boost::mpl::at<BaseToDerivedMapping, uniquePtrType>::type;
              t = std::make_unique<Derived> (to_object<Derived, BaseToDerivedMapping> (jsonDataForMember.as_object ()));
            }
          else
            {
              t = std::make_unique<uniquePtrType> (to_object<uniquePtrType, BaseToDerivedMapping> (jsonDataForMember.as_object ()));
            }
        }
    }
  else if constexpr (is_std_vector<uniquePtrType>::value)
    {
      auto tmp = uniquePtrType{};
      handleArray<BaseToDerivedMapping> (tmp, jsonDataForMember);
      t = std::make_unique<uniquePtrType> (tmp);
    }
}

/**
 * @brief creates the Type T from a json object
 *
 * @tparam T type to create
 * @tparam BaseToDerivedMapping optional template argument (function is forward declared) used to inject an implementation for example for std::unique_ptr<Base>
 * @param _value
 * @return T
 */
template <typename T, typename BaseToDerivedMapping>
T
to_object (boost::json::value const &_value)
{
  using namespace boost::json;
  T t{};
  boost::fusion::for_each (boost::mpl::range_c<unsigned, 0, boost::fusion::result_of::size<T>::value> (), [&] (auto index) {
    using currentType = std::remove_reference_t<decltype (boost::fusion::at_c<index> (t))>;
    auto &member = boost::fusion::at_c<index> (t);
    auto memberName = boost::fusion::extension::struct_member_name<T, index>::call ();
    auto &jsonDataForMember = _value.as_object ().at (memberName);
    if constexpr (std::is_same<bool, currentType>::value)
      {
        member = jsonDataForMember.as_bool ();
      }
    else if constexpr (std::is_signed<currentType>::value || std::is_unsigned<currentType>::value)
      {
        member = jsonDataForMember.template to_number<currentType> ();
      }
    else if constexpr (is_std_string<currentType>::value)
      {
        if (jsonDataForMember.kind () == kind::string) member = jsonDataForMember.as_string ().c_str ();
      }
    else if constexpr (is_std_or_boost_optional<currentType> ())
      {
        if (not jsonDataForMember.is_null ())
          {
            handleOptional<BaseToDerivedMapping> (member, _value, memberName);
          }
      }
    else if constexpr (is_unique_ptr<currentType>::value)
      {
        if (not jsonDataForMember.is_null ())
          {
            handleUniquePtr<BaseToDerivedMapping> (member, _value, memberName);
          }
      }
    else
      {
        if constexpr (is_std_vector<currentType>::value)
          {
            handleArray<BaseToDerivedMapping> (member, jsonDataForMember);
          }
        else if constexpr (is_std_pair<currentType>::value)
          {
            using firstType = std::remove_reference_t<decltype (member.first)>;
            using secondType = std::remove_reference_t<decltype (member.second)>;
            if constexpr (is_std_or_boost_optional<firstType> ())
              {
                if (not jsonDataForMember.at (0).is_null ())
                  {
                    handleOptional<BaseToDerivedMapping> (member.first, jsonDataForMember.at (0), std::string{ type_name<firstType> () });
                  }
              }
            else if constexpr (is_unique_ptr<firstType> ())
              {
                if (not jsonDataForMember.at (0).is_null ())
                  {
                    handleUniquePtr<BaseToDerivedMapping> (member.first, jsonDataForMember.at (0), std::string{ type_name<firstType> () });
                  }
              }
            else if constexpr (std::is_enum_v<firstType>)
              {
                auto result = std::string{ type_name<firstType> () };
                auto enumOptional = magic_enum::enum_cast<firstType> (jsonDataForMember.at (0).at (result).as_string ().c_str ());
                if (enumOptional)
                  {
                    member.first = enumOptional.value ();
                  }
                else
                  {
                    std::cout << type_name<firstType> () << ": not supported enum value: " << jsonDataForMember.as_string ().c_str () << std::endl;
                  }
              }
            else if constexpr (std::is_same<bool, firstType>::value)
              {
                member.first = jsonDataForMember.at (0).as_bool ();
              }
            else if constexpr (std::is_signed<firstType>::value || std::is_unsigned<firstType>::value)
              {
                member.first = jsonDataForMember.at (0).template to_number<firstType> ();
              }
            else if constexpr (is_std_string<firstType>::value)
              {
                if (jsonDataForMember.at (0).kind () == kind::string) member.first = jsonDataForMember.at (0).as_string ().c_str ();
              }
            else
              {
                member.first = to_object<firstType, BaseToDerivedMapping> (jsonDataForMember.at (0).at (type_name<firstType> ()));
              }
            if constexpr (is_std_or_boost_optional<secondType> ())
              {
                if (not jsonDataForMember.at (1).is_null ())
                  {
                    handleOptional<BaseToDerivedMapping> (member.second, jsonDataForMember.at (1), std::string{ type_name<secondType> () });
                  }
              }
            else if constexpr (is_unique_ptr<secondType> ())
              {
                if (not jsonDataForMember.at (1).is_null ())
                  {
                    handleUniquePtr<BaseToDerivedMapping> (member.second, jsonDataForMember.at (1), std::string{ type_name<secondType> () });
                  }
              }
            else if constexpr (std::is_enum_v<secondType>)
              {
                auto result = std::string{ type_name<secondType> () };
                auto enumOptional = magic_enum::enum_cast<secondType> (jsonDataForMember.at (1).at (result).as_string ().c_str ());
                if (enumOptional)
                  {
                    member.second = enumOptional.value ();
                  }
                else
                  {
                    std::cout << type_name<secondType> () << ": not supported enum value: " << jsonDataForMember.as_string ().c_str () << std::endl;
                  }
              }
            else if constexpr (std::is_same<bool, secondType>::value)
              {
                member.second = jsonDataForMember.at (1).as_bool ();
              }
            else if constexpr (std::is_signed<secondType>::value || std::is_unsigned<secondType>::value)
              {
                member.second = jsonDataForMember.at (1).template to_number<secondType> ();
              }
            else if constexpr (is_std_string<secondType>::value)
              {
                if (jsonDataForMember.at (1).kind () == kind::string) member.second = jsonDataForMember.at (1).as_string ().c_str ();
              }
            else
              {
                member.second = to_object<secondType, BaseToDerivedMapping> (jsonDataForMember.at (1).at (type_name<secondType> ()));
              }
          }
        else if constexpr (std::is_enum_v<currentType>)
          {
            auto result = std::string{ jsonDataForMember.as_string ().c_str () };
            auto enumOptional = magic_enum::enum_cast<currentType> (result);
            if (enumOptional)
              {
                member = enumOptional.value ();
              }
            else
              {
                std::cout << type_name<currentType> () << ": not supported enum value: " << jsonDataForMember.as_string ().c_str () << std::endl;
              }
          }
        else
          {
            member = to_object<currentType, BaseToDerivedMapping> (jsonDataForMember.as_object ());
          }
      }
  });
  return t;
}
}
#endif /* F5E56D46_F48D_4E89_B6F1_5D734D665E8D */
