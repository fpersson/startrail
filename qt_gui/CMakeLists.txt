find_package(Boost 1.4.2 COMPONENTS program_options filesystem system REQUIRED)
find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(${ImageMagick_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${Exiv2_INCLUDE_DIRS})

set(SRC 
  main.cpp
  mainwindow.cpp
  ../src/CCfgReader.cpp
  ../src/CProjReader.cpp
  ../src/CProjWriter.cpp
  ../src/CImageComposer.cpp
  ../src/CExifHandler.cpp
)

set(HEADERS 
  mainwindow.h
)

set(CORELIBS ${ImageMagick_LIBRARIES} ${Boost_LIBRARIES} ${Exiv2_LIBRARIES})

QT4_WRAP_UI(UI_SRC mainwindow.ui)
QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})

add_executable(sample ${CORELIBS} ${SRC} ${HEADERS_MOC} ${UI_SRC})
target_link_libraries(sample ${CORELIBS} ${QT_LIBRARIES})
