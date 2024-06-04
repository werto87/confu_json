##
## Copyright (c) 2024 Waldemar Schneider (w-schneider1987 at web dot de)
##
## Distributed under the Boost Software License, Version 1.0.
## (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


add_library(confu_json INTERFACE)


add_library(myproject::confu_json ALIAS confu_json)


find_package(di)
find_package(magic_enum)
find_package(Boost)

# Get the include directories for the target.


# Construct the compiler string for the include directories.


target_link_libraries(confu_json INTERFACE
        magic_enum::magic_enum
        boost::boost
        di::di
        )

target_include_directories(confu_json INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(confu_json INTERFACE cxx_std_20)

install(FILES
        concept.hxx
        confu_json.hxx
        to_json.hxx
        to_object.hxx
        util.hxx
        DESTINATION include/confu_json
        )
install(TARGETS confu_json DESTINATION lib)
