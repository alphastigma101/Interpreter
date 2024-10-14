#pragma once
#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include <any>
#include <variant>
#include <set>
#include <tuple>
#include <memory>
#include <unordered_map>
#include <map>
#include <iostream>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <functional>
#include <iomanip>
#include <atomic>
#include <mutex>
#include <thread>
#include <addon.h>
/** --------------------------------------------------------------------------
 * @brief All this alias templates are needed to avoid 
 *        using namespace std repetiviely which will make the code look more cleaner.
 * ---------------------------------------------------------------------------       
*/        
typedef std::string String;
template<typename K, typename V>
// Containers
using Map = std::map<K, V>;
template<typename K, typename V>
using Unordered = std::unordered_map<K, V>;
template<typename... T>
using Variant = std::variant<T...>;
template<typename T>
using Vector = std::vector<T>;
template<typename T>
// Pointers
using Shared = std::shared_ptr<T>;
template<typename T>
using Unique = std::unique_ptr<T>;
template<typename T>
using Weak = std::weak_ptr<T>;
// Threading/Atomic/Mutex
template<typename T>
using Atomic = std::atomic<T>;
using Any = std::any;
template<typename T>
using Set = std::set<T>;
/** --------------------------------------------------------------------------
 * @brief Initialized in main.cc and is copy-initialized in abstraction_syntax_tree.cc
 * ---------------------------------------------------------------------------
*/
extern String user_choice;
extern String file_name;
/** ---------------------------------------------------------------------------
 * @brief Defined in context_free_grammar.h
 *
 * @details This is a forward declaration which will be very useful for later on.
 *
 * --------------------------------------------------------------------------
*/
namespace ContextFreeGrammar {
    class Expr;
    class Binary;
    class Unary;
    class Grouping;
    class Literal;
    class Statement;
    class Variable;
    class Methods;
    class Arguments;
    class EcoSystem;
};
/** ---------------------------------------------------------------------------
 * @brief defined in parser.h 
 * 
 * @details The parser I am making is a top-down parser. 
 *          Meaning it starts at the top, and works it's way down the grammar
 * 
 * @details The precendence are in reverse, because the lower precendence might contain higher precendence.
 *          That means 
 *
 * ---------------------------------------------------------------------------
*/
namespace Parser {
    template<class Derived>
    class parseError;
    class parser;
};
/** --------------------------------------------------------------------------
 * @brief A forward declaration of the namespace Interpreter
 * 
 * ---------------------------------------------------------------------------
*/
namespace Interpreter {
    class interpreter;
};
extern Vector<String> evaluatedExpressions;
extern int evalExprSize;
namespace UnaryOperations {
    class unaryOperations;
};
namespace BinaryOperations {
    class binaryOperations;
};
namespace MethodOperations {
    class methodOperations;
};
namespace ArgumentOperations {
    class argumentOperations;
};
/** ---------------------------------------------------------------------------
 * @details 'ExprTypes' used alot in parser.cc and context_free_grammar.h
 *                      Needed for returning multiple user defined class instances
 *
 * @brief Details that explain the custom data structures and there purpose
 *
 * @details 'astTree' Represents a tree structure with a type T, a pair of type U and Shared<V>
 * @details 'Vertices' Known as nodes which represent the lines/links of a directed/undirected graph
 *                     It will use templates so it can be reused somewhere in the codebase if needed
 * @details 'Vertex' Known as the dot/point in a directed/undirected graph
 *                   It will use templates so it can be reused somewhere else in the codebase if needed
 * ---------------------------------------------------------------------------
*/
template<typename... Derived>
using ExprTypes = Shared<Derived...>;
using ExprVariant = Variant<ContextFreeGrammar::Expr*, Unique<ContextFreeGrammar::Expr>>;
template<typename T, typename U, typename V>
using astTree = std::tuple<T, std::pair<U, V>>;
template<typename T, typename U, typename V>
extern astTree<T, U, V> compressedAstTree(T first, U second, V third);
extern Set<astTree<int, String, ExprVariant>> cTree;
//template<typename X, typename Y, typename Z>
//using Vertices =
//template<typename X, typename Y, typename Z>
//using Vertex = std::tuple<

namespace Logging {
    template<typename Derived>
    class logging;
};
/** ---------------------------------------------------------------------------
 * @brief static logger. It is used by every single concrete class that is avialable
 *
 * @details Use grep -R 'logEntries' <root-path> replace root-path that will search through all the files that have logEntries  
 * ---------------------------------------------------------------------------
*/
template<typename T>
using logTable = T;
extern logTable<std::map<std::string, std::vector<std::string>>> logEntries; 
/**---------------------------------------------------------------------------
 * @brief Used to create a specific file with a specific extension. Is used  by interpreter.cc 
 * ---------------------------------------------------------------------------
*/
typedef std::map<String, std::pair<String, String>> Table;
static Table initTable(const Unordered<String, Vector<String>> languageExtensions, const Unordered<std::string, String> downloads);

#include <enum_types.h>

#endif 
