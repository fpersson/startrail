find_package(Lua51)
find_package(Boost 1.4.2 COMPONENTS filesystem REQUIRED)
include_directories(${CMAKEDEMO_SOURCE_DIR}../src)
include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${Exiv2_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})


link_directories(${CMAKEDEMO_BINARY_DIR}/)

set(CORELIBS ${ImageMagick_LIBRARIES} ${LUA_LIBRARIES} ${Exiv2_LIBRARIES} ${Boost_LIBRARIES})

set(CMAKE_CXX_FLAGS "-shared -fPIC")
add_executable(libstartrail.so ${CORELIBS} libstartrail.cpp ../src/CImageComposer.cpp ../src/CCfgReader.cpp ../src/CExifHandler.cpp)
target_link_libraries(libstartrail.so ${CORELIBS})
