find_package(Lua51)
include_directories(${CMAKEDEMO_SOURCE_DIR}../src)
include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${LUA_INCLUDE_DIR})

link_directories(${CMAKEDEMO_BINARY_DIR}/)

set(CORELIBS ${ImageMagick_LIBRARIES} ${LUA_LIBRARIES})

set(CMAKE_CXX_FLAGS "-shared -fPIC")
add_executable(libstartrail.so ${CORELIBS} libstartrail.cpp ../src/CImageComposer.cpp ../src/CCfgReader.cpp)
target_link_libraries(libstartrail.so ${CORELIBS})
