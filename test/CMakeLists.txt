add_executable(_test
        main.cxx
        jsonToUserDefined.cxx
        userDefinedToJson.cxx
        constant.hxx
        combineToJsonAndToObject.cxx
        )
find_package(Catch2)
target_link_libraries(_test
        confu_json
        Catch2::Catch2
        )
target_include_directories(_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

add_test(NAME _test
        COMMAND _test -r junit)