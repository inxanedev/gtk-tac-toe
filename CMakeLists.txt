cmake_minimum_required(VERSION 3.10)
project(gtk-tac-toe)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-3.0)

add_executable(gtk-tac-toe
    "src/main.cc"
    "src/game_window.cc"
    "src/game.cc"
)
target_include_directories(gtk-tac-toe PRIVATE "./src/")
target_link_libraries(gtk-tac-toe PUBLIC
    PkgConfig::GTKMM
)
