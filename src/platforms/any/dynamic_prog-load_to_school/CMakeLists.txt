
# project specific logic here.
#

include_directories(${CMAKE_SOURCE_DIR}/src/headers)

## project  ###################################################################
#
SET(OUTPUT_NAME "dynamic_prog-load_to_school")
SET(SOURCES
  "main.cpp"
  )

# cmake -DCMAKE_BUILD_TYPE=Debug / cmake -DCMAKE_BUILD_TYPE=Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")


ADD_EXECUTABLE       (${OUTPUT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES(${OUTPUT_NAME} ${EXTRA_LIBS})
#
#################################################################### project ##

# TODO: Add tests and install targets if needed.
