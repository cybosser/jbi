set(JBI_HEADER_FILES core/exceptions.h)

set(JBI_SOURCE_FILES interpreter/interpreter.cpp)

add_library(jbi ${JBI_HEADER_FILES} ${JBI_SOURCE_FILES})
