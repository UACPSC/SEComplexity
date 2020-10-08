# Build for srcComplexity

cmake_minimum_required(VERSION 3.14.0)

project(srcComplexity)

option(LINK_STATIC "Build with static library" OFF)

find_package(LibXml2 REQUIRED)
message("-- libxml2 include: " ${LIBXML2_INCLUDE_DIR})
message("-- libxml2 library: " ${LIBXML2_LIBRARY})

# Build srcComplexity
file(GLOB CLIENT_SOURCES "client/*.cpp")
add_executable(srcComplexity ${CLIENT_SOURCES})
if(LINK_STATIC)
    message("-- static library")
    target_link_libraries(srcComplexity PUBLIC srcmlxpath)
else()
    message("-- shared library")
    target_link_libraries(srcComplexity PUBLIC srcmlxpath_shared)
endif()
target_include_directories(srcComplexity PUBLIC libsrcmlxpath)

# libraries
file(GLOB LIBRARY_SOURCES "libsrcmlxpath/*.cpp")

# Static srcmlxpath library
add_library(srcmlxpath STATIC ${LIBRARY_SOURCES})
target_include_directories(srcmlxpath PUBLIC ${LIBXML2_INCLUDE_DIR})
target_include_directories(srcmlxpath PUBLIC .)
target_link_libraries(srcmlxpath PUBLIC ${LIBXML2_LIBRARY})

# Shared srcmlxpath library
add_library(srcmlxpath_shared SHARED ${LIBRARY_SOURCES})
target_include_directories(srcmlxpath_shared PUBLIC ${LIBXML2_INCLUDE_DIR})
target_include_directories(srcmlxpath_shared PUBLIC .)
target_link_libraries(srcmlxpath_shared PUBLIC ${LIBXML2_LIBRARY})
set_target_properties(srcmlxpath_shared PROPERTIES OUTPUT_NAME srcmlxpath)

# srcMLXPathCount test program
file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(srcMLXPathCount_t ${TEST_SOURCES})
target_include_directories(srcMLXPathCount_t PUBLIC ${LIBXML2_INCLUDE_DIR})
target_include_directories(srcMLXPathCount_t PUBLIC libsrcmlxpath)
target_link_libraries(srcMLXPathCount_t PUBLIC ${LIBXML2_LIBRARY})

# run example
set(SRCCOMPLEXITY_TESTFILE srcMLXPathCount.cpp.xml)
configure_file(${SRCCOMPLEXITY_TESTFILE} ${SRCCOMPLEXITY_TESTFILE} COPYONLY)
add_custom_target(run DEPENDS srcComplexity
                      COMMAND ./srcComplexity ${SRCCOMPLEXITY_TESTFILE})
