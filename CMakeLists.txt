project(jotta)

cmake_minimum_required (VERSION 2.6)
SET(STD_DEBUG_FLAGS   "-g -std=c++11")
SET(STD_RELEASE_FLAGS "-std=c++11")

# add the executable
include_directories("/usr/include/soci")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${STD_DEBUG_FLAGS}" )
# add the executable
# currently src is header only
SET(JOTTA_SRC_INCLUDE "./src")
INCLUDE_DIRECTORIES(${JOTTA_SRC_INCLUDE})

add_definitions(-DBOOST_TEST_DYN_LINK)
add_executable(JOTTA_UNIT_TEST test/test.cpp)
target_link_libraries(JOTTA_UNIT_TEST boost_unit_test_framework)
target_link_libraries(JOTTA_UNIT_TEST soci_core)
target_link_libraries(JOTTA_UNIT_TEST soci_sqlite3)
