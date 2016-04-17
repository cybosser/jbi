set(JBI_HEADER_FILES
    algorithm/pp.h

    core/exceptions.h
    core/none.h
    core/string.h
    core/type_traits.h

    interpreter/interpreter.h
    interpreter/lexer/flex/scanner.h
    interpreter/lexer/flex/scanner_generated.h
    interpreter/lexer/lexer.h
    interpreter/lexer/token.h
    interpreter/type.h

    variant/static_visitor.h
    variant/variant.h
)

set(JBI_SOURCE_FILES
    core/none.cpp

    interpreter/interpreter.cpp
    interpreter/lexer/flex/scanner.cpp
    interpreter/lexer/lexer.cpp
    interpreter/type.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(jbi ${JBI_HEADER_FILES} ${JBI_SOURCE_FILES})
