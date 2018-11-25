# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

# Include sub-projects.
add_subdirectory ("platforms/win/BitOrder")
add_subdirectory ("platforms/win/Integrating Mocking with C++ Default Parameters")
## some compilers are not supported c++17 yet
#add_subdirectory ("platforms/win/std_any")
