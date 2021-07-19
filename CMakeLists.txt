cmake_minimum_required(VERSION 3.17)
project(project VERSION 1.0.0
  DESCRIPTION project
  LANGUAGES CXX
  ) 
cmake_policy(SET CMP0015 NEW)




########## enable cache system
include(cmake/Cache.cmake)

########## link against the libs to apply the configurations to the target
# compiler warnings
set(PROJECT_WARNINGS project_warning)
add_library(${PROJECT_WARNINGS} INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJECT_WARNINGS})
# compiler options
set(PROJECT_OPTIONS project_options)


add_library(${PROJECT_OPTIONS} INTERFACE)

target_compile_features(${PROJECT_OPTIONS} INTERFACE cxx_std_20)
# target_precompile_headers(${PROJECT_OPTIONS} INTERFACE 
# )


# include(cmake/Sanitizers.cmake)
# enable_sanitizers(${PROJECT_OPTIONS})

# allow for static analysis options
#include(cmake/StaticAnalyzers.cmake) 
 
######## conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)


set(TARGET_NAME confu_json)
add_library(${TARGET_NAME} INTERFACE)

######## add sub dir
add_subdirectory(confu_json) 


####### link
target_link_libraries(${TARGET_NAME} INTERFACE
  ${PROJECT_WARNINGS}
  ${PROJECT_OPTIONS}
    CONAN_PKG::boost
    CONAN_PKG::magic_enum
)

####### create executable
OPTION(BUILD_TESTS "enable tests" ON)
IF(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test) 
ENDIF(BUILD_TESTS)
