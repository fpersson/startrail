cmake_minimum_required (VERSION 2.6)
project(STARTRAIL)

set (VERSION_MAJOR 2)
set (VERSION_MINOR 2)
set (VERSION_REALESE 1)

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
find_package(Lua51)
find_package(PythonLibs)
find_package(Qt4)

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
add_subdirectory(test)

#om lua finns kan vi använda det
if(LUA51_FOUND)
  add_subdirectory(lib)
  message("Lua [OK]")
endif(LUA51_FOUND)

#om python finns kan vi använda det, borde även kolla boost::python...
if(PYTHONLIBS_FOUND)
  add_subdirectory(python)
  message("Python [OK]")
endif(PYTHONLIBS_FOUND)

#för att bygga QT-GUI
if(QT4_FOUND)
   add_subdirectory(qt_gui)
   message("QT4 [OK]")
endif(QT4_FOUND)
