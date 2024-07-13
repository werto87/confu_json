# confu_json
## Helps you with parsing  json to user defined type and vice versa.

## How to:
  Define a boost fusion struct "https://www.boost.org/doc/libs/1_76_0/libs/fusion/doc/html/fusion/adapted/define_struct.html".
  
  Use to_json(object from your type) to create a json with the data from your type.
  
  Use to_object< your type >(json) to create an object from a json.
  
  
## Example:
  ```c++
  #include "confu_json/to_json.hxx"
  #include "confu_json/to_object.hxx"
  #include <boost/fusion/adapted/struct/adapt_struct.hpp>
  #include <boost/json/src.hpp>  // if you use boost json header only this file should be included only in one translation unit

  BOOST_FUSION_DEFINE_STRUCT((shared_class), Nested, (long, answer)) // used to define a struct

  int main() {
    using namespace confu_json;
    auto nested = shared_class::Nested{};
    nested.answer = 42;
    std::cout << to_json(nested) << std::endl; // converts the struct into json and prints it
    auto nestedTest = to_object<shared_class::Nested>(to_json(nested)); // converts the struct into json and back into an object
    assert(nested.answer == nestedTest.answer);
  }  
  ```
  Exampls for defining types: "https://github.com/werto87/confu_json/blob/main/test/constant.hxx"
  
  Exampls for usage: "https://github.com/werto87/confu_json/blob/main/test/combineToJsonAndToObject.cxx"

## This project builds on:
boost::json -> json handling 

boost::mpl and boost::fusion -> template metaprogramming
