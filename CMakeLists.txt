# Build for srcComplexity

cmake_minimum_required(VERSION 3.14.0)

project(srcComplexity VERSION "0.9.5")

find_package(LibXml2 REQUIRED)
message("-- libxml2 include: " ${LIBXML2_INCLUDE_DIR})
message("-- libxml2 library: " ${LIBXML2_LIBRARY})

# Build srcComplexity
add_executable(srcComplexity srcComplexity.cpp)
target_link_libraries(srcComplexity PUBLIC srcmlxpath_shared)
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
#set_target_properties(srcmlxpath_shared PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(srcmlxpath_shared PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
install(TARGETS srcmlxpath_shared LIBRARY)

# strip executables and link_libraries
# Verify that it works
set(CPACK_STRIP_FILES ON)

set(CPACK_PACKAGE_NAME "srccomplexity")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_CONTACT "Michael L. Collard <collard@uakron.edu>")

# Copyright
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/COPYING.txt)
install(FILES ${CMAKE_SOURCE_DIR}/COPYING.txt DESTINATION share/doc/srccomplexity RENAME copyright)

# Description
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Calculate source code complexity")
file(WRITE ${CMAKE_BINARY_DIR}/description.txt
"srcComplexity Hi
")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_BINARY_DIR}/description.txt)

# Changelog file - required by lintian
file(WRITE ${CMAKE_BINARY_DIR}/changelog
"srcComplexity (1.0.0-1) UNRELEASED; urgency=medium

  * Initial release

 -- Michael L. Collard <collard@uakron.edu>  Fri, 30 Oct 2020 17:00:00 +0400
")
execute_process(COMMAND gzip -n -9 -f ${CMAKE_BINARY_DIR}/changelog)
install(FILES ${CMAKE_BINARY_DIR}/changelog.gz DESTINATION share/doc/srccomplexity)

# Trigger required for library installed in client to initiate ldconfig
set(TRIGGERS_FILE "${CMAKE_CURRENT_BINARY_DIR}/triggers")
file(WRITE "${TRIGGERS_FILE}" "activate-noawait ldconfig\n")

# Remove the conf files that shows CPackDeb does not know what it is doing
file(WRITE ${CMAKE_BINARY_DIR}/postrm "#!/bin/sh
set -e

if [ \"$1\" = \"remove\" ]; then
    echo
fi
")
file(WRITE ${CMAKE_BINARY_DIR}/postinst "#!/bin/sh
set -e

if [ \"$1\" = \"remove\" ]; then
    echo
fi
")

# Extra files are triggers, postinst, postrm
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${TRIGGERS_FILE};${CMAKE_BINARY_DIR}/postinst;${CMAKE_BINARY_DIR}/postrm")

# Autogenerate dependency information
set(CPACK_DEBIAN_PACKAGE_DEBUG ON)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_GENERATE_SHLIBS ON)

include(CPack)
