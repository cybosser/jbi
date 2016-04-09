set(IJBI_HEADER_FILES io/console.h)

set(IJBI_SOURCE_FILES
    io/console.cpp

    main.cpp
)

add_executable(ijbi ${IJBI_HEADER_FILES} ${IJBI_SOURCE_FILES})
target_link_libraries(ijbi jbi)
