
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


