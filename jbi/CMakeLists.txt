set(JBI_HEADER_FILES
    algorithm/pp.h

    core/exceptions.h
    core/memory.h
    core/string.h
    core/type_traits.h
    core/utility.h

    interpreter/abstract_syntax_tree/arithmetic_operator.h
    interpreter/abstract_syntax_tree/assignment_statement.h
    interpreter/abstract_syntax_tree/expression.h
    interpreter/abstract_syntax_tree/literals.h
    interpreter/abstract_syntax_tree/node.h
    interpreter/abstract_syntax_tree/output_statement.h
    interpreter/abstract_syntax_tree/statement.h

    interpreter/lexical_analyser/flex/scanner.h
    interpreter/lexical_analyser/flex/scanner_generated.h
    interpreter/lexical_analyser/lexical_analyser.h
    interpreter/lexical_analyser/token.h

    interpreter/arithmetic_operation.h
    interpreter/interpreter.h
    interpreter/statement_evaluator.h
    interpreter/syntactic_analyser.h
    interpreter/type.h

    variant/static_visitor.h
    variant/variant.h
)

set(JBI_SOURCE_FILES
    interpreter/interpreter.cpp
    interpreter/statement_evaluator.cpp
    interpreter/syntactic_analyser.cpp

    interpreter/lexical_analyser/flex/scanner.cpp
    interpreter/lexical_analyser/lexical_analyser.cpp

    interpreter/type.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(jbi ${JBI_HEADER_FILES} ${JBI_SOURCE_FILES})
