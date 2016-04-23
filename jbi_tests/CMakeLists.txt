include_directories(${gtest_SOURCE_DIR}/include ${gmock_SOURCE_DIR}/include)

set(JBI_TESTS_SOURCE_FILES
    algorithm_tests/pp_tests.cpp

    core_tests/exceptions_tests.cpp
    core_tests/string_tests.cpp
    core_tests/utility_tests.cpp

    interpreter_tests/arithmetic_operation_tests.cpp
    interpreter_tests/lexical_analyser_tests/lexical_analyser_tests.cpp
    interpreter_tests/syntactic_analyser_tests.cpp

    variant_tests/variant_tests.cpp

    visitable_tests/visitable_tests.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(jbi_tests ${JBI_TESTS_SOURCE_FILES})
target_link_libraries(jbi_tests jbi gmock gmock_main)
