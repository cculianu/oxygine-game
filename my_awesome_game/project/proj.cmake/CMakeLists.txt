cmake_minimum_required (VERSION 2.6)
project (my_awesome_game)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../../../libs/oxygine-framework/ oxygine-framework)
add_definitions(${OXYGINE_DEFINITIONS})
include_directories(${OXYGINE_INCLUDE_DIRS})
link_directories(${OXYGINE_LIBRARY_DIRS})


add_subdirectory(../../../libs/oxygine-sound/ oxygine-sound)
add_definitions(${OXYGINESOUND_DEFINITIONS})
include_directories(${OXYGINESOUND_INCLUDE_DIRS})
link_directories(${OXYGINESOUND_LIBRARY_DIRS})

add_subdirectory(../../../libs/oxygine-flow/ oxygine-flow)
include_directories(${OXYGINE_FLOW_INCLUDE_DIRS})


add_subdirectory(../../../libs/oxygine-freetype/ oxygine-freetype)
include_directories(${OXYGINE_FREETYPE_INCLUDE_DIRS})
link_directories(${OXYGINE_FREETYPE_LIBRARY_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OXYGINE_CXX_FLAGS} ${OXYGINE_FREETYPE_CXX_FLAGS}")

set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/../src)
set(SOURCES 
	${SRC}/Enemy.cpp 
	${SRC}/Game.cpp
	${SRC}/GameMenu.cpp
	${SRC}/GameScene.cpp
	${SRC}/Joystick.cpp
	${SRC}/MainMenuScene.cpp
	${SRC}/MyButton.cpp
	${SRC}/Player.cpp
	${SRC}/Rocket.cpp
	${SRC}/MyScene.cpp
	${SRC}/Unit.cpp
	${SRC}/example.cpp
	${SRC}/main.cpp
	${SRC}/res.cpp
	${SRC}/Enemy.h
	${SRC}/Game.h
	${SRC}/GameMenu.h
	${SRC}/GameScene.h
	${SRC}/Joystick.h
	${SRC}/MainMenuScene.h
	${SRC}/MyButton.h
	${SRC}/Player.h
	${SRC}/Rocket.h
	${SRC}/MyScene.h
	${SRC}/Unit.h
	${SRC}/example.h
	${SRC}/res.h)

add_executable(my_awesome_game ${SOURCES})

if (WIN32) #disable console mode for VC++
	set_target_properties(my_awesome_game PROPERTIES WIN32_EXECUTABLE TRUE)
endif(WIN32)

find_package(SDL2 REQUIRED)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(EXTRA_LIBS "-framework AppKit")
endif()
target_link_libraries(my_awesome_game ${OXYGINESOUND_LIBS} oxygine-flow ${OXYGINE_CORE_LIBS} ${OXYGINE_FREETYPE_LIBS} oxygine-freetype SDL2::SDL2 SDL2::SDL2main ${EXTRA_LIBS})


if (EMSCRIPTEN)
	SET(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --memory-init-file 0 -s TOTAL_MEMORY=50331648 -s FORCE_FILESYSTEM=1")
	em_link_pre_js(my_awesome_game  ${OXYGINE_JS_LIBRARIES}  ${CMAKE_CURRENT_SOURCE_DIR}/data.js)
endif(EMSCRIPTEN)
