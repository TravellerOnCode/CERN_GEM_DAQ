#cmsgemos_add_module(
#    configdb
#    SOURCES
#    Postgres_Database.cpp
#    VFAT_Config_Table.cpp
#    VFAT_Data_Table.cpp
#    VFAT_Index_Table.cpp
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
    ./interface/postgres_database.h
    ./src/postgres_database.cpp
    ./interface/vfat_config_table.h
    ./src/vfat_config_table.cpp
    ./interface/vfat_data_table.h
    ./src/vfat_data_table.cpp
    ./interface/vfat_index_table.h
    ./src/vfat_index_table.cpp    
)

add_executable(gemdatabase main.cpp)

target_link_libraries(gemdatabase library ${PQXX_LIB} ${PQ_LIB})
add_compile_options(-Wall -lpqxx -lpq)
