#include <resolver.h>
#include <interpreter.h>
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
void Resolver::resolver::resolve(Vector<Statement*>& statements) {
    for (auto& statement : statements) {
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
void Resolver::resolver::resolve(ContextFreeGrammar::Statement* stmt) {
    // TODO: If this does not work, then swap out the argument with this instead
    stmt->accept(stmt);
}

void Resolver::resolver::resolve(Expr *expr) {
    expr->accept(expr);
}
void Resolver::resolver::resolveFunction(ContextFreeGrammar::Functions *function, FunctionType type) {
    FunctionType enclosingFunction = currentFunction;
    currentFunction = type;
    beginScope();
    for (auto& param : function->params) {
      declare(param);
      define(param);
    }
    resolve(function->body);
    endScope();
    currentFunction = enclosingFunction;
}
/** ---------------------------------------------------------------------------------
 * @brief Creates a new lexical scope
 * 
 * @return None
 * 
 * ---------------------------------------------------------------------------------- 
*/
void Resolver::resolver::beginScope() {
    auto map = new Map<String, bool>();
    scopes->push(std::move(map));
}
/** ---------------------------------------------------------------------------------
 * @brief Exits the stack explicitly 
 * ----------------------------------------------------------------------------------
*/
void Resolver::resolver::endScope() { scopes->pop(); }

void Resolver::resolver::declare(Token &name) {
    if (scopes->isEmpty()) return;

    Map<String, bool>* scope = scopes->peek();
    if (scope->at(name.getLexeme())) {
      /*Lox.error(name,
          "Already a variable with this name in this scope.");*/
    }
    scope->insert_or_assign(name.getLexeme(), false);
}

void Resolver::resolver::define(Token &name) {
    if (scopes->isEmpty()) return;
    scopes->peek()->insert_or_assign(name.getLexeme(), true);
}

void Resolver::resolver::resolveLocal(Expr *expr, Token &name)
{
    for (int i = scopes->size() - 1; i >= 0; i--) {
      if (scopes->get(i)->at(name.getLexeme())) {
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
Any Resolver::resolver::visitExpressionStmt(ContextFreeGrammar::Expression *stmt) {
    resolve(stmt->initializer);
    return nullptr;
}
Any Resolver::resolver::visitFunctionStmt(Functions *stmt)
{
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
      //Lox.error(stmt.keyword, "Can't return from top-level code.");
    }
    if (stmt->value != nullptr) {
      resolve(stmt->value);
    }
    return nullptr;
}
/** ---------------------------------------------------------------------------------
 * @brief A vistor method that visits lexical scopes
 *
 * @param stmt A derived class that derives from Statement
 *
 * ----------------------------------------------------------------------------------
 */
Any Resolver::resolver::visitVarStmt(Statement *stmt) {
    beginScope();
    resolve(stmt->statements);
    endScope();
    return nullptr;
}

Any Resolver::resolver::visitWhileStmt(ContextFreeGrammar::While *stmt) {
    resolve(stmt->condition);
    resolve(stmt->body);
    return nullptr;
}

Any Resolver::resolver::visitVariableExpr(Variable *expr) {
    if (!scopes->isEmpty() &&
        scopes->peek()->at(expr->op.getLexeme()) == false) {
      /*Lox.error(expr.name,
          "Can't read local variable in its own initializer.");*/
    }
    resolveLocal(expr, expr->op);
    return nullptr;
}

Any Resolver::resolver::visitAssignExpr(Assign *expr) {
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
      resolve(std::any_cast<ContextFreeGrammar::Expr*>(argument));
    }
    return nullptr;
}
Any Resolver::resolver::visitGroupingExpr(ContextFreeGrammar::Grouping *expr) {
    resolve(expr->expression);
    return nullptr;
}

Any Resolver::resolver::visitLiteralExpr(ContextFreeGrammar::Literal *expr) { return nullptr; }

Any Resolver::resolver::visitLogicalExpr(ContextFreeGrammar::Logical *expr)
{
    resolve(expr->left);
    resolve(expr->right);
    return nullptr;
}

Any Resolver::resolver::visitUnaryExpr(ContextFreeGrammar::Unary *expr)
{
    resolve(expr->right);
    return nullptr;
}
