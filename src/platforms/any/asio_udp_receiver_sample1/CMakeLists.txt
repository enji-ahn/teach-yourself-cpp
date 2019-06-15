# CMakeList.txt : CMake project, include source and define
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

## project  ###################################################################
#
SET(OUTPUT_NAME "asio_udp_receiver_sample1")
SET(SOURCES
  "main.cpp"
  )

find_package(Threads REQUIRED)
set(EXTRA_LIBS ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE       (${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
