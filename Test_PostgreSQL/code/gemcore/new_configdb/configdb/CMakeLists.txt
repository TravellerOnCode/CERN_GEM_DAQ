#cmsgemos_add_module(
#    configdb
#    SOURCES
#    Postgres_Database.cpp
#    VFAT_Config_Table.cpp
#    VFAT_settings.cpp
#    VFAT_indexes.cpp
#)
#target_link_libraries(gemcore_configdb PUBLIC pqxx)
#target_link_libraries(gemcore_configdb PUBLIC xDAQ::nlohmann)
#
#add_executable(gemdatabase main.cpp)
#target_link_libraries(gemdatabase PRIVATE gemcore_configdb)



# ------- old cmake --------

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
    ./interface/database_utils.h
    ./src/database_utils.cpp
    ./interface/vfat_configurations.h
    ./src/vfat_configurations.cpp
    ./interface/vfat_settings.h
    ./src/vfat_settings.cpp
    ./interface/vfat_indexes.h
    ./src/vfat_indexes.cpp    
)

add_executable(gemdatabase main.cpp)

target_link_libraries(gemdatabase library ${PQXX_LIB} ${PQ_LIB})
add_compile_options(-Wall -lpqxx -lpq)
