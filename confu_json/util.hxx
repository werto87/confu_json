//
// Copyright (c) 2021 Waldemar Schneider (w-schneider1987 at web dot de)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6
#define EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6

#include <boost/algorithm/string.hpp>
#include <boost/core/type_name.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/json.hpp>
#include <boost/type_index.hpp>
#include <iostream>
#include <sstream>
#include <string_view>
namespace confu_json
{

template <typename T>
std::string
// use this for something where you want to know the user defined type
// returns the typename without namespace so my_typename::MyType becomes MyType
// for std::string it returns string
// do not use it with std::optional<MyType> use it with 'type_name<typename std::optional<MyType>::value_type>()' this gives you MyType
type_name ()
{
  auto typeWithNamespace = boost::core::type_name<T> ();
  auto splitNames = std::vector<std::string>{};
  boost::algorithm::split (splitNames, typeWithNamespace, boost::is_any_of ("::"));
  if (splitNames.empty ()) return "";
  return splitNames.back ();
}

inline boost::json::value
read_json (std::string const &jsonAsString, boost::system::error_code &ec)
{
  return boost::json::parse (jsonAsString, ec);
}
}
#endif /* EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6 */
