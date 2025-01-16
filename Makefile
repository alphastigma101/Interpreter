# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++23 
LDFLAGS := -L $(HOME)/Interpreter/tests -lgtest -lgtest_main -pthread

# Include directories
INCLUDES := -I types/ -I logging/ -I catch/ -I tokens/ -I interface/ -I ast/ -I cfg/ -I declarations/ -I runtime/ -I interpreter/ -I scanner/ \
			-I parser/ -I threading/ -I environment/ -I tacticalNuke/ \
			-I resolver/ -I stack/

########
# Compiler flags for specific components
ENABLE_LOGGING := -D ENABLE_LOGGING=1
ENABLE_VISITOR_PATTERN := -D ENABLE_VISITOR_PATTERN=1
DISABLE_VISITOR_PATTERN := -D ENABLE_VISITOR_PATTERN=0
ENABLE_COMPILER := -D ENABLE_COMPILER=1

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
SRC_FILES_TEST_RUNTIME := tests/test_runtime.cc
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
SRC_FILES_TEST_STACK := tokens/token.cc stack/user_stack.cc tests/test_user_stack.cc
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
# Convert source files to object files
OBJ_FILES_DEBUG_TOKENS := $(SRC_FILES_DEBUG_TOKENS:.cc=.o)
OBJ_FILES_DEBUG_SCANNER := $(SRC_FILES_DEBUG_SCANNER:.cc=.o)
OBJ_FILES_DEBUG_AST := $(SRC_FILES_DEBUG_AST:.cc=.o)
OBJ_FILES_DEBUG_PARSER := $(SRC_FILES_DEBUG_PARSER:.cc=.o)
OBJ_FILES_DEBUG_STACK := $(SRC_FILES_DEBUG_STACK:.cc=.o)
OBJ_FILES_DEBUG_RESOLVER := $(SRC_FILES_DEBUG_RESOLVER:.cc=.o)
OBJ_FILES_DEBUG_INTERPRETER := $(SRC_FILES_DEBUG_INTERPRETER:.cc=.o)

OBJ_FILES_TEST_TOKENS := $(SRC_FILES_TEST_TOKENS:.cc=.o)
OBJ_FILES_TEST_RUNTIME := $(SRC_FILES_TEST_RUNTIME:.cc=.o)
OBJ_FILES_TEST_SCANNER := $(SRC_FILES_TEST_SCANNER:.cc=.o)
OBJ_FILES_TEST_AST := $(SRC_FILES_TEST_AST:.cc=.o)
OBJ_FILES_TEST_PARSER := $(SRC_FILES_TEST_PARSER:.cc=.o)
OBJ_FILES_TEST_BINARY := $(SRC_FILES_TEST_BINARY:.cc=.o)
OBJ_FILES_TEST_UNARY := $(SRC_FILES_TEST_UNARY:.cc=.o)
OBJ_FILES_TEST_TRUTHY := $(SRC_FILES_TEST_TRUTHY:.cc=.o)
OBJ_FILES_TEST_TACTICALNUKE := $(SRC_FILES_TEST_TACTICALNUKE:.cc=.o)
OBJ_FILES_TEST_STACK := $(SRC_FILES_TEST_STACK:.cc=.o)
OBJ_FILES_TEST_RESOLVER := $(SRC_FILES_TEST_RESOLVER:.cc=.o)
OBJ_FILES_TEST_INTERPRETER := $(SRC_FILES_TEST_INTERPRETER:.cc=.o)

OBJ_FILES_INTERPRETER := $(SRC_FILES_INTERPRETER:.cc=.o)

# All binaries
BINARIES := exec_debug_tokens exec_debug_scanner exec_debug_ast \
            exec_debug_parser exec_debug_interpreter \
			exec_debug_stack exec_debug_resolver \
			exec_test_tokens exec_test_runtime exec_test_scanner exec_test_ast exec_test_parser \
			exec_test_binaryOperations exec_test_unaryOperations exec_test_truthyOperations \
			exec_test_tacticalnuke exec_test_stack exec_test_resolver \
			exec_test_interpreter exec_interpreter

.PHONY: all clean

all: $(BINARIES)

# Special compilation rules
cfg/context_free_grammar.o: cfg/context_free_grammar.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

environment/environment.o: environment/environment.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tacticalNuke/tacticalNuke.o: tacticalNuke/tactical_nuke.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

stack/user_stack.o: stack/user_stack.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

resolver/resolver.o: resolver/resolver.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

interpreter/interpreter.o: interpreter/interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

debugging/debug_abstraction_syntax_tree.o: debugging/debug_abstraction_syntax_tree.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c cfg/context_free_grammar.cc -o cfg/test_context_free_grammar.o 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

debugging/debug_parser.o: debugging/debug_parser.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

debugging/debug_environment.o: debugging/debug_environment.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

debugging/debug_interpreter.o: debugging/debug_interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

tests/test_token.o: tests/test_token.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_runtime.o: tests/test_runtime.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_scanner.o: tests/test_scanner.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_abstraction_syntax_tree.o: tests/test_abstraction_syntax_tree.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_parser.o: tests/test_parser.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_binaryOperations.o: tests/test_binaryOperations.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_unaryOperations.o: tests/test_unaryOperations.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_truthyOperations.o: tests/test_truthyOperations.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_environment.o: tests/test_environment.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_tacticalNuke.o: tests/test_tacticalNuke.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_user_stack.o: tests/test_user_stack.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_resolver.o: tests/test_resolver.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

tests/test_interpreter.o: tests/test_interpreter.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(ENABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

main.o: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DISABLE_VISITOR_PATTERN) -MMD -MP -c $< -o $@

# Add header dependency tracking
DEPS := $(OBJ_FILES_DEBUG_TOKENS:.o=.d) \
        $(OBJ_FILES_DEBUG_SCANNER:.o=.d) \
        $(OBJ_FILES_DEBUG_AST:.o=.d) \
        $(OBJ_FILES_DEBUG_PARSER:.o=.d) \
        $(OBJ_FILES_DEBUG_STACK:.o=.d) \
        $(OBJ_FILES_DEBUG_RESOLVER:.o=.d) \
        $(OBJ_FILES_DEBUG_INTERPRETER:.o=.d) \
        $(OBJ_FILES_TEST_TOKENS:.o=.d) \
        $(OBJ_FILES_TEST_RUNTIME:.o=.d) \
        $(OBJ_FILES_TEST_SCANNER:.o=.d) \
        $(OBJ_FILES_TEST_AST:.o=.d) \
        $(OBJ_FILES_TEST_PARSER:.o=.d) \
        $(OBJ_FILES_TEST_BINARY:.o=.d) \
        $(OBJ_FILES_TEST_UNARY:.o=.d) \
        $(OBJ_FILES_TEST_TRUTHY:.o=.d) \
        $(OBJ_FILES_TEST_TACTICALNUKE:.o=.d) \
        $(OBJ_FILES_TEST_STACK:.o=.d) \
        $(OBJ_FILES_TEST_RESOLVER:.o=.d) \
        $(OBJ_FILES_TEST_INTERPRETER:.o=.d) \
        $(OBJ_FILES_INTERPRETER:.o=.d)

-include $(DEPS)

# Default object compilation
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

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

exec_test_runtime: $(OBJ_FILES_TEST_RUNTIME)
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
	$(CXX) $(CXXFLAGS) cfg/test_context_free_grammar.o  $^ -o $@ $(LDFLAGS)

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
	rm -f *.o *.d debugging/*.o debugging/*.d ast/*.o ast/*.d cfg/*.o cfg/*.d \
		tests/*.o tests/*.d parser/*.o parser/*.d tokens/*.o tokens/*.d \
		scanner/*.o scanner/*.d environment/*.o environment/*.d main.o main.d $(BINARIES)

