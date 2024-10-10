#!bin/bash 

INCLUDE=" -I ../types/ -I ../logging/ -I ../asm/ -I ../catch/ -I ../tokens/ -I ../languages/ -I ../interface/ -I ../ast/ -I ../cfg/ -I 
             ../declarations/ -I ../definitions/ -I ../runtime/ -I ../interpreter/ -I ../scanner/ -I ../parser/ -I ../addon/ -I ../threading/ -I ../compiler/"
LDFLAGS=" -L $HOME/Public-Projects/logging -lgtest -lgtest_main -pthread"

#echo "creating debugging object files and executables"
g++ -g -w -std=c++17 -fconcepts -DRADNOM_EXTENSIONS=0 $INCLUDE  -c ../logging/logging.cc -o logging.o 
#g++ -g -std=c++17 -fconcepts $INCLUDE -c debug_logging.cc -o debug_logging.o
#g++ -g -DRADNOM_EXTENSIONS=0 -DENABLE_TESTING=1 debug_logging.o logging.o -o exec_debug_logging
#echo "Creating test object files and executables" 
#g++ -g -std=c++17 -fconcepts -D RADNOM_EXTENSIONS=0 -D ENABLE_TESTING=1 $INCLUDE -c ../tests/test_logging.cc -o test_logging.o 
#echo "Linking the test object files together for the logger"
#g++ -g -std=c++17 test_logging.o logging.o -o test_logging $LDFLAGS


#echo "Creating debugging object files and executables"
g++ -g -std=c++17 -fconcepts $INCLUDE -c ../languages/languages.cc -o languages.o
#g++ -g -std=c++17 -fconcepts -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST -DENABLE_GENERATION=1 $INCLUDE -c debug_languages.cc -o debug_languages.o
#g++ -g -std=c++17 debug_languages.o languages.o logging.o -o exec_debug_languages
#g++ -g -std=c++17 -fconcepts -DENABLE_TESTING=1 -DENABLE_GENERATION=1 -DENABLE_LOGGING_TEST $INCLUDE -c ../tests/test_languages.cc -o test_languages.o
#g++ -g -std=c++17 test_languages.o languages.o logging.o -o test_languages $LDFLAGS


#echo "Creating debugging object files and executables for token"
g++ -g -std=c++17 -fconcepts  $INCLUDE -c ../tokens/token.cc -o token.o
#g++ -g -std=c++17 -DENABLE_LOGGING_TEST -c debug_tokens.cc -o debug_tokens.o
#g++ -g -std=c++17 token.o debug_tokens.o languages.o logging.o -o exec_debug_tokens
#g++ -g -std=c++17 -fconcepts -DENABLE_LOGGING_TEST $INCLUDE -c ../tests/test_token.cc -o test_token.o 
#g++ -g -std=c++17 test_token.o token.o languages.o logging.o -o test_tokens $LDFLAGS

#echo "Creating debuging object files and executables for scanner"
g++ -g -std=c++17 -fconcepts $INCLUDE -c ../scanner/scanner.cc -o scanner.o
#g++ -g -std=c++17 -DENABLE_LOGGING_TEST $INCLUDE -c debug_scanner.cc -o debug_scanner.o
#g++ -g -std=c++17 token.o scanner.o languages.o logging.o debug_scanner.o -o exec_debug_scanner 
#g++ -g -std=c++17 -DENABLE_LOGGING_TEST=1 $INCLUDE -c ../tests/test_scanner.cc -o test_scanner.o
#g++ -g -std=c++17 test_scanner.o token.o scanner.o languages.o logging.o -o test_scanner $LDFLAGS

echo "Building the expression types object files"
g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_TREE_BUILD=1 -c ../cfg/context_free_grammar.cc -o context_free_grammar.o


echo "Build object file for parser.cc"
g++ -w -g -std=c++17 -fconcepts $INCLUDE -c ../parser/parser.cc -o parser.o

echo "Creating debugging object files and executables for ast"
g++ -g -std=c++17 -fconcepts $INCLUDE -c ../ast/abstraction_tree_syntax.cc -o abstraction_tree_syntax.o 
g++ -g -std=c++17 -fconcepts -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1 -DENABLE_TREE_DEBUGGING=1 $INCLUDE  -c ../debugging/debug_ast.cc -o debug_abstraction_tree_syntax.o 
g++ -g -std=c++17 -fconcepts parser.o context_free_grammar.o scanner.o abstraction_tree_syntax.o languages.o token.o logging.o debug_abstraction_tree_syntax.o -o exec_debug_abstraction_tree_syntax
#g++ -g -std=c++17 -fconcepts $INCLUDE -c ../tests/test_ast.cc -o test_abstraction_tree_syntax.o 
#g++ -g -std=c++17 -fconcepts -D RADNOM_EXTENSIONS=0 scanner.o test_abstraction_tree_syntax.o abstraction_tree_syntax.o languages.o token.o logging.o -o test_abstraction_tree_syntax $LDFLAGS

#echo "Creating debugging object files and executables for parser"
#g++ -g -std=c++17 -fconcepts -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1 $INCLUDE -c ../debugging/debug_parser.cc -o debug_parser.o
#g++ -g -std=c++17 -fconcepts context_free_grammar.o token.o scanner.o abstraction_tree_syntax.o parser.o  languages.o logging.o debug_parser.o -o exec_debug_parser
#g++ -g -std=c++17 -fconcepts -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1 $INCLUDE -c ../tests/test_parser.cc -o test_parser.o
#g++ -g -std=c++17 -fconcepts context_free_grammar.o scanner.o abstraction_tree_syntax.o parser.o languages.o token.o logging.o test_parser.o -o test_parser $LDFLAGS

#echo "Creating debugging object files and executables for truthy"
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_GENERATION=1 -c ../interpreter/language_specific_truthy_operations.cc -o language_specific_truthy_operations.o 
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_LOGGING_TEST=1 -DENABLE_GENERATION=1 -DENABLE_TESTING=1 -c ../debugging/debug_truthy.cc -o debug_language_specific_truthy_operations.o
#g++ -g -std=c++17 -fconcepts language_specific_truthy_operations.o languages.o token.o logging.o debug_language_specific_truthy_operations.o -o exec_debug_truthy
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_LOGGING_TEST=1 -DENABLE_GENERATION=1 -DENABLE_TESTING=1 -c ../tests/test_truthy.cc -o test_truthy.o
#g++ -g -std=c++17 -fconcepts language_specific_truthy_operations.o languages.o token.o logging.o test_truthy.o -o test_truthy $LDFLAGS


#echo "Creating debugging object files and executables for unary"
#g++ -g -std=c++17 -fconcepts $INCLUDE -c ../interpreter/language_specific_unary_operations.cc -o language_specific_unary_operations.o 
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_GENERATION=1 -c ../debugging/debug_unary.cc -o debug_language_specific_unary_operations.o
#g++ -g -std=c++17 -fconcepts language_specific_unary_operations.o languages.o token.o logging.o debug_language_specific_unary_operations.o -o exec_debug_unary
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_GENERATION=1 -c ../tests/test_unary.cc -o test_unary.o
#g++ -g -std=c++17 -fconcepts -D RADNOM_EXTENSIONS=0 language_specific_unary_operations.o languages.o token.o logging.o test_unary.o -o test_unary $LDFLAGS


#echo "Creating debugging object files and executables for binary"
#g++ -g -std=c++17 -fconcepts $INCLUDE -c ../interpreter/language_specific_binary_operations.cc -o language_specific_binary_operations.o 
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_GENERATION=1 -DENABLE_TESTING=1 -c ../debugging/debug_binary.cc -o debug_language_specific_binary_operations.o
#g++ -g -std=c++17 -fconcepts language_specific_binary_operations.o languages.o token.o logging.o debug_language_specific_binary_operations.o -o exec_debug_binary
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_GENERATION=1 -c ../tests/test_binary.cc -o test_binary.o
#g++ -g -std=c++17 -fconcepts language_specific_binary_operations.o languages.o token.o logging.o test_binary.o -o test_binary $LDFLAGS


echo "Creating debugging object files and executables for interpreter"
#g++ -g -std=c++17 -fconcepts  $INCLUDE -c ../interpreter/interpreter.cc -o interpreter.o 
#g++ -g -std=c++17 -fconcepts $INCLUDE  -DENABLE_TESTING=1 -DENABLE_LOGGING_TEST=1  -c ../debugging/debug_interpreter.cc -o debug_interpreter.o
#g++ -g -std=c++17 -fconcepts scanner.o parser.o context_free_grammar.o abstraction_tree_syntax.o interpreter.o language_specific_truthy_operations.o language_specific_unary_operations.o language_specific_binary_operations.o languages.o token.o logging.o  debug_interpreter.o -o exec_debug_interpreter
#g++ -g -std=c++17 -fconcepts $INCLUDE -DENABLE_GENERATION=1 -DENABLE_TESTING=1 -c ../tests/test_interpreter.cc -o test_interpreter.o
#g++ -g -std=c++17 -fconcepts interpreter.o languages.o token.o logging.o test_interpreter.o unary.o binary.o truthy.o -o test_truthy $LDFLAGS
