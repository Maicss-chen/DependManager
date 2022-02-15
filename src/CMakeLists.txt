
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
add_subdirectory(build-system-parser)
add_subdirectory(package-installer)

add_executable(DependManager
        main.cpp
        MainWindow.cpp
        MainWindow.h
        pages/PageOpenProject.cpp
        pages/PageOpenProject.h
        pages.h pages/PageWorking.cpp
        pages/PageWorking.h
        pages/PageDependChoose.cpp
        pages/PageDependChoose.h
        build-system-parser/BSParser.cpp
        build-system-parser/BSParser.h
        pages/PageBSChoose.cpp
        pages/PageBSChoose.h
        build-system-parser/XMakeBSParser.cpp
        build-system-parser/XMakeBSParser.h
        pages/PageInstallWorking.cpp
        pages/PageInstallWorking.h
        )

target_link_libraries(DependManager
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        bsparser
        package-installer
        )

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.4)
    message(FATAL_ERROR "You are on an extremely old version of GCC. Please update your compiler to at least GCC 5.4, preferably latest")
  elseif (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11.0)
    message(WARNING "Old Verison of GCC detected. Using Legacy C++ support")
    target_link_libraries(${PROJECT_NAME} -lstdc++fs)
    target_compile_definitions(${PROJECT_NAME} PUBLIC LEGACY_CXX)
  endif()
endif()
