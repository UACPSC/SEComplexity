# Build for srcComplexity

cmake_minimum_required(VERSION 3.14.0)

project(srcComplexity)

find_package(LibXml2 REQUIRED)
message("-- libxml2 include: " ${LIBXML2_INCLUDE_DIR})
message("-- libxml2 library: " ${LIBXML2_LIBRARY})

# Build srcComplexity
add_executable(srcComplexity srcComplexity.cpp)
target_link_libraries(srcComplexity PUBLIC srcmlxpath_shared)

# Static srcmlxpath library
add_library(srcmlxpath STATIC srcMLXPathCount.cpp)
target_include_directories(srcmlxpath PUBLIC ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcmlxpath PUBLIC ${LIBXML2_LIBRARY})

# Shared srcmlxpath library
add_library(srcmlxpath_shared SHARED srcMLXPathCount.cpp)
target_include_directories(srcmlxpath_shared PUBLIC ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcmlxpath_shared PUBLIC ${LIBXML2_LIBRARY})
set_target_properties(srcmlxpath_shared PROPERTIES OUTPUT_NAME srcmlxpath)

# run example
set(SRCCOMPLEXITY_TESTFILE srcMLXPathCount.cpp.xml)
configure_file(${SRCCOMPLEXITY_TESTFILE} ${SRCCOMPLEXITY_TESTFILE} COPYONLY)
add_custom_target(run DEPENDS srcComplexity
                      COMMAND ./srcComplexity ${SRCCOMPLEXITY_TESTFILE})

# Setup testing
enable_testing()

# all .cpp files in test/ are independent test programs
file(GLOB TEST_SOURCES test/*.cpp)
foreach(TESTFILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TESTFILE} NAME_WLE)
    add_executable(${TEST_NAME} ${TESTFILE})
    target_link_libraries(${TEST_NAME} PUBLIC srcmlxpath_shared)
    target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_SOURCE_DIR})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
#    message("-- Added test ${TEST_NAME} command ${TEST_NAME} program ${TESTFILE}")
endforeach()
