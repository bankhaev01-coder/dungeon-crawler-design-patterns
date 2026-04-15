cmake_minimum_required(VERSION 3.10)
project(DungeonCrawler)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

set(SFML_DIR "C:\\mingw64\\SFML-3.0.2\\lib\\cmake\\SFML")


find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(dungeon main.cpp ${SOURCES})

target_link_libraries(dungeon SFML::Graphics SFML::Window SFML::System)