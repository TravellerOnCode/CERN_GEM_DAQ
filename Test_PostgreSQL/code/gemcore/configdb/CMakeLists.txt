cmake_minimum_required(VERSION 3.0)
project(gemdatabase)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

include_directories(CMAKE_CURRENT_SOURCE_DIR)
# add_subdirectory() 

find_package(Boost)
    IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_library(
    library
    ./interface/info.h
    ./interface/json.hpp
    ./interface/Postgres_Database.h
    ./src/Postgres_Database.cpp
    ./interface/VFAT_Config_Table.h
    ./src/VFAT_Config_Table.cpp
    ./interface/VFAT_Data_Table.h
    ./src/VFAT_Data_Table.cpp
    ./interface/VFAT_Index_Table.h
    ./src/VFAT_Index_Table.cpp    
)

add_executable(gemdatabase main.cpp)

target_link_libraries(gemdatabase library ${PQXX_LIB} ${PQ_LIB})
add_compile_options(-Wall -lpqxx -lpq)
