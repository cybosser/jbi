set(IJBI_SOURCE_FILES main.cpp)

add_executable(ijbi ${IJBI_SOURCE_FILES})
target_link_libraries(ijbi jbi)
