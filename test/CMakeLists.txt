add_executable(_test
        combineToJsonAndToObject.cxx
        main.cxx
        playground.cxx
        )
find_package(Catch2)
find_package(durak)

target_link_libraries(_test
        myproject_options
        myproject_warnings
        confu_json
        Catch2::Catch2WithMain
        durak::durak
        )
target_include_directories(_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

add_test(NAME _test
        COMMAND _test -r junit)