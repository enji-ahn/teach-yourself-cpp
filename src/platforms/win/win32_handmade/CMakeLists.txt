# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ide.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/platform.cmake)
include_directories(${CMAKE_SOURCE_DIR}/src/headers)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FC /Zi /Qspectre /W4")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D__STDC_WANT_SECURE_LIB__)
	add_definitions(-D_WIN32_WINNT=0x0A00) # Windows 10
endif (WIN32)

## project  ###################################################################
#
SET(OUTPUT_NAME "win32_handmade")
SET(SOURCES
  "main.cpp"
  "pch.cpp"
  "pch.h"
  )

ADD_EXECUTABLE       (${OUTPUT_NAME} WIN32 ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS}
    XInput # Windows XInput (for Xbox 360/One controller support)
    DSound
    user32.lib gdi32.lib)
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
