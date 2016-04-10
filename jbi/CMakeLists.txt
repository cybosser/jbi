set(JBI_HEADER_FILES
    algorithm/pp.h

    core/exceptions.h
    core/type_traits.h

    interpreter/interpreter.h
)

set(JBI_SOURCE_FILES interpreter/interpreter.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(jbi ${JBI_HEADER_FILES} ${JBI_SOURCE_FILES})
