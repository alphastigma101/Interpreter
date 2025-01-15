//#include <interpreter.h>
#include <context_free_grammar.h>
#include <tactical_nuke.h>
#include "resolver.h"
//Stack::stack* Resolver::resolver::scopes = new Stack::stack();

/** ------------------------------------------
 * @brief A constructor that uses `this->` to initialize the data member with the parameter
 * 
 * @param interp A raw pointer that points to interpreter
 * 
 * --------------------------------------------
*/
Resolver::resolver::resolver(Interpreter::interpreter *interp) noexcept { this->interp = std::move(interp); }
/** -----------------------------------------------------------------
 * @brief Resolves a list of statements by iterating through each statement
 *        and invoking the resolve method recursively. 
 * 
 * @param stmt A pointer to an abstract class called `Statement`.
 * 
 * @details This begins a new scope  for each statement, traverses into the individual statement, 
 *          processes it, and then moves to the next. 
 * @details The logic for processing lives in the helper methods invoked within the `resolve` function.
 * 
 * -------------------------------------------------------------------
*/
void Resolver::resolver::resolve(Vector<ContextFreeGrammar::Statement*> statements) {
    for (auto statement : statements) {
      resolve(statement);
    }
}
/** -------------------------------------------------------------------
 * @brief Resolves a single statement in the context-free grammar.
 * 
 * @details This function calls the `accept` method on the provided 
 *          statement, delegating the resolution process to the statement itself. 
 * @details The implementation relies on the internal logic defined in the 
 *          statement's `accept` method.
 * 
 * @note If this implementation fails, consider replacing the argument 
 * passed to `accept` with the current object instance (`this`).
 * 
 * @param stmt A pointer to the statement to be resolved.
 * 
 * --------------------------------------------------------------------
 */
void Resolver::resolver::resolve(ContextFreeGrammar::Statement* stmt) { stmt->accept(this); }
/** -------------------------------------------------------------------
 * @brief Resolves a single expression in the context-free grammar.
 * 
 * @details This function calls the `accept` method on the provided 
 *          expression, delegating the resolution process to the statement itself. 
 * @details The implementation relies on the internal logic defined in the 
 *          statement's `accept` method.
 * @param expr A pointer to the Expr to be resolved.
 * 
 * --------------------------------------------------------------------
*/
void Resolver::resolver::resolve(ContextFreeGrammar::Expr *expr) { expr->accept(this); }
void Resolver::resolver::resolveFunction(ContextFreeGrammar::Functions *function, FunctionType type) {
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;
    beginScope();
    for (auto param : function->params) {
      declare(param);
      define(param);
    }
    for (auto body : function->statements) this->resolve(body);
    endScope();
    currentFunction = enclosingFunction;
}

void Resolver::resolver::resolveProperties(ContextFreeGrammar::Statement *stmt) {
    beginScope();
    declare(stmt->op);
    define(stmt->op);
    this->resolve(stmt);
    endScope();
}
/** ---------------------------------------------------------------------------------
 * @brief Creates a new lexical scope by allocating a map on the stack.
 * 
 * @return None
 * 
 * ---------------------------------------------------------------------------------- 
*/
void Resolver::resolver::beginScope() { scopes->push(new Map<String, bool>()); }
/** ---------------------------------------------------------------------------------
 * @brief  Resolves the variable. 
 *         If variable is not found in stack, assume that variable is global therefore pop it.
 * ----------------------------------------------------------------------------------
*/
void Resolver::resolver::endScope() { scopes->pop(); }
/** ---------------------------------------------------------------------------------
 * @brief A method that throws an error when a variable is already initialized
 * 
 * @param name is a lvalue reference to the Token class 
*/
void Resolver::resolver::declare(Token name) {
    if (scopes->isEmpty()) return;
    try {
        if (scopes->peek().at(name.getLexeme())) {
            int temp = std::stoi(name.getLiteral());
            NuclearLang::Nuke::error(temp, "Already a variable with this name in this scope.");
        }
        else 
            scopes->peek().insert_or_assign(name.getLexeme(), false);
    }
    catch(...) {
        scopes->peek().insert_or_assign(name.getLexeme(), false);
    }
}
/** ----------------------------------------------------
 * @brief resolve its initializer expression 
 *        in that same scope where the new variable now exists but is unavailable.
 * 
 * -----------------------------------------------------
*/
void Resolver::resolver::define(Token name) {
    if (scopes->isEmpty()) return;
    scopes->peek().insert_or_assign(name.getLexeme(), true);
    return;
}
/** -------------------------------------------------------------
 * @brief A helper method that actually resolves the variable during the walking phase
 * 
 * @param expr A pointer to the abstract class Expr
 * @param name An alias to the Token class 
 */
void Resolver::resolver::resolveLocal(ContextFreeGrammar::Expr *expr, Token name) {
    for (int i = scopes->size() - 1; i >= 0; i--) {
        auto& scope = scopes->get(i);
        auto it = scope.find(name.getLexeme());
        if (it != scope.end()) {
            interp->resolve(expr, scopes->size() - 1 - i);
            return;
        }
    }
}

/** ---------------------------------------------------------------------------------
 * @brief A vistor method that visits lexical scopes
 *
 * @param stmt A derived class that derives from Statement
 *
 * ----------------------------------------------------------------------------------
 */
Any Resolver::resolver::visitBlockStmt(ContextFreeGrammar::Block* stmt) {
    beginScope();
    resolve(stmt->statements);
    endScope();
    return nullptr;
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @details the key entry "this" can have another entry that could be its field or properties
 *          Fields are member variables while properties can be methods
 * @return returns nullptr 
*/
Any Resolver::resolver::visitClassStmt(ContextFreeGrammar::Class *stmt) {
    ClassType enclosingClass = currentClass;
    currentClass = ClassType::CLASS;
    declare(stmt->op);
    define(stmt->op);
    if (stmt->superclass != nullptr &&
        stmt->op.getLexeme() == stmt->superclass->op.getLexeme()) {
       NuclearLang::Nuke::error(stmt->superclass->op.getLine(), "A class can't inherit from itself.");
    }
    if (stmt->superclass != nullptr) {
        currentClass = ClassType::SUBCLASS;
        resolve(stmt->superclass);
    }
    if (stmt->superclass != nullptr) {
        beginScope();
        scopes->peek().insert_or_assign("super", true);
    }
    beginScope();
    scopes->peek().insert_or_assign("this", true);
    for (int i = 0; i < stmt->methods.size(); i++) {
      FunctionType declaration = FunctionType::METHOD;
      if (stmt->methods.at(i)->op.getLexeme() == String("init")) {
        declaration = FunctionType::INITIALIZER;
      }
      resolveFunction(stmt->methods.at(i), declaration);
    }
    if (stmt->superclass != nullptr) endScope(); 
    currentClass = enclosingClass;
    endScope();
    return nullptr;
}

Any Resolver::resolver::visitExpressionStmt(ContextFreeGrammar::Expression *stmt) {
    resolve(stmt->expression);
    return nullptr;
}
/** ---------------------------------------------------------
 * @brief When resolving a function, it will bind the parameters to the function.
 * 
 * @param stmt It is a pointer to the Functions class
 * 
*/
Any Resolver::resolver::visitFunctionStmt(ContextFreeGrammar::Functions *stmt) {
    declare(stmt->op);
    define(stmt->op);
    resolveFunction(stmt, FunctionType::FUNCTION);
    return nullptr;
}
Any Resolver::resolver::visitIfStmt(ContextFreeGrammar::If *stmt) {
    resolve(stmt->condition);
    resolve(stmt->thenBranch);
    if (stmt->elseBranch != nullptr) resolve(stmt->elseBranch);
    return nullptr;
}
Any Resolver::resolver::visitPrintStmt(ContextFreeGrammar::Print *stmt) {
    resolve(stmt->initializer);
    return nullptr;
}
Any Resolver::resolver::visitReturnStmt(ContextFreeGrammar::Return *stmt) {
    if (currentFunction == FunctionType::NONE) {
        int temp = std::stoi(stmt->op.getLiteral());
        NuclearLang::Nuke::error(temp, "Can't return from top-level code.");
    }
    if (stmt->value != nullptr) {
        if (currentFunction == FunctionType::INITIALIZER) {
            int temp = std::stoi(stmt->op.getLiteral());
            NuclearLang::Nuke::error(temp,
                "Can't return a value from an initializer.");
        }
      resolve(stmt->value);
    }
    return nullptr;
}
/** ---------------------------------------------------------------------------------
 * @brief A vistor method that visits lexical scopes
 *
 * @param stmt A derived class that derives from Statement
 * 
 * @details It will put stuff inside the stack. 
 *
 * ----------------------------------------------------------------------------------
 */
Any Resolver::resolver::visitVarStmt(ContextFreeGrammar::Statement *stmt) {
    declare(stmt->op);
    if (stmt->initializer != nullptr) {
      resolve(stmt->initializer);
    }
    define(stmt->op);
    return nullptr;
}

Any Resolver::resolver::visitWhileStmt(ContextFreeGrammar::While *stmt) {
    resolve(stmt->condition);
    resolve(stmt->body);
    return nullptr;
}

Any Resolver::resolver::visitVariableExpr(ContextFreeGrammar::Variable *expr) {
    try {
        auto map = scopes->peek();
        if (!scopes->isEmpty() && map.at(expr->op.getLexeme()) == false) {
            int temp = std::stoi(expr->op.getLiteral());
            NuclearLang::Nuke::error(temp, "Can't read local variable in its own initializer.");
        }
    } catch(...) {}
    resolveLocal(expr, expr->op);
    return nullptr;
}

Any Resolver::resolver::visitAssignExpr(ContextFreeGrammar::Assign *expr) {
    resolve(expr->right);
    resolveLocal(expr, expr->op);
    return nullptr;
}

Any Resolver::resolver::visitBinaryExpr(ContextFreeGrammar::Binary *expr) {
    resolve(expr->left);
    resolve(expr->right);
    return nullptr;
}

Any Resolver::resolver::visitCallExpr(ContextFreeGrammar::Call *expr) {
    resolve(expr->callee);
    for (auto argument : expr->arguments) {
      resolve(std::any_cast<ContextFreeGrammar::Call*>(argument));
    }
    return nullptr;
}
Any Resolver::resolver::visitGroupingExpr(ContextFreeGrammar::Grouping *expr) {
    resolve(expr->expression);
    return nullptr;
}

Any Resolver::resolver::visitGetExpr(ContextFreeGrammar::Get *expr) {
    resolve(expr->object);
    return nullptr;
}

Any Resolver::resolver::visitLiteralExpr(ContextFreeGrammar::Literal *expr) { return nullptr; }

Any Resolver::resolver::visitLogicalExpr(ContextFreeGrammar::Logical *expr) {
    resolve(expr->left);
    resolve(expr->right);
    return nullptr;
}

Any Resolver::resolver::visitSetExpr(ContextFreeGrammar::Set *expr) {
    resolve(expr->value);
    resolve(expr->object);
    return nullptr;
}

Any Resolver::resolver::visitSuperExpr(ContextFreeGrammar::Super *expr) {
    if (currentClass == ClassType::EMPTY) {
      NuclearLang::Nuke::error(expr->op.getLine(), "Can't use 'super' outside of a class.");
    } else if (currentClass != ClassType::SUBCLASS) {
       NuclearLang::Nuke::error(expr->op.getLine(), "Can't use 'super' in a class with no superclass.");
    }
    resolveLocal(expr, expr->op);
    return nullptr;
}
Any Resolver::resolver::visitThisExpr(ContextFreeGrammar::This *expr) {
    if (currentClass == ClassType::EMPTY) {
        NuclearLang::Nuke::error(expr->op.getLine(), "Can't use 'this' outside of a class.");
        return nullptr;
    }
    resolveLocal(expr, expr->op);
    return nullptr;
}

Any Resolver::resolver::visitUnaryExpr(ContextFreeGrammar::Unary *expr) {
    resolve(expr->right);
    return nullptr;
}
