
# project specific logic here.
#

# Include sub-projects.
ADD_SUBDIRECTORY ("platforms/any/helloworld")
ADD_SUBDIRECTORY ("platforms/any/여러-번역-단위에-걸친-룩업")
ADD_SUBDIRECTORY ("platforms/any/예외로부터-보호")
ADD_SUBDIRECTORY ("platforms/any/hash-pocketmon")
ADD_SUBDIRECTORY ("platforms/any/hash-marathoners")
ADD_SUBDIRECTORY ("platforms/any/hash-phonebook")
ADD_SUBDIRECTORY ("platforms/any/hash-bestalbum")
ADD_SUBDIRECTORY ("platforms/any/hash-clothes")
ADD_SUBDIRECTORY ("platforms/any/exhaustive_search-min_rect")
ADD_SUBDIRECTORY ("platforms/any/exhaustive_search-prime_number")
add_subdirectory ("platforms/any/exhaustive_search-tired")
add_subdirectory ("platforms/any/exhaustive_search-vowel_dict")

if (WIN32)
  ADD_SUBDIRECTORY ("platforms/win/BitOrder")
  ADD_SUBDIRECTORY ("platforms/win/Integrating Mocking with C++ Default Parameters")
  ADD_SUBDIRECTORY ("platforms/win/win32_handmade")
  ADD_SUBDIRECTORY ("platforms/win/순열")
  ADD_SUBDIRECTORY ("platforms/win/h_index")
  ADD_SUBDIRECTORY ("platforms/win/hate_same_number")
  ADD_SUBDIRECTORY ("platforms/win/function_dev")
  ADD_SUBDIRECTORY ("platforms/win/correct_bracket")
  ADD_SUBDIRECTORY ("platforms/win/processes")
  ADD_SUBDIRECTORY ("platforms/win/truck_on_bridge")
  ADD_SUBDIRECTORY ("platforms/win/stock_prices")
  ADD_SUBDIRECTORY ("platforms/win/more_spicy")
  ADD_SUBDIRECTORY ("platforms/win/double_prio_queue")
  ADD_SUBDIRECTORY ("platforms/win/insertion_sort")
  ADD_SUBDIRECTORY ("platforms/win/shell_sort")
  ADD_SUBDIRECTORY ("platforms/win/async_via_thread")
endif (WIN32)

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

ADD_SUBDIRECTORY ("platforms/any/async_via_promise")
ADD_SUBDIRECTORY ("platforms/any/async_via_await")

ADD_SUBDIRECTORY ("platforms/any/command_pattern")
ADD_SUBDIRECTORY ("platforms/any/observer_pattern")
ADD_SUBDIRECTORY ("platforms/any/state_pattern")
ADD_SUBDIRECTORY ("platforms/any/doublebuffer_pattern")
ADD_SUBDIRECTORY ("platforms/any/gameloop_pattern")

#ADD_SUBDIRECTORY ("platforms/any/game_logic")
# ADD_SUBDIRECTORY ("platforms/any/aiming_bullet")

ADD_SUBDIRECTORY ("platforms/any/std_map")
ADD_SUBDIRECTORY ("platforms/any/nested_exception_handling")

ADD_SUBDIRECTORY ("platforms/any/generic_partition_and_stable_partition_algorithm")
ADD_SUBDIRECTORY ("platforms/any/generic_transform_algorithm")

ADD_SUBDIRECTORY ("platforms/any/copy_constructor")
## some compilers are not supported c++17 yet
#ADD_SUBDIRECTORY ("platforms/win/std_any")
