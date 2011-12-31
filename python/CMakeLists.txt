find_package(Boost 1.4.2 COMPONENTS filesystem python REQUIRED)
find_package(PythonLibs REQUIRED)
include_directories(${CMAKEDEMO_SOURCE_DIR}../src)
include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${Exiv2_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})


link_directories(${CMAKEDEMO_BINARY_DIR}/)

set(CORELIBS ${ImageMagick_LIBRARIES} ${LUA_LIBRARIES} ${Exiv2_LIBRARIES} ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

add_library(_pystartrail SHARED libstartrail.cpp ../src/CImageComposer.cpp ../src/CCfgReader.cpp ../src/CExifHandler.cpp)
target_link_libraries(_pystartrail ${CORELIBS})
