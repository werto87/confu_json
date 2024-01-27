##
## Copyright (c) 2024 Waldemar Schneider (w-schneider1987 at web dot de)
##
## Distributed under the Boost Software License, Version 1.0.
## (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
##
add_library(confu_json INTERFACE)

install(FILES
        concept.hxx
        confu_json.hxx
        to_json.hxx
        to_object.hxx
        util.hxx
        DESTINATION include/confu_json
        )

find_package(Boost)
find_package(magic_enum)
target_link_libraries(confu_json INTERFACE
        ${PROJECT_WARNINGS}
        ${PROJECT_OPTIONS}
        boost::boost
        magic_enum::magic_enum
        )

# state that anybody linking to us needs to include the current source dir
# to find MathFunctions.h, while we don't.
target_include_directories(confu_json
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        )
install(TARGETS confu_json DESTINATION lib)
