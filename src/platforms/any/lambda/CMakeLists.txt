# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

if (WIN32)
	add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
endif (WIN32)

## projects  ##################################################################
#
SET(OUTPUT "lamda_example")
SET(SOURCES "main.cpp")
ADD_EXECUTABLE       (${OUTPUT} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT} ${EXTRA_LIBS})

#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
