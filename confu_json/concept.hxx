//
// Copyright (c) 2021 Waldemar Schneider (w-schneider1987 at web dot de)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef A0BAA2CA_6E62_4337_B0BE_F4AFE5469841
#define A0BAA2CA_6E62_4337_B0BE_F4AFE5469841
#include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/lambda/detail/is_instance_of.hpp>
#include <boost/optional/optional.hpp>
#include <iostream>
#include <optional>
#include <string_view>

namespace confu_json
{

template <typename T> struct is_std_string : std::bool_constant<std::is_same<std::decay_t<T>, std::string>::value>
{
};

template <class T> struct is_std_optional : boost::lambda::is_instance_of_1<T, std::optional>
{
};

template <class T> struct is_boost_optional : boost::lambda::is_instance_of_1<T, boost::optional>
{
};

template <typename T> struct is_std_pair : public std::false_type
{
};

template <typename T>
constexpr bool
is_std_or_boost_optional ()
{
  return is_std_optional<T>::value || is_boost_optional<T>::value;
}
template <typename S, typename T> struct is_std_pair<std::pair<S, T>> : public std::true_type
{
};

template <typename> struct is_std_vector : std::false_type
{
};

template <typename T, typename A> struct is_std_vector<std::vector<T, A>> : std::true_type
{
};

}
#endif /* A0BAA2CA_6E62_4337_B0BE_F4AFE5469841 */
