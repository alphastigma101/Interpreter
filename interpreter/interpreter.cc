#include <interpreter.h>
#include <context_free_grammar.h>
Environment::environment* interpreter::globals = new Environment::environment();
/** ------------------------------------------------
 * @brief Default constructor that calls in native functions 
 * 
 * @details Native functions are built in and come with the language  
 * 
*/
interpreter::interpreter() {
    globals->define(String("launch"), new NuclearLang::NukeCallable<NukeFunction>());
    globals->define(String("fussion"), new NuclearLang::NukeCallable<NukeFunction>());
    globals->define(String("fission"), new NuclearLang::NukeCallable<NukeFunction>());
}
/** ------------------------------------------------
 * @brief Returns the value that the call expression produces.
 * 
 * @param interpreter A pointer to the interpreter class
 * @param arguments A vector that contains a list of arguments of user-defined function 
 * 
 */
Any interpreter::call(Interpreter::interpreter* interpreter, Vector<Any>& arguments) {
    launch();
    return Any(); 
}

/** -------------------------------------------------
 * @brief Calls in evaluate mehtod to begin the evaluation 
 * 
*/
interpreter::interpreter(Vector<ContextFreeGrammar::Statement*>& stmt): interpreter::interpreter() {
    try {
        for (auto &it: stmt) {
            if (auto conv = dynamic_cast<Statement*>(it))
                execute(conv);
        }
    } 
    catch (runtimeerror<interpreter>& e) {
        String error = e.what(e.getType<TokenType>(), e.getMsg());
        #if ENABLE_LOGGING
            std::cout << "Logs have been updated!" << std::endl;
            logging<interpreter> logs(error);
            logs.rotate();
            logs_ = logs.getLogs();
        #else
            std::cout << error << std::endl;
        #endif
    }                              
}
/** ------------------------------------------------
 * @brief Calls the accept method to begin the recrusive tree walk
 * 
 * @param temp A type safe union that is useful to return multiple types inside a conatinaer 
 * 
 */
Any interpreter::evaluate(ContextFreeGrammar::Expr* conv) {
    if (auto call = dynamic_cast<Call*>(conv)) return conv->accept(this);
    else if (auto binary = dynamic_cast<Binary*>(conv)) return conv->accept(this);
    else if (auto literal = dynamic_cast<Literal*>(conv)) return conv->accept(this);
    else if (auto unary = dynamic_cast<Unary*>(conv)) return conv->accept(this);
    else if (auto grouping = dynamic_cast<Grouping*>(conv)) return conv->accept(this);
    else if (auto assign = dynamic_cast<Assign*>(conv)) return conv->accept(this);
    else if (auto logic = dynamic_cast<Logical*>(conv)) return conv->accept(this);
    else if (auto var = dynamic_cast<Variable*>(conv)) return conv->accept(this);
    throw catcher<interpreter>("Unexpected type in evaluate function");
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

Any interpreter::visitCallExpr(ContextFreeGrammar::Call* expr) {
    auto callee = evaluate(expr->callee);
    Vector<Any> arguments;
    for (auto& it : expr->arguments) {
        try {
            arguments.push_back(evaluate(std::any_cast<ContextFreeGrammar::Expr*>(it)));
        }
        catch(...) {
            throw runtimeerror<interpreter>(expr->op, "Failed to convert one of the elements in arguments into Expr*");
        }
    }
    if (!(instanceof<NukeFunction*>(callee))) {
      throw runtimeerror<interpreter>(expr->paren,
          "Can only call functions and classes.");
    }
    auto function = std::any_cast<NukeFunction*>(callee);
    if (arguments.size() != function->arity()) {
      throw runtimeerror<interpreter>(expr->paren, String("Expected " +
          std::to_string(function->arity()) + " arguments but got " +
          std::to_string(arguments.size()) + ".").c_str());
    }
    return function->call(this, arguments);
}

Any Interpreter::interpreter::visitGetExpr(ContextFreeGrammar::Get *expr) {
    Any object = evaluate(expr->object);
    if (instanceof<NuclearLang::NukeInstance>(object)) {
        auto res = std::any_cast<NuclearLang::NukeInstance>(object);
      return res.get(expr->op);
    }

    throw runtimeerror<Interpreter::interpreter>(expr->op,
        "Only instances have properties.");
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

Any Interpreter::interpreter::visitLiteralExpr(ContextFreeGrammar::Literal *expr) {
    return expr->op.getLexeme();
}

Any Interpreter::interpreter::visitGroupingExpr(ContextFreeGrammar::Grouping *expr) {
    return evaluate(expr->expression);
}
/** ---------------------------------------------------------------
 * @brief Represents the runtime of a class
 * 
 * @details Store the name of the class inside of a map. 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
Any Interpreter::interpreter::visitClassStmt(ContextFreeGrammar::Class *stmt) {
    environment->define(stmt->op.getLexeme(), nullptr);
    Map<String, NuclearLang::NukeFunction>* methods = new Map<String, NuclearLang::NukeFunction>();
    for (auto& method : stmt->methods) {
        bool temp;
        if (method->op.getLexeme() == String("init")) temp = true;
        else temp = false;
      NuclearLang::NukeFunction* function = new NuclearLang::NukeFunction(
            method, 
            environment, 
            temp
        );
      methods->insert_or_assign(method->op.getLexeme(), std::move(*function));
    }
    NuclearLang::NukeClass* klass = new NuclearLang::NukeClass(stmt->op.getLexeme(), methods);
    environment->assign(stmt->op, klass);
    return nullptr;
}
Any interpreter::visitExpressionStmt(ContextFreeGrammar::Expression *stmt)
{
    if (auto conv = dynamic_cast<Expression*>(stmt))
        evaluate(conv->expression);
    return "\0";
}
Any interpreter::visitFunctionStmt(ContextFreeGrammar::Functions* stmt) {
    NukeFunction* function = new NukeFunction(stmt, environment, false);
    environment->define(stmt->op.getLexeme(), std::move(function));
    //functionName = new String(stmt->op.getLexeme());
    return nullptr;
}
/** ---------------------------------------------------------------------------
 * @brief visits the Print class from context_free_grammar.cc and evaluates the value 
 * 
 * @param stmt: Is a raw pointer that points to the class called Return. 
 * 
 * @return Returns an any type.
 * 
 * ---------------------------------------------------------------------------
*/
Any interpreter::visitPrintStmt(ContextFreeGrammar::Print* stmt) {
    if (auto conv = dynamic_cast<Print*>(stmt))
        globals->define("radiate", evaluate(conv->initializer));
    return nullptr;
}
/** ---------------------------------------------------------------------------
 * @brief visits the Return class from context_free_grammar.cc and evaluates the value 
 * 
 * @param stmt: Is a raw pointer that points to the class called Return. 
 * 
 * @return Returns nothing.
 * 
 * ---------------------------------------------------------------------------
*/
Any interpreter::visitReturnStmt(ContextFreeGrammar::Return* stmt) {
    Any value = nullptr;
    if (stmt->value != nullptr) { 
        value = evaluate(stmt->value);
        //environment->define(std::move(*((String*)functionName)), value);
    }
    throw new NuclearLang::NukeReturn(value);
}

Any interpreter::visitVariableExpr(ContextFreeGrammar::Variable* expr) {
    return lookUpVariable(expr->op, expr);
    /*if (auto conv = dynamic_cast<Variable*>(expr))
        return globals->get(expr->op);
    throw catcher<interpreter>("Data member of interpreter 'visitVariableExpr', failed to convert its parameter into Variable class!");*/
}
Any Interpreter::interpreter::lookUpVariable(Token name, ContextFreeGrammar::Expr *expr) {
    int* distance = nullptr;
    try {
        *distance = locals->at(expr);
    } catch(...) {}
    if (distance != nullptr) {
      return environment->getAt(std::any_cast<int>(distance), name.getLexeme());
    } else {
      return globals->get(name);
    }
}
Any interpreter::visitVarStmt(ContextFreeGrammar::Var* stmt) {
    Any value = nullptr;
    if (stmt->initializer != nullptr) {
      value = evaluate(stmt->initializer);
    }
    globals->define(stmt->op.getLexeme(), value);
    return nullptr;
}
Any interpreter::visitWhileStmt(ContextFreeGrammar::While* stmt) {
    while (isTruthy(evaluate(stmt->condition))) {
        execute(stmt->body);
    }
    return nullptr;
}
Any interpreter::visitAssignExpr(ContextFreeGrammar::Assign* expr) {
    Any value = evaluate(expr->right);
    Any distance;
    try {
        locals->at(expr);
    }
    catch(...) {distance = nullptr;}
    if (distance.type() != typeid(nullptr)) {
      environment->assignAt(std::any_cast<int>(distance), expr->op, value);
    } else {
      globals->assign(expr->op, value);
    }
    return value;
}
Any interpreter::visitIfStmt(ContextFreeGrammar::If* stmt) {
    Any res = evaluate(stmt->condition);
    if (isTruthy(res)) {
        execute(stmt->thenBranch);
    } else if (stmt->elseBranch != nullptr) {
        execute(stmt->elseBranch);
    }
    return nullptr;
}
Any interpreter::visitLogicalExpr(ContextFreeGrammar::Logical* expr) {
    Any left = evaluate(expr->left);
    if (expr->op.getType() == TokenType::OR) {
      if (isTruthy(left)) return left;
    } else {
      if (!isTruthy(left)) return left;
    }
    return evaluate(expr->right);
}

Any Interpreter::interpreter::visitSetExpr(ContextFreeGrammar::Set *expr)
{
    Any object = evaluate(expr->object);

    if (!instanceof<NuclearLang::NukeInstance>(object)) {
        throw  runtimeerror<Interpreter::interpreter>(expr->op, "Only instances have fields.");
    }

    Any value = evaluate(expr->value);
    auto res = std::any_cast<NuclearLang::NukeInstance>(object);
    res.set(expr->op, value);
    return value;
}

Any Interpreter::interpreter::visitThisExpr(ContextFreeGrammar::This *expr) {
    return lookUpVariable(expr->op, expr);
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
