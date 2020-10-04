# Build for srcComplexity

cmake_minimum_required(VERSION 3.14.0)

project(srcComplexity)

find_package(LibXml2 REQUIRED)
message("-- libxml2 include: " ${LIBXML2_INCLUDE_DIR})
message("-- libxml2 library: " ${LIBXML2_LIBRARY})

# Builds srcComplexity
add_executable(srcComplexity srcComplexity.cpp srcMLXPathCount.cpp)
target_include_directories(srcComplexity PUBLIC ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcComplexity PUBLIC ${LIBXML2_LIBRARY})

# run example
set(SRCCOMPLEXITY_TESTFILE srcMLXPathCount.cpp.xml)
configure_file(${SRCCOMPLEXITY_TESTFILE} ${SRCCOMPLEXITY_TESTFILE} COPYONLY)
add_custom_target(run DEPENDS srcComplexity
                      COMMAND ./srcComplexity ${SRCCOMPLEXITY_TESTFILE})
