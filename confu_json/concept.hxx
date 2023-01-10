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
#include <iostream>
#include <string_view>
namespace confu_json
{

template <typename T> concept IsPrintable = requires(T t) { std::cout << t; };

template <typename T> concept IsOptional = requires(T t) { t.has_value (); };

template <typename T> concept IsPair = requires(T t) { t.second; };

template <class, template <class...> class> constexpr bool is_specialization = false;

template <template <class...> class T, class... Args> inline constexpr bool is_specialization<T<Args...>, T> = true;

template <class T> concept isVector = is_specialization<T, std::vector>;

}
#endif /* A0BAA2CA_6E62_4337_B0BE_F4AFE5469841 */
