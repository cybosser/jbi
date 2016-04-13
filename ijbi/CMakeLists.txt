set(IJBI_HEADER_FILES
    io/console.h

    printer.h
)

set(IJBI_SOURCE_FILES
    io/console.cpp

    main.cpp
    printer.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(ijbi ${IJBI_HEADER_FILES} ${IJBI_SOURCE_FILES})
target_link_libraries(ijbi jbi)
