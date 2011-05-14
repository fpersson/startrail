find_package( Boost 1.36.0 )
include_directories(${CMAKEDEMO_SOURCE_DIR}../src)
include_directories(${ImageMagick_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

link_directories(${CMAKEDEMO_BINARY_DIR}../)

set(CORELIBS ${ImageMagick_LIBRARIES} ${LUA_LIBRARIES} ${Boost_LIBRARIES})

add_executable(startrail ${CORELIBS} main.cpp ../src/CImageComposer.cpp ../src/CCfgReader.cpp)
target_link_libraries(startrail ${CORELIBS})
