# SEComplexity

cmake_minimum_required(VERSION 3.11)

project(srcComplexity)

enable_testing()
include(CTest)

find_package(LIBXML2 REQUIRED)

add_executable(srcComplexity srcComplexity.cpp srcMLXPathCount.cpp)
target_include_directories(srcComplexity PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcComplexity PRIVATE ${LIBXML2_LIBRARIES})

add_executable(srcMLXPathCount_t srcMLXPathCount_t.cpp srcMLXPathCount.cpp)
target_include_directories(srcMLXPathCount_t PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcMLXPathCount_t PRIVATE ${LIBXML2_LIBRARIES})

add_test(NAME srcMLXPathCount_t COMMAND srcMLXPathCount_t)
