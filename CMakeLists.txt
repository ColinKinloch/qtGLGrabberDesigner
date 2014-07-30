project(grabber)
cmake_minimum_required(VERSION 2.6)

find_package(Qt4 REQUIRED)
find_package(OpenGL REQUIRED)

set(GRABBER_INCLUDES
  
)
set(GRABBER_HEADERS
  ${GRABBER_INCLUDES}
  src/mainwindow.h
  src/glwidget.h
)
set(GRABBER_SRCS
  src/main.cpp
  src/mainwindow.cpp
  src/glwidget.cpp
)
set(GRABBER_FORMS
  form/grabber.ui
)
set(GRABBER_RESOURCES
  
)
qt4_wrap_ui(GRABBER_FORMS_HEADERS ${GRABBER_FORMS})
qt4_wrap_cpp(GRABBER_HEADERS_MOC ${GRABBER_HEADERS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
include_directories(${QT_QTOPENGL_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(grabber
  ${GRABBER_SRCS}
  ${GRABBER_HEADERS_MOC}
  ${GRABBER_FORMS_HEADERS}
)
target_link_libraries(grabber ${QT_LIBRARIES})
target_link_libraries(grabber ${QT_QTOPENGL_LIBRARY})
target_link_libraries(grabber ${OPENGL_LIBRARY})
