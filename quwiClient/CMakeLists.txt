cmake_minimum_required(VERSION 3.5)

project(quwiClient LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

if(ANDROID)
    add_library(quwiClient SHARED
      main.cpp
      login.cpp
      login.h
      projectshandler.cpp
      projectshandler.h
      projectmanager.cpp
      projectmanager.h
      quwihttpmanager.cpp
      quwihttpmanager.h
      public.h
      qml.qrc
    )
else()
    add_executable(quwiClient
      main.cpp
      login.cpp
      login.h
      projectshandler.cpp
      projectshandler.h
      projectmanager.cpp
      projectmanager.h
      quwihttpmanager.cpp
      quwihttpmanager.h
      public.h
      qml.qrc
    )
endif()

target_compile_definitions(quwiClient
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(quwiClient
  PRIVATE Qt5::Core Qt5::Quick)
