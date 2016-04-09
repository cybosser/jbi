cmake_minimum_required(VERSION 3.3)

project(jbi)

include_directories(.)

add_subdirectory(jbi)
add_subdirectory(ijbi)

add_subdirectory(thirdparty)

add_subdirectory(jbi_tests)
