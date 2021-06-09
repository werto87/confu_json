#ifndef F5E56D46_F48D_4E89_B6F1_5D734D665E8D
#define F5E56D46_F48D_4E89_B6F1_5D734D665E8D
#include "confu_json/concept.hxx"
#include "confu_json/util.hxx"
#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/fusion/include/algorithm.hpp>
#include <boost/mpl/range_c.hpp>
#include <magic_enum.hpp>
namespace confu_json
{

template <typename T> T to_object (boost::json::value const &_value); // pre declare

template <typename T, typename U>
void
handleOptional (T &t, U &_value, std::string const &name)
{
  using namespace boost::json;
  auto &jsonDataForMember = _value.as_object ().at (name);

  using optionalType = std::remove_reference_t<decltype (t.value ())>;
  if constexpr (std::is_same<bool, optionalType>::value)
    {
      t = jsonDataForMember.as_bool ();
    }
  else if constexpr (std::is_signed<optionalType>::value)
    {
      t = jsonDataForMember.as_int64 ();
    }
  else if constexpr (std::is_unsigned<optionalType>::value)
    {
      t = jsonDataForMember.as_uint64 ();
    }
  else if constexpr (IsOptional<optionalType>)
    {
      if (not jsonDataForMember.is_null ())
        {
          handleOptional (t, jsonDataForMember, name);
        }
    }
  else if constexpr (printable<optionalType>)
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
      t = to_object<optionalType> (jsonDataForMember.as_object ());
    }
}

template <typename T>
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
    else if constexpr (std::is_signed<currentType>::value)
      {
        member = jsonDataForMember.as_int64 ();
      }
    else if constexpr (std::is_unsigned<currentType>::value)
      {
        member = jsonDataForMember.as_uint64 ();
      }
    else if constexpr (IsOptional<currentType>)
      {
        if (not jsonDataForMember.is_null ())
          {
            handleOptional (member, _value, memberName);
          }
      }
    else if constexpr (printable<currentType>)
      {
        if (jsonDataForMember.kind () == kind::string) member = jsonDataForMember.as_string ().c_str ();
      }
    else
      {
        if constexpr (IsArray<currentType>)
          {
            using someTypeOtherType = std::remove_reference_t<decltype (member.front ())>;
            if constexpr (IsOptional<someTypeOtherType>)
              {
                using optionalType = std::remove_reference_t<decltype (member.front ().value ())>;
                if constexpr (boost::fusion::traits::is_sequence<optionalType>::value)
                  {
                    for (value const &element : jsonDataForMember.as_array ())
                      {
                        if (not element.is_null ())
                          {
                            auto temp = someTypeOtherType{};
                            handleOptional (temp, element, std::string{ type_name<someTypeOtherType> () });
                            member.push_back (temp);
                          }
                        else
                          {
                            member.push_back (someTypeOtherType{});
                          }
                      }
                  }
                else
                  {
                    for (value const &element : jsonDataForMember.as_array ())
                      {
                        if (not element.is_null ())
                          {
                            if constexpr (std::is_same<bool, optionalType>::value)
                              {
                                member.push_back (element.as_bool ());
                              }
                            else if constexpr (std::is_signed<optionalType>::value)
                              {
                                member.push_back (element.as_int64 ());
                              }
                            else if constexpr (std::is_unsigned<optionalType>::value)
                              {
                                member.push_back (element.as_uint64 ());
                              }
                            else if constexpr (printable<optionalType>)
                              {
                                if (element.kind () == kind::string) member.push_back (std::string{ element.as_string ().c_str () });
                                else
                                  {
                                    member.push_back (std::string{});
                                  }
                              }
                            else if constexpr (std::is_enum_v<optionalType>)
                              {

                                auto result = std::string{ type_name<optionalType> () };
                                auto enumOptional = magic_enum::enum_cast<optionalType> (element.as_object ().at (result).as_string ().c_str ());
                                if (enumOptional)
                                  {
                                    member.push_back (enumOptional.value ());
                                  }
                                else
                                  {
                                    std::cout << type_name<optionalType> () << ": not supported enum value: " << jsonDataForMember.as_string ().c_str () << std::endl;
                                  }
                              }
                          }
                        else
                          {
                            member.push_back (someTypeOtherType{});
                          }
                      }
                  }
              }
            else if constexpr (IsPair<someTypeOtherType>)
              {
                for (auto &element : jsonDataForMember.as_array ())
                  {
                    auto result = someTypeOtherType{};
                    using firstType = std::remove_reference_t<decltype (result.first)>;
                    using secondType = std::remove_reference_t<decltype (result.second)>;
                    if constexpr (IsOptional<firstType>)
                      {
                        if (not element.at (0).is_null ())
                          {
                            handleOptional (result.first, element.at (0), std::string{ type_name<firstType> () });
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
                        else
                          {
                            result.first = to_object<firstType> (element.at (0).at (type_name<firstType> ()));
                          }
                      }

                    if constexpr (IsOptional<secondType>)
                      {
                        if (not element.at (1).is_null ())
                          {
                            handleOptional (result.second, element.at (1), std::string{ type_name<secondType> () });
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
                        else
                          {
                            result.second = to_object<secondType> (element.at (1).at (type_name<secondType> ()));
                          }
                      }
                    member.push_back (result);
                  }
              }
            else
              {
                if constexpr (boost::fusion::traits::is_sequence<someTypeOtherType>::value)
                  {
                    for (value const &element : jsonDataForMember.as_array ())
                      {
                        member.push_back (to_object<someTypeOtherType> (element.as_object ().at (type_name<someTypeOtherType> ())));
                      }
                  }
                else if constexpr (std::is_enum_v<someTypeOtherType>)
                  {
                    for (value const &element : jsonDataForMember.as_array ())
                      {
                        auto result = std::string{ type_name<someTypeOtherType> () };
                        auto enumOptional = magic_enum::enum_cast<someTypeOtherType> (element.as_object ().at (result).as_string ().c_str ());
                        if (enumOptional)
                          {
                            member.push_back (enumOptional.value ());
                          }
                        else
                          {
                            std::cout << type_name<someTypeOtherType> () << ": not supported enum value: " << jsonDataForMember.as_string ().c_str () << std::endl;
                          }
                      }
                  }
                else
                  {
                    member = value_to<currentType> (jsonDataForMember);
                  }
              }
          }
        else if constexpr (IsPair<currentType>)
          {
            // TODO how does int work???
            using firstType = std::remove_reference_t<decltype (member.first)>;
            using secondType = std::remove_reference_t<decltype (member.second)>;

            if constexpr (IsOptional<firstType>)
              {
                if (not jsonDataForMember.at (0).is_null ())
                  {
                    handleOptional (member.first, jsonDataForMember.at (0), std::string{ type_name<firstType> () });
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
            else
              {
                member.first = to_object<firstType> (jsonDataForMember.at (0).at (type_name<firstType> ()));
              }

            if constexpr (IsOptional<secondType>)
              {
                if (not jsonDataForMember.at (1).is_null ())
                  {
                    handleOptional (member.second, jsonDataForMember.at (1), std::string{ type_name<secondType> () });
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
            else
              {
                member.second = to_object<secondType> (jsonDataForMember.at (1).at (type_name<secondType> ()));
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
            member = to_object<currentType> (jsonDataForMember.as_object ());
          }
      }
  });
  return t;
}
}
#endif /* F5E56D46_F48D_4E89_B6F1_5D734D665E8D */
