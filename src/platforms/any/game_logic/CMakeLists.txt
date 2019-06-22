# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

## project  ###################################################################
#
SET(OUTPUT_NAME "game_logic")
SET(SOURCES
  "main.cpp"
  "game.cpp"
  )

find_package(Threads REQUIRED)
find_package(SFML 2 COMPONENTS network audio graphics window system REQUIRED)
set(EXTRA_LIBS ${CMAKE_THREAD_LIBS_INIT} sfml-graphics sfml-audio sfml-network sfml-window sfml-system)

# cmake -DCMAKE_BUILD_TYPE=Debug / cmake -DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")


ADD_EXECUTABLE       (${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
