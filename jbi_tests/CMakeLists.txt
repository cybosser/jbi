include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(JBI_TESTS_SOURCE_FILES core_tests/exceptions_tests.cpp)

add_executable(jbitests ${JBI_TESTS_SOURCE_FILES})
target_link_libraries(jbitests gtest gtest_main)
