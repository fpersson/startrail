# Breif - A minimal working CMakeLists.txt for goggle unittesting
# Author - Fredrik Persson - fpersson.se@gmail.com
# Licens - BSD
cmake_minimum_required (VERSION 2.6)
project(demo)

find_package(Boost 1.4.2 COMPONENTS program_options filesystem system filesystem unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(CORELIBS ${Boost_LIBRARIES})

add_executable(demo_unittest ${CORELIBS} unittest.cpp ../src/CCfgReader.cpp ../src/CProjReader.cpp ../src/CProjWriter.cpp ../src/CFileLister.cpp)
target_link_libraries(demo_unittest ${CORELIBS})