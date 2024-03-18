
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

## project  ###################################################################
#
SET(OUTPUT_NAME "hash-marathoners")
SET(SOURCES
  "main.cpp"
  )

# cmake -DCMAKE_BUILD_TYPE=Debug / cmake -DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

ADD_EXECUTABLE       (${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
