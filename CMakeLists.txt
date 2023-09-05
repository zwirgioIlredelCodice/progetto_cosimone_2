cmake_minimum_required(VERSION 3.24)
project(CHARacter_adventure)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
add_executable(CHARacter_adventure main.cpp Salvataggio.cpp Salvataggio.hpp nemici.hpp nemici.cpp strutture.h strutture.h Potenziamenti.cpp Potenziamenti.hpp player.hpp player.cpp mapList.hpp mapList.cpp
        Negozio.cpp Negozio.hpp
        Manager.cpp Manager.cpp)
target_link_libraries(CHARacter_adventure ${CURSES_LIBRARIES})
