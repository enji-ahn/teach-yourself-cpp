# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
endif (WIN32)

## project  ###################################################################
#
SET(OUTPUT_NAME "shell_sort")
SET(SOURCES
  "main.cpp"
  "pch.cpp"
  "pch.h"
  )

ADD_EXECUTABLE       (${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
