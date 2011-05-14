cmake_minimum_required (VERSION 2.6)
project(STARTRAIL)

find_package(ImageMagick COMPONENTS Magick++)

add_subdirectory(src)
add_subdirectory(bin)
add_subdirectory(lib)

