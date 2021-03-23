# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /FC /Zi /Qspectre /W4")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
    add_definitions(-D__STDC_WANT_SECURE_LIB__)
	add_definitions(-D_WIN32_WINNT=0x0601) # Windows 7
endif (WIN32)

## projects  ##################################################################
#
SET(FAKE_OBJECT_OUTPUT "fake_object")
SET(FAKE_OBJECT_SOURCES "fake_object.cpp")
ADD_EXECUTABLE       (${FAKE_OBJECT_OUTPUT} ${FAKE_OBJECT_SOURCES})
TARGET_LINK_LIBRARIES(${FAKE_OBJECT_OUTPUT} ${EXTRA_LIBS})

#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
