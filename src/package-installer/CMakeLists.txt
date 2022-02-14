if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
    add_definitions(-D_x86_64_)
elseif(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86")
    add_definitions(-D_x86_)
endif ()
message("Your System is ${CMAKE_SYSTEM_PROCESSOR}")
add_library(package-installer
        PackageInstaller.h
        PackageInstaller.cpp)
target_link_libraries(package-installer
        packagekit-glib2
        glib-2.0
        gobject-2.0
        gio-2.0)