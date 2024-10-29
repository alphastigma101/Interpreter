# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -fconcepts -w
LDFLAGS := -L $(HOME)/Interpreter/tests -lgtest -lgtest_main -pthread

# Include directories
INCLUDES := -I types/ -I logging/ -I asm/ -I catch/ -I tokens/ \
            -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ \
            -I scanner/ -I parser/ -I threading/ -I addon/

########
# Compiler flags for specific components
DEBUG_AST_FLAGS := -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1 -DENABLE_TREE_DEBUGGING=1
DEBUG_INTERPRETER_FLAGS := -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1 -DENABLE_TREE_DEBUGGING=1
CFG_FLAGS := -DENABLE_TREE_BUILD=1 -DENABLE_TATICAL_NUKE=1
INTERPRETER_FLAGS := -DENABLE_EVALUATED_EXPRESSIONS=1
TEST_FLAGS := -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1

########
# Source file definitions
SRC_FILES_DEBUG_LOGGING := logging/logging.cc debugging/debug_logging.cc
SRC_FILES_DEBUG_TOKENS := logging/logging.cc tokens/token.cc debugging/debug_tokens.cc
SRC_FILES_DEBUG_SCANNER := logging/logging.cc tokens/token.cc scanner/scanner.cc debugging/debug_scanner.cc
SRC_FILES_DEBUG_AST := logging/logging.cc tokens/token.cc scanner/scanner.cc cfg/context_free_grammar.cc parser/parser.cc ast/abstraction_tree_syntax.cc debugging/debug_ast.cc
SRC_FILES_DEBUG_PARSER := logging/logging.cc tokens/token.cc parser/parser.cc scanner/scanner.cc cfg/context_free_grammar.cc debugging/debug_parser.cc
SRC_FILES_DEBUG_INTERPRETER := logging/logging.cc tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc \
			       interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
			       interpreter/language_specific_truthy_operations.cc interpreter/interpreter.cc debugging/debug_interpreter.cc

SRC_FILES_TEST_LOGGING := logging/logging.cc tests/test_logging.cc
SRC_FILES_TEST_TOKENS := logging/logging.cc tokens/token.cc tests/test_token.cc
SRC_FILES_TEST_SCANNER := logging/logging.cc tokens/token.cc scanner/scanner.cc tests/test_scanner.cc
SRC_FILES_TEST_AST := logging/logging.cc tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc ast/abstraction_tree_syntax.cc scanner/scanner.cc tests/test_ast.cc
SRC_FILES_TEST_PARSER := logging/logging.cc tokens/token.cc scanner/scanner.cc tests/test_parser.cc
SRC_FILES_TEST_INTERPRETER := logging/logging.cc tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc interpreter/interpreter.cc \
			      interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
			      interpreter/language_specific_truthy_operations.cc tests/test_interpreter.cc

SRC_FILES_INTERPRETER := logging/logging.cc tokens/token.cc scanner/scanner.cc ast/abstraction_tree_syntax.cc cfg/context_free_grammar.cc parser/parser.cc \
                         interpreter/interpreter.cc interpreter/language_specific_unary_operations.cc \
                         interpreter/language_specific_binary_operations.cc interpreter/language_specific_truthy_operations.cc \
                         main.cc

# Convert source files to object files
OBJ_FILES_DEBUG_LOGGING := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_LOGGING))
OBJ_FILES_DEBUG_TOKENS := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_TOKENS))
OBJ_FILES_DEBUG_SCANNER := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_SCANNER))
OBJ_FILES_DEBUG_AST := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_AST))
OBJ_FILES_DEBUG_PARSER := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_PARSER))
OBJ_FILES_DEBUG_INTERPRETER := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_INTERPRETER))

OBJ_FILES_TEST_LOGGING := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_LOGGING))
OBJ_FILES_TEST_TOKENS := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_TOKENS))
OBJ_FILES_TEST_SCANNER := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_SCANNER))
OBJ_FILES_TEST_AST := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_AST))
OBJ_FILES_TEST_PARSER := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_PARSER))
OBJ_FILES_TEST_INTERPRETER := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_INTERPRETER))

OBJ_FILES_INTERPRETER := $(patsubst %.cc,%.o,$(SRC_FILES_INTERPRETER))

# All binaries
BINARIES := exec_debug_logging exec_debug_tokens exec_debug_scanner exec_debug_ast \
            exec_debug_parser exec_debug_interpreter exec_test_logging exec_test_tokens \
            exec_test_scanner exec_test_ast exec_test_parser exec_test_interpreter \
            exec_interpreter

.PHONY: all clean

all: $(BINARIES)

# Special compilation rules
cfg/context_free_grammar.o: cfg/context_free_grammar.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(CFG_FLAGS) -c $< -o $@

interpreter/interpreter.o: interpreter/interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(INTERPRETER_FLAGS) -c $< -o $@

debugging/debug_ast.o: debugging/debug_ast.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEBUG_AST_FLAGS) -c $< -o $@

debugging/debug_interpreter.o: debugging/debug_interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEBUG_INTERPRETER_FLAGS) -c $< -o $@

debugging/debug_parser.o: debugging/debug_parser.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_FLAGS) -c $< -o $@

main.o: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_FLAGS) -c $< -o $@

tests/test_%.o: tests/test_%.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(TEST_FLAGS) -c $< -o $@

# Default object compilation
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Debug executables
exec_debug_logging: $(OBJ_FILES_DEBUG_LOGGING)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

exec_debug_tokens: $(OBJ_FILES_DEBUG_TOKENS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

exec_debug_scanner: $(OBJ_FILES_DEBUG_SCANNER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

exec_debug_ast: $(OBJ_FILES_DEBUG_AST)
	$(CXX) $(CXXFLAGS) $(DEBUG_AST_FLAGS) $(INCLUDES) $^ -o $@

exec_debug_parser: $(OBJ_FILES_DEBUG_PARSER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

exec_debug_interpreter: $(OBJ_FILES_DEBUG_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

# Test executables
exec_test_logging: $(OBJ_FILES_TEST_LOGGING)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_tokens: $(OBJ_FILES_TEST_TOKENS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_scanner: $(OBJ_FILES_TEST_SCANNER)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_ast: $(OBJ_FILES_TEST_AST)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_parser: $(OBJ_FILES_TEST_PARSER)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_interpreter: $(OBJ_FILES_TEST_INTERPRETER)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Main interpreter executable
exec_interpreter: $(OBJ_FILES_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

clean:
	rm -f $(patsubst %.cc,%.o,$(SRC_FILES_INTERPRETER))
	rm -f $(BINARIES)
