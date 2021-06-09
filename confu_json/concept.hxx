#ifndef A0BAA2CA_6E62_4337_B0BE_F4AFE5469841
#define A0BAA2CA_6E62_4337_B0BE_F4AFE5469841
#include <boost/algorithm/string.hpp>
#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string_view>
namespace confu_json
{

template <typename T> concept printable = requires(T t) { std::cout << t; };

template <typename T> concept IsOptional = requires(T t) { t.has_value (); };

template <typename T> concept IsPair = requires(T t) { t.second; };

template <typename T> concept IsArray = requires(T t) { t.size (); };

template <typename T> using is_adapted_struct = std::is_same<typename boost::fusion::traits::tag_of<T>::type, boost::fusion::struct_tag>;

template <typename T> concept IsFusionStruct = requires(T t) { T::self_type; };

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

template <typename T>
std::string
// only use this if your type is a simple user defined type with not template class something like namespace::MyType and you want to get MyType
// does not work with templated types or something like std::string which is std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > and the result will be allocator<char> >
typeNameWithOutNamespace (T const &)
{
  auto fullName = std::vector<std::string>{};
  auto typeWithNamespace = boost::typeindex::type_id<T> ().pretty_name ();
  boost::algorithm::split (fullName, typeWithNamespace, boost::is_any_of ("::"));
  boost::erase_all (fullName.back (), ">");
  return fullName.back ();
}

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
}
#endif /* A0BAA2CA_6E62_4337_B0BE_F4AFE5469841 */
