//
// Copyright (c) 2021 Waldemar Schneider (w-schneider1987 at web dot de)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6
#define EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6

#include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string_view>

namespace confu_json
{

template <typename T>
auto
type_name ()
{
#ifdef _MSC_VER
  name = __FUNCSIG__;
  auto fullName = std::vector<std::string>{};
  boost::algorithm::split (fullName, name, boost::is_any_of ("::"));
  boost::erase_all (fullName.back (), ">(void)");
#else
  std::string_view name = __PRETTY_FUNCTION__;
  auto fullName = std::vector<std::string>{};
  boost::algorithm::split (fullName, name, boost::is_any_of ("::"));
  boost::erase_all (fullName.back (), "]");
  boost::erase_all (fullName.back (), ">");
#endif

  return fullName.back ();
}

inline boost::json::value
read_json (std::stringstream &is, boost::json::error_code &ec)
{
  // TODO think about unsigned support how to save a number in a json so we can say its an unsigned for example we have 2 in a json is this unsigned or not?
  boost::json::stream_parser p;
  std::string line;
  while (std::getline (is, line))
    {
      p.write (line, ec);
      if (ec) return nullptr;
    }
  p.finish (ec);
  if (ec) return nullptr;
  return p.release ();
}

inline boost::json::value
read_json (std::string const &jsonAsString, boost::json::error_code &ec)
{
  std::stringstream is{};
  is << jsonAsString;
  return read_json (is, ec);
}

}
#endif /* EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6 */
