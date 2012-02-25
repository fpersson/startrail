find_package(Boost 1.4.2 COMPONENTS program_options filesystem system REQUIRED)
include_directories(${CMAKEDEMO_SOURCE_DIR}../src)
include_directories(${ImageMagick_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${Exiv2_INCLUDE_DIRS})

add_definitions( -DSTAND_ALONE )

link_directories(${CMAKEDEMO_BINARY_DIR}/)

set(CORELIBS ${ImageMagick_LIBRARIES} ${LUA_LIBRARIES} ${Boost_LIBRARIES} ${Exiv2_LIBRARIES})

add_executable(startrail ${CORELIBS} main.cpp ../src/CImageComposer.cpp ../src/CCfgReader.cpp ../src/CExifHandler.cpp)
target_link_libraries(startrail ${CORELIBS})
