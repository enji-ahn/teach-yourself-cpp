# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/headers)

IF (WIN32)
	ADD_DEFINITIONS(-D_WIN32_WINNT=0x0601) # Windows 7
ENDIF (WIN32)

## project  ###################################################################
#
FIND_PACKAGE(Threads)
FIND_PACKAGE(Boost REQUIRED system thread)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
SET(Boost_USE_STATIC_LIBS ON)
#
SET(OUTPUT_NAME "asio_check_Connection")
SET(SOURCES
	"asio_check_when_the_connection_is_made.cpp"
	"asio_check_when_the_connection_is_made.h"
	"client.cpp"
	"pch.cpp"
	"pch.hpp"
	"server.cpp"
	)

ADD_EXECUTABLE(${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
	${Boost_LIBRARIES}
	${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.

