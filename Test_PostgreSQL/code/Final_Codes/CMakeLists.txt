cmake_minimum_required(VERSION 3.0)
project(gemdatabase)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_STANDARD 11)

include_directories( CMAKE_CURRENT_SOURCE_DIR)
include_directories("/usr/include/pqxx")

add_executable(gemdatabase main.cpp)

add_library(
    library
    info.h
    Postgres_Database.h
    Postgres_Database.cpp
    VFAT_Config_Table.h
    VFAT_Config_Table.cpp
    VFAT_Data_Table.h
    VFAT_Data_Table.cpp
    VFAT_Index_Table.h
    VFAT_Index_Table.cpp    
)

target_link_libraries(gemdatabase library)

# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

# find_package(nlohmann_json 3.2.0 REQUIRED)



# set(SOURCE_FILES main.cpp sample Item.cpp Item.h)
# add_executable(assingment_5 ${SOURCE_FILES})

# find_package(libmongocxx REQUIRED)
# find_package(libbsoncxx REQUIRED)
# include_directories(${LIBMONGOCXX_INCLUDE_DIR})
# include_directories(${LIBBSONCXX_INCLUDE_DIR})
# include_directories("/usr/include/pqxx")
# include_directories("/usr/local/include/mongocxx/v_noabi")
# include_directories("/usr/local/include/bsoncxx/v_noabi")
# include_directories("/usr/local/include/libmongoc-1.0")
# include_directories("/usr/local/include/libbson-1.0")
# include_directories("/usr/local/lib")

# target_link_libraries(gemdatabase ${LIBMONGOCXX_LIBRARIES})
# target_link_libraries(gemdatabase ${LIBBSONCXX_LIBRARIES})


add_compile_options(-Wall -lpqxx -lpq)