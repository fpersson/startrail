cmake_minimum_required (VERSION 2.6)
project(STARTRAIL)

set (VERSION_MAJOR 2)
set (VERSION_MINOR 1)
set (VERSION_REALESE 6)

configure_file (
  "${PROJECT_SOURCE_DIR}/src/config.h.in"
  "${PROJECT_BINARY_DIR}/src/config.h"
)

configure_file (
  "${PROJECT_SOURCE_DIR}/about.txt.in"
  "${PROJECT_BINARY_DIR}/about.txt"
)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(ImageMagick COMPONENTS Magick++)
find_package(Exiv2)
find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_subdirectory(src)
add_subdirectory(bin)
add_subdirectory(lib)
add_subdirectory(python)