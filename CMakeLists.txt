cmake_minimum_required(VERSION 3.24)
project(progetto_cosimone_2)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(progetto_cosimone_2 main.cpp protagonista.hpp protagonista.cpp salvataggio.cpp salvataggio.hpp nemici.hpp nemici.cpp strutture.h strutture.h)
target_link_libraries(progetto_cosimone_2 ${CURSES_LIBRARIES})
