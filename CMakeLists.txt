# SEComplexity

cmake_minimum_required(VERSION 3.14)

project(srcComplexity)

# require C++11
set(CMAKE_CXX_STANDARD 11)

# libxml2
find_package(LIBXML2 REQUIRED)

# srcComplexity program
add_executable(srcComplexity srcComplexity.cpp srcMLXPathCount.cpp)
target_include_directories(srcComplexity PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcComplexity PRIVATE ${LIBXML2_LIBRARIES})

# srcMLXPathCount test program
add_executable(srcMLXPathCount_t srcMLXPathCount_t.cpp srcMLXPathCount.cpp)
target_include_directories(srcMLXPathCount_t PRIVATE ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcMLXPathCount_t PRIVATE ${LIBXML2_LIBRARIES})

add_test(NAME srcMLXPathCount_t COMMAND srcMLXPathCount_t)

# run command on example file
add_custom_target(run COMMENT "Run srcComplexity on example"
                      COMMAND ./srcComplexity ${CMAKE_CURRENT_SOURCE_DIR}/srcMLXPathCount.cpp.xml
                      DEPENDS srcComplexity)
