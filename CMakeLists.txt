cmake_minimum_required(VERSION 4.0)

project(ProyectTurnBasedGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/BIN)

set(PROJECT_SOURCES
	src/main.cpp
	src/Character.cpp
	src/Enemy.cpp
	src/GameManager.cpp
	src/HUD.cpp
	src/Inventory.cpp
	src/Item.cpp
	src/Map.cpp
	src/Player.cpp
	src/Skill.cpp
	src/Stats.cpp
	src/TurnBasedSystem.cpp)

set(PROJECT_HEADERS
	include/Character.h
	include/Enemy.h
	include/GameManager.h
	include/HUD.h
	include/Inventory.h
	include/Item.h
	include/Map.h
	include/Player.h
	include/Skill.h
	include/Stats.h
	include/TurnBasedSystem.h)

set(PROJECT_FILES ${PROJECT_SOURCES} ${PROJECT_HEADERS})

set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include/)

target_link_libraries(ProyectTurnBasedGame
    sfml-graphics
    sfml-window
    sfml-system
)

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
endif()

if (WIN32)
    add_custom_command(TARGET ProyectTurnBasedGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/bin"
        $<TARGET_FILE_DIR:ProyectTurnBasedGame>)
endif()