#ifndef _DECLARATIONS_H_
#define _DECLARATIONS_H_
#include <variant>
#include <set>
#include <tuple>
#include <list>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <typeinfo>
#include <functional>
#include <atomic>
#include <mutex>
#include <thread>
#include <addon.h>
#include <interface.h>
#include <logging.h>
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
using List = std::list<T>;

// Pointers
template<typename T>
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
    class Logical;
    class Grouping;
    class Literal;
    class Assign;
    class Variable;
    class Functions;
    class Call;
    class Statement;
    class Print;
    class Expression;
    class If;
    class Return;
    class Var;
    class While;
    class Block;
    class Methods;
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
/** ---------------------------------------------------------------------------
 * @brief defined in abstraction_tree_syntax.h
 * 
 * @details A codebase that prints out the ast in a string format 
 * 
 * @details Will be useful for test cases, debugging, and or the compiler 
 *
 * ---------------------------------------------------------------------------
*/
namespace AbstractionTreeSyntax {
    template<class Derived>
    class generateAst;
    class ast;
};
/** --------------------------------------------------------------------------
 * @brief A forward declaration of the namespace Interpreter
 * 
 * ---------------------------------------------------------------------------
*/
namespace Interpreter {
    class interpreter;
};
namespace Resolver {
    class resolver;
};
namespace UnaryOperations {
    class unaryOperations;
};
namespace BinaryOperations {
    class binaryOperations;
};
namespace Environment {
    class environment;
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
//template<typename X, typename Y, typename Z>
//using Vertices =
//template<typename X, typename Y, typename Z>
//using Vertex = std::tuple<

namespace Logging {
    template<typename Derived>
    class logging;
};
namespace Lists {
    class linkedList;
    struct Node;
};
namespace Stack {
    class stack;
};
#endif 
