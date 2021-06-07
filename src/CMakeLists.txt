# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

# Include sub-projects.
ADD_SUBDIRECTORY ("platforms/any/helloworld")

ADD_SUBDIRECTORY ("platforms/win/BitOrder")
ADD_SUBDIRECTORY ("platforms/win/Integrating Mocking with C++ Default Parameters")
ADD_SUBDIRECTORY ("platforms/win/win32_handmade")

# ADD_SUBDIRECTORY ("platforms/win/asio_check_when_the_connection_is_made")
# ADD_SUBDIRECTORY ("platforms/win/asio_listen_stopped_by_io_service")
ADD_SUBDIRECTORY ("platforms/any/class_templated_stack")
# ADD_SUBDIRECTORY ("platforms/any/circular_list")
# ADD_SUBDIRECTORY ("platforms/any/random_integer_generator_simple")
ADD_SUBDIRECTORY ("platforms/any/random_integer_generator_alter")
# ADD_SUBDIRECTORY ("platforms/any/random_integer_generator_closure")
# ADD_SUBDIRECTORY ("platforms/any/generator_via_template")
# ADD_SUBDIRECTORY ("platforms/any/operator_override")
ADD_SUBDIRECTORY ("platforms/any/working_effectively_with_legacy_code")
ADD_SUBDIRECTORY ("platforms/any/lambda")

ADD_SUBDIRECTORY ("platforms/any/asio_udp_receiver_sample1")
ADD_SUBDIRECTORY ("platforms/any/asio_udp_sender_sample1")

ADD_SUBDIRECTORY ("platforms/any/insertion_sort")
ADD_SUBDIRECTORY ("platforms/any/shell_sort")
ADD_SUBDIRECTORY ("platforms/any/async_via_thread")
ADD_SUBDIRECTORY ("platforms/any/async_via_promise")

#ADD_SUBDIRECTORY ("platforms/any/game_logic")
# ADD_SUBDIRECTORY ("platforms/any/aiming_bullet")

ADD_SUBDIRECTORY ("platforms/any/generic_partition_and_stable_partition_algorithm")
ADD_SUBDIRECTORY ("platforms/any/generic_transform_algorithm")

ADD_SUBDIRECTORY ("platforms/any/copy_constructor")
## some compilers are not supported c++17 yet
#ADD_SUBDIRECTORY ("platforms/win/std_any")
