include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(JBI_TESTS_SOURCE_FILES
    algorithm_tests/pp_tests.cpp

    core_tests/exceptions_tests.cpp
    core_tests/string_tests.cpp
    core_tests/variant_tests.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(jbi_tests ${JBI_TESTS_SOURCE_FILES})
target_link_libraries(jbi_tests gtest gtest_main)
