# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

## project  ###################################################################
#
SET(OUTPUT_NAME "asio_udp_sender_sample1")
SET(SOURCES
  "main.cpp"
  )

IF (WIN32)
  ADD_DEFINITIONS(-D_WIN32_WINNT=0x0601) # Windows 7
ENDIF (WIN32)

find_package(Threads REQUIRED)
set(EXTRA_LIBS ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE       (${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
