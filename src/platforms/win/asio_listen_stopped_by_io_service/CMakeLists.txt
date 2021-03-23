# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/headers)

IF (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FC /Zi /Qspectre /W4")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D__STDC_WANT_SECURE_LIB__)
	ADD_DEFINITIONS(-D_WIN32_WINNT=0x0601) # Windows 7
ENDIF (WIN32)

## project  ###################################################################
#
FIND_PACKAGE(Threads)
FIND_PACKAGE(Boost REQUIRED system thread)
#INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
SET(Boost_USE_STATIC_LIBS ON)

SET(OUTPUT_NAME "asio_listen_stop")
SET(SOURCES
	"asio_listen_stopped_by_io_service.cpp"
	"asio_listen_stopped_by_io_service.hpp"
	"pch.cpp"
	"pch.hpp"
	)

ADD_EXECUTABLE(${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
	${Boost_LIBRARIES}
	${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
