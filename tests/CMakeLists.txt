# CMakeLists.txt for tests

# Optionally, find_package(Catch2) or use your own test framework
# Here, we assume test sources are in this directory

add_executable(router_tests router_tests.cpp)
target_link_libraries(router_tests PRIVATE lightcppframework)
add_test(NAME RouterTests COMMAND router_tests)

add_executable(http_tests http_tests.cpp)
target_link_libraries(http_tests PRIVATE lightcppframework)
add_test(NAME HTTPTests COMMAND http_tests)

add_executable(static_tests static_tests.cpp)
target_link_libraries(static_tests PRIVATE lightcppframework)
add_test(NAME StaticTests COMMAND static_tests) 