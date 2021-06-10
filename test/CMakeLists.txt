set(TEST_TARGET_NAME _test)
if(TARGET_SOURCES-NOTFOUND STREQUAL TARGET_SOURCES)
  unset(TARGET_SOURCES)
endif()
add_executable(${TEST_TARGET_NAME} 
main.cxx
jsonToUserDefined.cxx
userDefinedToJson.cxx
constant.hxx
combineToJsonAndToObject.cxx
${TARGET_SOURCES}
 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g")

 if (CMAKE_BINARY_DIR)
 target_compile_definitions(${TEST_TARGET_NAME} PRIVATE PATH_TO_BINARY="${CMAKE_BINARY_DIR}")
 endif()
target_link_libraries(${TEST_TARGET_NAME}
${PROJECT_WARNINGS}
${PROJECT_OPTIONS}
${TARGET_NAME}
 CONAN_PKG::catch2
 CONAN_PKG::boost
${TARGET_LIBS}
)
target_include_directories(${TEST_TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR})

add_test(NAME ${TEST_TARGET_NAME}
         COMMAND ${TEST_TARGET_NAME} -r junit) 

         