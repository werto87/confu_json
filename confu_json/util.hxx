#ifndef EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6
#define EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6

#include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string_view>

// template <typename T>
// std::string
// // only use this if your type is a simple user defined type with not template class something like namespace::MyType and you want to get MyType
// // does not work with templated types or something like std::string which is std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > and the result will be allocator<char> >
// typeNameWithOutNamespace (T const &)
// {
//   auto fullName = std::vector<std::string>{};
//   auto typeWithNamespace = boost::typeindex::type_id<T> ().pretty_name ();
//   boost::algorithm::split (fullName, typeWithNamespace, boost::is_any_of ("::"));
//   boost::erase_all (fullName.back (), ">");
//   return fullName.back ();
// }

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

#endif /* EFBB6F2B_7B2E_4BD2_AF22_95E2E7BEDBD6 */
