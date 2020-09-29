#specify minimum version
cmake_minimum_required(VERSION 2.8)

#sepcifying project name
project(mongo-test-run)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

include(FindPkgConfig)
pkg_check_modules(MongoCXX IMPORTED_TARGET libmongocxx = 3.4)

add_executable(mongo-test write.cpp)
target_link_libraries(mongo-test PkgConfig::MongoCXX)