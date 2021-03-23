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

IF (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FC /Zi /Qspectre /W4")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D__STDC_WANT_SECURE_LIB__)
    ADD_DEFINITIONS(-D_WIN32_WINNT=0x0601) # Windows 7
ENDIF (WIN32)

find_package(Threads REQUIRED)
set(EXTRA_LIBS ${CMAKE_THREAD_LIBS_INIT})

# cmake -DCMAKE_BUILD_TYPE=Debug / cmake -DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DBOOST_ASIO_ENABLE_HANDLER_TRACKING")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

ADD_EXECUTABLE       (${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
