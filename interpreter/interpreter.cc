#include <interpreter.h>
Environment::environment* interpreter::env = new Environment::environment();
/** -------------------------------------------------
 * @brief Calls in evaluate mehtod to begin the evaluation 
 * 
*/
interpreter::interpreter(Vector<ContextFreeGrammar::Statement*>& stmt) {
    try {
        for (auto &it: stmt) {
            if (auto conv = dynamic_cast<Statement*>(it))
                execute(conv);
        }
    } 
    catch (runtimeerror<interpreter>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        logging<interpreter> logs(e.what(e.getType<TokenType>(), e.getMsg()));
        logs.rotate();
        logs_ = logs.getLogs();
    }                              
}
/** ------------------------------------------------
 * @brief Calls the accept method to begin the recrusive tree walk
 * 
 * @param temp A type safe union that is useful to return multiple types inside a conatinaer 
 * 
 */
String interpreter::evaluate(auto conv) {
    if (auto binary = dynamic_cast<Binary*>(conv)) return conv->accept(binary, false);
    else if (auto literal = dynamic_cast<Literal*>(conv)) return conv->accept(literal, false);
    else if (auto unary = dynamic_cast<Unary*>(conv)) return conv->accept(unary, false);
    else if (auto grouping = dynamic_cast<Grouping*>(conv)) return conv->accept(grouping, false);
    else if (auto assign = dynamic_cast<Assign*>(conv)) return conv->accept(assign, false);
    else { throw catcher<interpreter>("Unexpected type in evaluate function"); }
    return nullptr;
}
/** ---------------------------------------------------------------------------
 * @brief visits the Binary abstraction syntax tree 
 * 
 * @param auto expr: Is a generic type that must have a concrete type during run time and the tree it will visit at run time
 * 
 * @return A Binary abstraction syntax tree node in the form of a string
 * 
 * ---------------------------------------------------------------------------
*/
Any interpreter::visitBinaryExpr(ContextFreeGrammar::Binary* expr) {
    Any left = evaluate(expr->left);
    Any right = evaluate(expr->right);
    switch (expr->op.getType()) {
        case TokenType::GREATER:
            checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) > std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) > std::any_cast<int>(toNumeric(right)));
        case TokenType::GREATER_EQUAL:
            checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) >= std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) >= std::any_cast<int>(toNumeric(right)));
        case TokenType::LESS:
            checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) < std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) < std::any_cast<int>(toNumeric(right)));
        case TokenType::LESS_EQUAL:
            checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) <= std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) <= std::any_cast<int>(toNumeric(right)));
        case TokenType::MINUS:
            checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) - std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) - std::any_cast<int>(toNumeric(right)));
        case PLUS:
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) + std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) + std::any_cast<int>(toNumeric(right)));
            if (instanceof<String>(left) && instanceof<String>(right)) return std::any_cast<String>(left) + std::any_cast<String>(right);
            throw new runtimeerror<interpreter>(expr->op.getType(), "Operands must be two numbers or two strings.");
            break;
        case TokenType::SLASH:
            checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) / std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) / std::any_cast<int>(toNumeric(right)));
        case TokenType::STAR:
            checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(toNumeric(left)) * std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(toNumeric(left)) * std::any_cast<int>(toNumeric(right)));
        case TokenType::BANG_EQUAL: return !isEqual(left, right);
        case TokenType::EQUAL_EQUAL: return isEqual(left, right);
    }
    // Unreachable.
    return nullptr;
}
Any interpreter::visitUnaryExpr(ContextFreeGrammar::Unary* expr) {
    Any right = evaluate(expr->right);
    switch (expr->op.getType()) {
        case BANG:
            return !isTruthy(right);
        case TokenType::MINUS:
            checkNumberOperand(expr->op, right);
            if (instanceof<double>(right))
                return std::to_string(-std::any_cast<double>(toNumeric(right)));
            if (instanceof<int>(right))
                return std::to_string(-std::any_cast<int>(toNumeric(right)));
    }

    // Unreachable.
    return nullptr;
}
Any interpreter::visitExpressionStmt(ContextFreeGrammar::Expression* stmt) {
    String res;
    if (auto conv = dynamic_cast<Expression*>(stmt))
        res += evaluate(conv->initializer->expression);
    return res;
}

Any interpreter::visitPrintStmt(ContextFreeGrammar::Print* stmt) {
    String res;
    if (auto conv = dynamic_cast<Print*>(stmt))
        res += evaluate(conv->initializer);
    env->define(stmt->initializer->op.getTypeStr(), res);
    return res;
}
Any interpreter::visitVariableExpr(ContextFreeGrammar::Variable* expr) {
    if (auto conv = dynamic_cast<Variable*>(expr))
        return env->get(expr->op);
    return "\0";
}
void interpreter::visitVarStmt(ContextFreeGrammar::Var* stmt) {
    Any value = nullptr;
    if (stmt->initializer != nullptr) {
      value = evaluate(stmt->initializer);
    }
    env->define(stmt->op.getLexeme(), value);
    return;
}
Any interpreter::visitAssignExpr(ContextFreeGrammar::Assign* expr) {
    Any value = evaluate(expr->expression);
    env->assign(expr->op, value);
    return value;
}
void interpreter::visitBlockStmt(ContextFreeGrammar::Block* stmt) { 
    this->executeBlock(stmt->statements, new Environment::environment(*env));
}
void interpreter::executeBlock(Vector<ContextFreeGrammar::Statement*> statements, Environment::environment* environment) {
    Environment::environment* previous = this->env;
    try {
        this->env = environment;
        for (const auto& statement : statements) {
            execute(statement);
        }
    } catch(...) { this->env = previous; }
    this->env = previous;
}
/** ---------------------------------------------------------------
 * @brief A simple method that checks the instance using generics methods inside of it
 *
 * @param object Is an any container that always stores a String value.
 *               
 *
 * @details The parameter object will go through a series of generic methods to check and see if it is a supported type
 * ----------------------------------------------------------------
*/
template<typename T>
bool interpreter::instanceof(const Any& object) {
    try {
        if (isNumeric<T>(object)) return true;
        else if (isOther<T>(object)) return true;
        return false;
    } catch (...) {
        throw catcher<interpreter>("Unknown Type!");
    }
    return false;
}
