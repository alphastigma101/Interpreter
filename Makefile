# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -fconcepts
LDFLAGS :=  -L $(HOME)/Public-Projects/tests -lgtest -lgtest_main -pthread

# Include directories
INCLUDES := -I ../types/ -I logging/ -I asm/ -I catch/ -I tokens/ \
            -I languages/ -I interface/ -I ast/ -I cfg/ \
            -I declarations/ -I definitions/ -I runtime/ -I interpreter/ \
            -I scanner/ -I parser/ -I threading/ -I compiler/

FEATURES := -DRADNOM_EXTENSIONS=0 -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1
########
# Variables for debugging the code
SRC_FILES_DEBUG_LOGGING := logging/logging.cc debugging/debug_logging.cc

SRC_FILES_DEBUG_TOKENS := logging/logging.cc tokens/token.cc debugging/debug_tokens.cc

SRC_FILES_DEBUG_SCANNER := logging/logging.cc tokens/token.cc scanner/scanner.cc debugging/debug_scanner.cc

SRC_FILES_DEBUG_AST := logging/logging.cc tokens/token.cc scanner/scanner.cc cfg/context_free_grammar.cc parser/parser.cc \
                       languages/languages.cc debugging/debug_ast.cc

SRC_FILES_DEBUG_PARSER := logging/logging.cc tokens/token.cc parser/parser.cc scanner/scanner.cc \
                         debugging/debug_parser.cc

SRC_FILES_DEBUG_INTERPRETER := logging/logging.cc tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc languages/languages.cc scanner/scanner.cc \
                         debugging/debug_interpreter.cc
########


########
# Variables for testing the code
SRC_FILES_TEST_LOGGING := logging/logging.cc debugging/test_logging.cc

SRC_FILES_TEST_TOKENS := logging/logging.cc tokens/token.cc debugging/test_tokens.cc

SRC_FILES_TEST_SCANNER := logging/logging.cc tokens/token.cc scanner/scanner.cc debugging/test_scanner.cc

SRC_FILES_TEST_AST := logging/logging.cc tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc ast/abstraction_syntax_tree.cc \
                      languages/languages.cc scanner/scanner.cc debugging/test_ast.cc

SRC_FILES_TEST_PARSER := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         debugging/test_parser.cc

SRC_FILES_TEST_INTERPRETER := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         debugging/test_interpreter.cc
########


########
# Variables for running the actual program
SRC_FILES_INTERPRETER := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         ast/abstraction_tree_syntax.cc parser/parser.cc \
                         interpreter/interpreter.cc interpreter/language_specific_unary_operations.cc \
                         interpreter/language_specific_binary_operations.cc interpreter/language_specific_truthy_operations.cc \
                         main.cc

# Source files for exec_generator
SRC_FILES_GENERATOR := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                       ast/abstraction_tree_syntax.cc parser/parser.cc \
                       interpreter/language_specific_unary_operations.cc \
                       interpreter/language_specific_binary_operations.cc interpreter/language_specific_truthy_operations.cc \
                       generate_code.cc
#########

#########
# Variables for running test cases
SRC_FILES_TEST_TOKENS := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         tests/test_tokens.cc

SRC_FILES_TEST_SCANNER := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         tests/test_scanner.cc

SRC_FILES_TEST_AST := logging/logging.cc tokens/token.cc languages/languages.cc scanner/scanner.cc \
                         ast/abstraction_tree_syntax.cc tests/test_ast.cc


SRC_FILES_TEST_PARSER := logging/logging.cc tokens/token.cc languages/languages.cc \
                         ast/abstraction_tree_syntax.cc parser/parser.cc \
                         tests/test_parser.cc

SRC_FILES_TEST_TRUTHY := logging/logging.cc tokens/token.cc languages/languages.cc \
                         interpreter/language_specific_truthy_operations.cc \
                         tests/test_truthy.cc

SRC_FILES_TEST_UNARY := logging/logging.cc tokens/token.cc languages/languages.cc \
                         interpreter/language_specific_unary_operations.cc \
                         tests/test_unary.cc

SRC_FILES_TEST_BINARY := logging/logging.cc tokens/token.cc languages/languages.cc \
                         interpreter/language_specific_binary_operations.cc \
                         tests/test_binary.cc

SRC_FILES_TEST_INTERPRETER := logging/logging.cc tokens/token.cc languages/languages.cc \
                         ast/abstraction_tree_syntax.cc interpreter/language_specific_unary_operations.cc \
                         interpreter/language_specific_binary_operations.cc interpreter/language_specific_truthy_operations.cc \
                         tests/test_interpreter.cc

# Object for debugging the code
#########
# Object files for exec_debug_logging
OBJ_FILES_DEBUG_LOGGING :=  $(patsubst %.cc, %.o, $(SRC_FILES_DEBUG_LOGGING))

# Object files for exec_debug_tokens
OBJ_FILES_DEBUG_TOKEN :=  $(patsubst %.cc, %.o, $(SRC_FILES_DEBUG_TOKEN))

# Object files for exec_debug_scanner
OBJ_FILES_DEBUG_SCANNER :=  $(patsubst %.cc, %.o, $(SRC_FILES_DEBUG_SCANNER))

# Object files for exec_debug_ast
OBJ_FILES_DEBUG_AST :=  $(patsubst %.cc, %.o, $(SRC_FILES_DEBUG_AST))

# Object files for exec_debug_parser
OBJ_FILES_DEBUG_PARSER :=  $(patsubst %.cc, %.o, $(SRC_FILES_DEBUG_PARSER))

# Object files for exec_debug_interpreter
OBJ_FILES_DEBUG_INTERPRETER :=  $(patsubst %.cc, %.o, $(SRC_FILES_DEBUG_INTERPRETER))

#########


# Object for testing the code
#########
# Object files for exec_test_logging
OBJ_FILES_TEST_LOGGING :=  $(patsubst %.cc, %.o, $(SRC_FILES_TEST_LOGGING))

# Object files for exec_test_tokens
OBJ_FILES_TEST_TOKEN :=  $(patsubst %.cc, %.o, $(SRC_FILES_TEST_TOKEN))

# Object files for exec_test_scanner
OBJ_FILES_TEST_SCANNER :=  $(patsubst %.cc, %.o, $(SRC_FILES_TEST_SCANNER))

# Object files for exec_test_ast
OBJ_FILES_TEST_AST :=  $(patsubst %.cc, %.o, $(SRC_FILES_TEST_AST))

# Object files for exec_test_parser
OBJ_FILES_TEST_PARSER :=  $(patsubst %.cc, %.o, $(SRC_FILES_TEST_PARSER))

# Object files for exec_test_interpreter
OBJ_FILES_TEST_INTERPRETER :=  $(patsubst %.cc, %.o, $(SRC_FILES_TEST_INTERPRETER))

#########


# Objects for running the actual program
#########
# Object files for exec_interpreter
OBJ_FILES_INTERPRETER := $(patsubst %.cc, %.o, $(SRC_FILES_INTERPRETER))

# Object files for exec_generator
OBJ_FILES_GENERATOR := $(patsubst %.cc, %.o, $(SRC_FILES_GENERATOR))

OBJ_FILES_TEST_SCANNER := $(patsubst %.cc, %.o, $(SRC_FILES_TEST_SCANNER))

########
# Executables
BINARIES := exec_debug_logging exec_debug_tokens exec_debug_scanner exec_debug_ast exec_debug_parser exec_debug_interpreter \
            exec_test_logging exec_test_tokens exec_test_scanner exec_test_ast exec_test parser exec_test_interpreter \
            exec_interpreter exec_generator 
#exec_vm exec_new_parser_rules

# PHONY targets
.PHONY: all clean

# Default target
all: $(BINARIES)

########
# Build the object files and executable for debugging code
# Build exec_debug_logging
exec_debug_logging: $(OBJ_FILES_DEBUG_LOGGING)
	$(CXX) -w $(CXXFLAGS) $(INCLUDES)  $^ -o $@

# Build exec_debug_tokens
exec_debug_tokens: $(OBJ_FILES_DEBUG_TOKENS)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@

# Build exec_debug_scanner
exec_debug_scanner: $(OBJ_FILES_DEBUG_SCANNER)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@

# Build exec_debug_ast
exec_debug_ast: $(OBJ_FILES_DEBUG_AST)
	$(CXX) -w $(CXXFLAGS) $(INCLUDES)  $^ -o $@

# Build exec_debug_parser
exec_debug_parser: $(OBJ_FILES_DEBUG_PARSER)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@

# Build exec_debug_interpreter
exec_debug_interpreter: $(OBJ_FILES_DEBUG_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@

########
# Build the object files and executable for testing code
# Build exec_test_logging
exec_test_logging: $(OBJ_FILES_TEST_LOGGING)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@ $(LDFLAGS)

# Build exec_test_tokens
exec_test_tokens: $(OBJ_FILES_TEST_TOKENS)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@ $(LDFLAGS)

# Build exec_test_scanner
exec_test_scanner: $(OBJ_FILES_TEST_SCANNER)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@

# Build exec_debug_ast
exec_test_scanner: $(OBJ_FILES_TEST_AST)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@

# Build exec_test_parser
exec_test_parser: $(OBJ_FILES_TEST_PARSER)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@ $(LDFLAGS)

# Build exec_test_interpreter
exec_test_interpreter: $(OBJ_FILES_TEST_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES)  $^ -o $@ $(LDFLAGS)


########
# Build the object files and executable for the program
# Build exec_interpreter
exec_interpreter: $(OBJ_FILES_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ 

# Build exec_generator
exec_generator: $(OBJ_FILES_GENERATOR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ 

# Build exec_vm
#exec_vm: config_vm.o compiler.o parser.o ast.o token.o
	#$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

########

# Generic rule for compiling .cc to .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up object files and binaries
clean:
	rm -f $(patsubst %.cc,%.o,$(SRC_FILES_INTERPRETER) $(SRC_FILES_GENERATOR))
	rm -f $(BINARIES)
