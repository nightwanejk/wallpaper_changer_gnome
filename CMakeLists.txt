cmake_minimum_required(VERSION 3.16)

project(WallpaperChanger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(WallpaperChanger main.cpp)

include(GNUInstallDirs)
install(TARGETS WallpaperChanger
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
