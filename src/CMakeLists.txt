# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

# Include sub-projects.
ADD_SUBDIRECTORY ("platforms/win/BitOrder")
ADD_SUBDIRECTORY ("platforms/win/Integrating Mocking with C++ Default Parameters")
ADD_SUBDIRECTORY ("platforms/win/asio_check_when_the_connection_is_made")
ADD_SUBDIRECTORY ("platforms/win/asio_listen_stopped_by_io_service")
ADD_SUBDIRECTORY ("platforms/any/class_templated_stack")
## some compilers are not supported c++17 yet
#ADD_SUBDIRECTORY ("platforms/win/std_any")

