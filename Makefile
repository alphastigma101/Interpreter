# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++23 
LDFLAGS := -L $(HOME)/Interpreter/tests -lgtest -lgtest_main -pthread

# Include directories
INCLUDES := -I types/ -I logging/ -I catch/ -I tokens/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I definitions/ -I runtime/ -I interpreter/ -I scanner/ \
			-I parser/ -I threading/ -I environment/ -I tacticalNuke/ \
			-I resolver/ -I stack/

########
# Compiler flags for specific components
ENABLE_LOGGING := -D ENABLE_LOGGING=1
ENABLE_VISITOR_PATTERN := -D ENABLE_VISITOR_PATTERN=1
DISABLE_VISITOR_PATTERN := -D ENABLE_VISITOR_PATTERN=0

########
# Source file definitions
SRC_FILES_DEBUG_TOKENS := tokens/token.cc debugging/debug_tokens.cc
SRC_FILES_DEBUG_SCANNER := tokens/token.cc scanner/scanner.cc debugging/debug_scanner.cc
SRC_FILES_DEBUG_AST := tokens/token.cc scanner/scanner.cc parser/parser.cc ast/abstraction_tree_syntax.cc debugging/debug_abstraction_syntax_tree.cc
SRC_FILES_DEBUG_PARSER := tokens/token.cc parser/parser.cc scanner/scanner.cc debugging/debug_parser.cc
#SRC_FILES_DEBUG_ENV := tokens/token.cc tacticalNuke/tactical_nuke.cc environment/environment.cc debugging/debug_environment.cc
SRC_FILES_DEBUG_RESOLVER := tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc \
			       interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
				   environment/environment.cc tacticalNuke/tactical_nuke.cc stack/user_stack.cc resolver/resolver.cc \
			       interpreter/language_specific_truthy_operations.cc interpreter/interpreter.cc debugging/debug_resolver.cc 
SRC_FILES_DEBUG_STACK := stack/user_stack.cc debugging/debug_user_stack.cc 
SRC_FILES_DEBUG_INTERPRETER := tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc \
			       interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
				   environment/environment.cc tacticalNuke/tactical_nuke.cc stack/user_stack.cc resolver/resolver.cc \
			       interpreter/language_specific_truthy_operations.cc interpreter/interpreter.cc debugging/debug_interpreter.cc


SRC_FILES_TEST_TOKENS := tokens/token.cc tests/test_token.cc
SRC_FILES_TEST_SCANNER := tokens/token.cc scanner/scanner.cc tests/test_scanner.cc
SRC_FILES_TEST_AST :=  tokens/token.cc parser/parser.cc ast/abstraction_tree_syntax.cc scanner/scanner.cc tests/test_abstraction_tree_syntax.cc
SRC_FILES_TEST_PARSER := tokens/token.cc scanner/scanner.cc parser/parser.cc tests/test_parser.cc
#SRC_FILES_TEST_ENV := environment/environment.cc tests/test_environment.cc
SRC_FILES_TEST_BINARY := tokens/token.cc parser/parser.cc scanner/scanner.cc interpreter/language_specific_binary_operations.cc tests/test_binaryOperations.cc
SRC_FILES_TEST_UNARY := tokens/token.cc parser/parser.cc scanner/scanner.cc interpreter/language_specific_unary_operations.cc tests/test_unaryOperations.cc
SRC_FILES_TEST_TRUTHY := tokens/token.cc parser/parser.cc scanner/scanner.cc interpreter/language_specific_truthy_operations.cc tests/test_truthyOperations.cc
SRC_FILES_TEST_TACTICALNUKE :=  tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc \
			       interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
				   environment/environment.cc tacticalNuke/tactical_nuke.cc stack/user_stack.cc resolver/resolver.cc \
			       interpreter/language_specific_truthy_operations.cc interpreter/interpreter.cc tests/test_tacticalNuke.cc
SRC_FILES_TEST_STACK := stack/user_stack.cc tests/test_user_stack.cc
SRC_FILES_TEST_RESOLVER := tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc \
			       interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
				   environment/environment.cc tacticalNuke/tactical_nuke.cc stack/user_stack.cc resolver/resolver.cc \
			       interpreter/language_specific_truthy_operations.cc interpreter/interpreter.cc \
				   resolver/resolver.cc tests/test_resolver.cc
SRC_FILES_TEST_INTERPRETER := tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc \
			       interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
				   environment/environment.cc tacticalNuke/tactical_nuke.cc stack/user_stack.cc resolver/resolver.cc \
			       interpreter/language_specific_truthy_operations.cc interpreter/interpreter.cc tests/test_interpreter.cc



# Create an executable that runs the actual interpreter
SRC_FILES_INTERPRETER := tokens/token.cc cfg/context_free_grammar.cc parser/parser.cc scanner/scanner.cc \
			       interpreter/language_specific_unary_operations.cc interpreter/language_specific_binary_operations.cc \
				   environment/environment.cc tacticalNuke/tactical_nuke.cc stack/user_stack.cc resolver/resolver.cc \
			       interpreter/language_specific_truthy_operations.cc interpreter/interpreter.cc \
				   main.cc

# Convert source files to object files
OBJ_FILES_DEBUG_TOKENS := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_TOKENS))
OBJ_FILES_DEBUG_SCANNER := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_SCANNER))
OBJ_FILES_DEBUG_AST := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_AST))
OBJ_FILES_DEBUG_PARSER := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_PARSER))
#OBJ_FILES_DEBUG_ENV := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_ENV))
OBJ_FILES_DEBUG_STACK := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_STACK))
OBJ_FILES_DEBUG_RESOLVER := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_RESOLVER))
OBJ_FILES_DEBUG_INTERPRETER := $(patsubst %.cc,%.o,$(SRC_FILES_DEBUG_INTERPRETER))


OBJ_FILES_TEST_TOKENS := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_TOKENS))
OBJ_FILES_TEST_SCANNER := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_SCANNER))
OBJ_FILES_TEST_AST := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_AST))
OBJ_FILES_TEST_PARSER := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_PARSER))
OBJ_FILES_TEST_BINARY := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_BINARY))
OBJ_FILES_TEST_UNARY := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_UNARY))
OBJ_FILES_TEST_TRUTHY := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_TRUTHY))
#OBJ_FILES_TEST_ENV := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_ENV))
OBJ_FILES_TEST_TACTICALNUKE := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_TACTICALNUKE))
OBJ_FILES_TEST_STACK := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_STACK))
OBJ_FILES_TEST_RESOLVER := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_RESOLVER))
OBJ_FILES_TEST_INTERPRETER := $(patsubst %.cc,%.o,$(SRC_FILES_TEST_INTERPRETER))

OBJ_FILES_INTERPRETER := $(patsubst %.cc,%.o,$(SRC_FILES_INTERPRETER))

# All binaries
BINARIES := exec_debug_tokens exec_debug_scanner exec_debug_ast \
            exec_debug_parser exec_debug_interpreter \
			exec_debug_stack exec_debug_resolver \
			exec_test_tokens exec_test_scanner exec_test_ast exec_test_parser \
			exec_test_binaryOperations exec_test_unaryOperations exec_test_truthyOperations \
			exec_test_tacticalnuke exec_test_stack exec_test_resolver \
			exec_test_interpreter exec_interpreter

.PHONY: all clean

all: $(BINARIES)

# Special compilation rules
cfg/context_free_grammar.o: cfg/context_free_grammar.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -c $< -o $@

environment/environment.o: environment/environment.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tacticalNuke/tacticalNuke.o: tacticalNuke/tactical_nuke.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

stack/user_stack.o: stack/user_stack.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

resolver/resolver.o: resolver/resolver.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -c $< -o $@

interpreter/interpreter.o: interpreter/interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -c $< -o $@

debugging/debug_abstraction_syntax_tree.o: debugging/debug_abstraction_syntax_tree.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c cfg/context_free_grammar.cc -o cfg/test_context_free_grammar.o 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

debugging/debug_parser.o: debugging/debug_parser.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

debugging/debug_environment.o: debugging/debug_environment.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

debugging/debug_interpreter.o: debugging/debug_interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

tests/test_token.o: tests/test_token.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_scanner.o: tests/test_scanner.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_abstraction_syntax_tree.o: tests/test_abstraction_syntax_tree.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_parser.o: tests/test_parser.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_binaryOperations.o: tests/test_binaryOperations.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_unaryOperations.o: tests/test_unaryOperations.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_truthyOperations.o: tests/test_truthyOperations.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_environment.o: tests/test_environment.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_tacticalNuke.o: tests/test_tacticalNuke.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_user_stack.o: tests/test_user_stack.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_resolver.o: tests/test_resolver.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -c $< -o $@

tests/test_interpreter.o: tests/test_interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -c $< -o $@

main.o: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -c $< -o $@

# Default object compilation
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Debug executables

exec_debug_tokens: $(OBJ_FILES_DEBUG_TOKENS)
	$(CXX) $(CXXFLAGS) $^ -o $@

exec_debug_scanner: $(OBJ_FILES_DEBUG_SCANNER)
	$(CXX) $(CXXFLAGS) $^ -o $@

exec_debug_ast: $(OBJ_FILES_DEBUG_AST)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@

exec_debug_parser: $(OBJ_FILES_DEBUG_PARSER)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@

#exec_debug_environment: $(OBJ_FILES_DEBUG_ENV)

exec_debug_stack: $(OBJ_FILES_DEBUG_STACK)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

exec_debug_resolver: $(OBJ_FILES_DEBUG_RESOLVER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ 
	
exec_debug_interpreter: $(OBJ_FILES_DEBUG_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

exec_test_tokens: $(OBJ_FILES_TEST_TOKENS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_scanner: $(OBJ_FILES_TEST_SCANNER)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_ast: $(OBJ_FILES_TEST_AST)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@ $(LDFLAGS)

exec_test_parser: $(OBJ_FILES_TEST_PARSER)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@ $(LDFLAGS)

exec_test_binaryOperations: $(OBJ_FILES_TEST_BINARY)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@ $(LDFLAGS)

exec_test_unaryOperations: $(OBJ_FILES_TEST_UNARY)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@ $(LDFLAGS)

exec_test_truthyOperations: $(OBJ_FILES_TEST_TRUTHY)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@ $(LDFLAGS)

#exec_test_environment: $(OBJ_FILES_TEST_ENV)

exec_test_tacticalnuke: $(OBJ_FILES_TEST_TACTICALNUKE)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_stack: $(OBJ_FILES_TEST_STACK)
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o $^ -o $@ $(LDFLAGS)

exec_test_resolver: $(OBJ_FILES_TEST_RESOLVER)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

exec_test_interpreter: $(OBJ_FILES_TEST_INTERPRETER)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Main interpreter executable
exec_interpreter: $(OBJ_FILES_INTERPRETER)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

clean:
	rm -f $(patsubst %.cc,%.o,$(SRC_FILES_INTERPRETER))
	rm -f *.o debugging/*.o ast/*.o cfg/*.o tests/*.o main.o $(BINARIES)

