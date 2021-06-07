#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines-ts")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld -fcoroutines-ts")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fcoroutines -v")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file bin/asset/DejaVuSans.ttf -DCMAKE_EXPORT_COMPILE_COMMANDS=True  -s SOCKET_DEBUG=1 -s USE_PTHREADS  -s ALLOW_MEMORY_GROWTH=1 -fdebug-compilation-dir='../..' -fexceptions -s ASYNCIFY=1  --emit-symbol-map --tracing --bind -g -O0 -std=c++20 -s  -s WASM=1")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -DCMAKE_EXPORT_COMPILE_COMMANDS=True -lwebsocket.js -s SOCKET_DEBUG=1 -s USE_PTHREADS -s ALLOW_MEMORY_GROWTH=1 -fdebug-compilation-dir='../..' -fexceptions  -s ASYNCIFY=1 --emit-symbol-map --bind --tracing -g -O0  -fcoroutines-ts -std=c++20 -s  -s WASM=1" )

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
set(WASM  FALSE)
if(WASM)
set(CONAN_DISABLE_CHECK_COMPILER ON)
endif(WASM)
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
)

  



####### create executable
OPTION(BUILD_TESTS "enable tests" ON)
IF(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test) 
ENDIF(BUILD_TESTS)




####### include what you use
#find_program(iwyu_path NAMES include-what-you-use iwyu)
#set_property(TARGET ${TARGET_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})


#print all variables used in cmake
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
