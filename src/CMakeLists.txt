# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#

# Include sub-projects.
ADD_SUBDIRECTORY ("platforms/any/helloworld")

ADD_SUBDIRECTORY ("platforms/win/BitOrder")
ADD_SUBDIRECTORY ("platforms/win/Integrating Mocking with C++ Default Parameters")
ADD_SUBDIRECTORY ("platforms/win/win32_handmade")
add_subdirectory ("platforms/win/순열")
add_subdirectory ("platforms/win/h_index")
add_subdirectory ("platforms/win/hate_same_number")
add_subdirectory ("platforms/win/function_dev")
add_subdirectory ("platforms/win/correct_bracket")
add_subdirectory ("platforms/win/processes")
add_subdirectory ("platforms/win/truck_on_bridge")
add_subdirectory ("platforms/win/stock_prices")
add_subdirectory ("platforms/win/more_spicy")
add_subdirectory ("platforms/win/double_prio_queue")


ADD_SUBDIRECTORY ("platforms/unix/coroutine_in_c")
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
ADD_SUBDIRECTORY ("platforms/any/async_via_await")

add_subdirectory("platforms/any/command_pattern")
add_subdirectory("platforms/any/observer_pattern")
add_subdirectory("platforms/any/state_pattern")
add_subdirectory("platforms/any/doublebuffer_pattern")
add_subdirectory("platforms/any/gameloop_pattern")

#ADD_SUBDIRECTORY ("platforms/any/game_logic")
# ADD_SUBDIRECTORY ("platforms/any/aiming_bullet")

add_subdirectory("platforms/any/std_map")
ADD_SUBDIRECTORY("platforms/any/nested_exception_handling")

ADD_SUBDIRECTORY ("platforms/any/generic_partition_and_stable_partition_algorithm")
ADD_SUBDIRECTORY ("platforms/any/generic_transform_algorithm")

ADD_SUBDIRECTORY ("platforms/any/copy_constructor")
## some compilers are not supported c++17 yet
#ADD_SUBDIRECTORY ("platforms/win/std_any")
