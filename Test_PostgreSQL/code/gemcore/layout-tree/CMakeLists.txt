cmsgemos_add_module(
    layout-tree
    SOURCES
    load.cpp
)
target_link_libraries(gemcore_layout-tree PUBLIC PkgConfig::YAMLCpp)
target_link_libraries(gemcore_layout-tree PRIVATE Boost::filesystem Boost::iostreams)

configure_file(src/constants.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/constants.h)
target_include_directories(gemcore_layout-tree PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src/)

add_executable(test-base-classes test/base-classes.cpp)
target_link_libraries(test-base-classes PRIVATE gemcore_layout-tree)
target_link_libraries(test-base-classes PRIVATE Boost::unit_test_framework)
add_test(NAME "core/layout-tree/test-base-classes"
         COMMAND ./test-base-classes
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

add_executable(test-node-classes test/node-classes.cpp)
target_link_libraries(test-node-classes PRIVATE gemcore_layout-tree)
target_link_libraries(test-node-classes PRIVATE Boost::unit_test_framework)
add_test(NAME "core/layout-tree/test-node-classes"
         COMMAND ./test-node-classes
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
