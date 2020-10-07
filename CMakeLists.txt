# Build for srcComplexity

cmake_minimum_required(VERSION 3.14.0)

project(srcComplexity)

find_package(LibXml2 REQUIRED)
message("-- libxml2 include: " ${LIBXML2_INCLUDE_DIR})
message("-- libxml2 library: " ${LIBXML2_LIBRARY})

# Build srcComplexity
add_executable(srcComplexity srcComplexity.cpp)
target_link_libraries(srcComplexity PUBLIC srcmlxpath_shared)

# Object library srcmlxpathobj
add_library(srcmlxpathobj OBJECT srcMLXPathCount.cpp)
target_include_directories(srcmlxpathobj PUBLIC ${LIBXML2_INCLUDE_DIR})

# Static srcmlxpath library
add_library(srcmlxpath STATIC $<TARGET_OBJECTS:srcmlxpathobj>)
target_link_libraries(srcmlxpath PUBLIC ${LIBXML2_LIBRARY})

# Shared srcmlxpath library
add_library(srcmlxpath_shared SHARED $<TARGET_OBJECTS:srcmlxpathobj>)
target_link_libraries(srcmlxpath_shared PUBLIC ${LIBXML2_LIBRARY})
set_target_properties(srcmlxpath_shared PROPERTIES OUTPUT_NAME srcmlxpath)

# run example
set(SRCCOMPLEXITY_TESTFILE srcMLXPathCount.cpp.xml)
configure_file(${SRCCOMPLEXITY_TESTFILE} ${SRCCOMPLEXITY_TESTFILE} COPYONLY)
add_custom_target(run DEPENDS srcComplexity
                      COMMAND ./srcComplexity ${SRCCOMPLEXITY_TESTFILE})
