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
using MultiMap = std::multimap<K,V>;
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
namespace Test {
    class OperationsTest;
};
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
    class Class;
    class Get;
    class Set;
    class This;
    class Super;
    class Import;
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
namespace TruthyOperations {
    class binaryOperations;
};
namespace Environment {
    class environment;
};
namespace NuclearLang {
    class Nuke;
    template<class Derived>
    class NukeCallable;
    class NukeReturn;
    class NukeFunction;
    class NukeClass;
    class NukeInstance;
    class NukeProperties;
};
/** ---------------------------------------------------------------------------
 * @details 'ExprTypes' used alot in parser.cc and context_free_grammar.h
 *                      Needed for returning multiple user defined class instances
 *
 * @brief Details that explain the custom data structures and there purpose
 *
 * ---------------------------------------------------------------------------
*/
template<typename... Derived>
using ExprTypes = Shared<Derived...>;
using ExprVariant = Variant<ContextFreeGrammar::Expr*, Unique<ContextFreeGrammar::Expr>>;

namespace Logging {
    template<typename Derived>
    class logging;
};
namespace Stack {
    class stack;
};
#endif 
