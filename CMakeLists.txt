# Build for srcComplexity

cmake_minimum_required(VERSION 3.14.0)

project(srcComplexity VERSION "0.9.5")

option(LINK_STATIC "Build with static library" OFF)

find_package(LibXml2 REQUIRED)
message("-- libxml2 include: " ${LIBXML2_INCLUDE_DIR})
message("-- libxml2 library: " ${LIBXML2_LIBRARY})

# Build srcComplexity
add_executable(srcComplexity srcComplexity.cpp)
if(LINK_STATIC)
    message("-- static library")
    target_link_libraries(srcComplexity PUBLIC srcmlxpath)
else()
    message("-- shared library")
    target_link_libraries(srcComplexity PUBLIC srcmlxpath_shared)
endif()
install(TARGETS srcComplexity RUNTIME)

# Static srcmlxpath library
add_library(srcmlxpath STATIC srcMLXPathCount.cpp)
target_include_directories(srcmlxpath PUBLIC ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcmlxpath PUBLIC ${LIBXML2_LIBRARY})
install(TARGETS srcmlxpath LIBRARY)

# Shared srcmlxpath library
add_library(srcmlxpath_shared SHARED srcMLXPathCount.cpp)
target_include_directories(srcmlxpath_shared PUBLIC ${LIBXML2_INCLUDE_DIR})
target_link_libraries(srcmlxpath_shared PUBLIC ${LIBXML2_LIBRARY})
set_target_properties(srcmlxpath_shared PROPERTIES OUTPUT_NAME srcmlxpath)
set_target_properties(srcmlxpath_shared PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(srcmlxpath_shared PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
install(TARGETS srcmlxpath_shared LIBRARY)

# run example
set(SRCCOMPLEXITY_TESTFILE srcMLXPathCount.cpp.xml)
configure_file(${SRCCOMPLEXITY_TESTFILE} ${SRCCOMPLEXITY_TESTFILE} COPYONLY)
add_custom_target(run DEPENDS srcComplexity
                      COMMAND ./srcComplexity ${SRCCOMPLEXITY_TESTFILE})

set(CPACK_PACKAGE_NAME "srccomplexity")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_CONTACT "collard@uakron.edu")
include(CPack)
