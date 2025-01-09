//#include <interpreter.h>
#include <context_free_grammar.h>
#include "interpreter.h"
#define ENABLE_VISITOR_PATTERN 1
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
Any interpreter::call(Interpreter::interpreter* interpreter, Vector<Any> arguments) {
    launch();
    return Any(); 
}

void Interpreter::interpreter::execute(ContextFreeGrammar::Statement *stmt) {
    stmt->accept(this);
}

/** -------------------------------------------------
 * @brief Calls in evaluate mehtod to begin the evaluation 
 * 
*/
interpreter::interpreter(Vector<ContextFreeGrammar::Statement*> stmt): interpreter::interpreter() {
    try {
        for (const auto it: stmt) {
            if (auto conv = dynamic_cast<ContextFreeGrammar::Statement*>(it))
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
    if (auto call = dynamic_cast<ContextFreeGrammar::Call*>(conv)) return conv->accept(this);
    else if (auto binary = dynamic_cast<ContextFreeGrammar::Binary*>(conv)) return conv->accept(this);
    else if (auto literal = dynamic_cast<ContextFreeGrammar::Literal*>(conv)) return conv->accept(this);
    else if (auto unary = dynamic_cast<ContextFreeGrammar::Unary*>(conv)) return conv->accept(this);
    else if (auto grouping = dynamic_cast<ContextFreeGrammar::Grouping*>(conv)) return conv->accept(this);
    else if (auto assign = dynamic_cast<ContextFreeGrammar::Assign*>(conv)) return conv->accept(this);
    else if (auto logic = dynamic_cast<ContextFreeGrammar::Logical*>(conv)) return conv->accept(this);
    else if (auto var = dynamic_cast<ContextFreeGrammar::Variable*>(conv)) return conv->accept(this);
    else if (auto get = dynamic_cast<ContextFreeGrammar::Get*>(conv)) return conv->accept(this);
    else if (auto set = dynamic_cast<ContextFreeGrammar::Set*>(conv)) return conv->accept(this);
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
            bO->checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) > std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) > std::any_cast<int>(bO->toNumeric(right)));
        case TokenType::GREATER_EQUAL:
            bO->checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) >= std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) >= std::any_cast<int>(bO->toNumeric(right)));
        case TokenType::LESS:
            bO->checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) < std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) < std::any_cast<int>(bO->toNumeric(right)));
        case TokenType::LESS_EQUAL:
            bO->checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) <= std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) <= std::any_cast<int>(bO->toNumeric(right)));
        case TokenType::MINUS:
            bO->checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) - std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) - std::any_cast<int>(bO->toNumeric(right)));
        case PLUS:
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) + std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) + std::any_cast<int>(bO->toNumeric(right)));
            return std::any_cast<String>(left) + std::any_cast<String>(right);
            throw runtimeerror<interpreter>(expr->op.getType(), "Operands must be two numbers or two strings.");
            break;
        case TokenType::SLASH:
            bO->checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) / std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) / std::any_cast<int>(bO->toNumeric(right)));
        case TokenType::STAR:
            bO->checkNumberOperands(expr->op, left, right);
            if (instanceof<double>(left) && instanceof<double>(right))
                return std::to_string(std::any_cast<double>(bO->toNumeric(left)) * std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(left) && instanceof<int>(right))
                return std::to_string(std::any_cast<int>(bO->toNumeric(left)) * std::any_cast<int>(bO->toNumeric(right)));
        case TokenType::BANG_EQUAL: return !bO->isEqual(left, right);
        case TokenType::EQUAL_EQUAL: return bO->isEqual(left, right);
    }
    // Unreachable.
    return nullptr;
}

Any interpreter::visitCallExpr(ContextFreeGrammar::Call* expr) {
    auto callee = evaluate(expr->callee);
    Vector<Any> arguments;
    for (auto it : expr->arguments) {
        try {
            arguments.push_back(evaluate(std::any_cast<ContextFreeGrammar::Expr*>(it)));
        }
        catch(...) {
            throw runtimeerror<interpreter>(expr->op, "Failed to convert one of the elements in arguments into Expr*");
        }
    }
    if (callee.type() == typeid(NuclearLang::NukeFunction*)) {
        auto function = std::any_cast<NuclearLang::NukeFunction*>(callee);
        if (arguments.size() != function->arity()) {
        throw runtimeerror<Interpreter::interpreter>(expr->paren, String("Expected " +
            std::to_string(function->arity()) + " arguments but got " +
            std::to_string(arguments.size()) + ".").c_str());
        }
        return function->call(this, arguments);
    }
    else if (callee.type() == typeid(NuclearLang::NukeClass*)) {
        auto function = std::any_cast<NuclearLang::NukeClass*>(callee);
        if (arguments.size() != function->arity()) {
            throw runtimeerror<interpreter>(expr->paren, String("Expected " +
            std::to_string(function->arity()) + " arguments but got " +
            std::to_string(arguments.size()) + ".").c_str());
        }
        return function->call(this, arguments); 
    }
    throw runtimeerror<Interpreter::interpreter>(expr->paren, "Can only call functions and classes.");
}

Any Interpreter::interpreter::visitGetExpr(ContextFreeGrammar::Get *expr) {
    Any object = evaluate(expr->object);
    if (instanceof<NuclearLang::NukeInstance*>(object)) {
        auto res = std::any_cast<NuclearLang::NukeInstance*>(object);
        return res->get(expr->op);
    }

    throw runtimeerror<Interpreter::interpreter>(expr->op,
        "Only instances have properties.");
}

Any interpreter::visitUnaryExpr(ContextFreeGrammar::Unary* expr) {
    Any right = evaluate(expr->right);
    switch (expr->op.getType()) {
        case BANG:
            return !tO->isTruthy(right);
        case TokenType::MINUS:
            uO->checkNumberOperand(expr->op, right);
            if (instanceof<double>(right))
                return std::to_string(-std::any_cast<double>(bO->toNumeric(right)));
            if (instanceof<int>(right))
                return std::to_string(-std::any_cast<int>(bO->toNumeric(right)));
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

Any Interpreter::interpreter::visitBlockStmt(ContextFreeGrammar::Block *stmt) {
    executeBlock(stmt->statements, new Environment::environment(*globals));
    return nullptr;
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
    Map<String, NuclearLang::NukeFunction> methods;
    Map<String, NuclearLang::NukeProperties> properties;
    NuclearLang::NukeProperties* property;
    int j = 0;
    for (int i = 0; i < stmt->methods.size(); i++) {
        bool temp;
        if (stmt->methods.at(i)->op.getLexeme() == String("init")) temp = true;
        else temp = false;
        NuclearLang::NukeFunction* function = new NuclearLang::NukeFunction(
            stmt->methods.at(i), 
            environment, 
            temp
        );
        if (i < stmt->properties.size() && !stmt->properties.empty()) { 
            NuclearLang::NukeProperties* property = new NuclearLang::NukeProperties(
                    stmt->properties.at(i)->types.at(i),
                    stmt->properties.at(i)
            );
            properties.insert_or_assign(stmt->op.getLexeme(), std::move(*property));
            j++;
        }  
      methods.insert_or_assign(stmt->methods.at(i)->op.getLexeme(), std::move(*function));
    }
    for (int i = j; i < stmt->properties.size(); i++) {
        NuclearLang::NukeProperties* property = new NuclearLang::NukeProperties(
                stmt->types.at(i),
                stmt->properties.at(i)
        );
        properties.insert_or_assign(stmt->op.getLexeme(), std::move(*property));
    }
    NuclearLang::NukeClass* klass = new NuclearLang::NukeClass(stmt->op.getLexeme(), methods, properties);
    environment->assign(stmt->op, std::move(klass));
    return nullptr;
}
Any interpreter::visitExpressionStmt(ContextFreeGrammar::Expression *stmt) {
    if (auto conv = dynamic_cast<ContextFreeGrammar::Expression*>(stmt))
        evaluate(conv->expression);
    return nullptr;
}
Any interpreter::visitFunctionStmt(ContextFreeGrammar::Functions* stmt) {
    NuclearLang::NukeFunction* function = new NuclearLang::NukeFunction(stmt, environment, false);
    environment->define(stmt->op.getLexeme(), std::move(function));
    try {
        // Get the type globably 
        globalType = stmt->properties.at(globals->count(stmt->op.getLexeme()))->op.getLexeme();
        std::cout << globalType << std::endl;
    }
    catch(...) {}
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
    if (auto conv = dynamic_cast<ContextFreeGrammar::Print*>(stmt))
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
}
Any Interpreter::interpreter::lookUpVariable(Token name, ContextFreeGrammar::Expr *expr) {
    int* distance = nullptr;
    try {
        if (locals.size() != 0)
            distance = new int(locals.count(expr));
        else 
            distance = nullptr;
    } catch(...) {}
    if (distance != nullptr) {
      return environment->getAt(std::move(*distance), name.getLexeme());
    } else {
      return globals->get(name);
    }
}
Any interpreter::visitVarStmt(ContextFreeGrammar::Var* stmt) {
    // TODO: Need to get the type locally.
    Any value = nullptr;
    if (stmt->initializer != nullptr) {
      value = evaluate(stmt->initializer);
    }
    globals->define(stmt->op.getLexeme(), value);
    return nullptr;
}
Any interpreter::visitWhileStmt(ContextFreeGrammar::While* stmt) {
    while (tO->isTruthy(evaluate(stmt->condition))) {
        execute(stmt->body);
    }
    return nullptr;
}
Any interpreter::visitAssignExpr(ContextFreeGrammar::Assign* expr) {
    Any value = evaluate(expr->right);
    int* distance = nullptr;
    try {
        distance = new int(locals.count(expr));
    }
    catch(...) {distance = nullptr;}
    if (distance != nullptr) {
      environment->assignAt(std::move(*distance), expr->op, value);
    } else {
      globals->assign(expr->op, value);
    }
    return value;
}
Any interpreter::visitIfStmt(ContextFreeGrammar::If* stmt) {
    Any res = evaluate(stmt->condition);
    if (tO->isTruthy(res)) {
        execute(stmt->thenBranch);
    } else if (stmt->elseBranch != nullptr) {
        execute(stmt->elseBranch);
    }
    return nullptr;
}
Any interpreter::visitLogicalExpr(ContextFreeGrammar::Logical* expr) {
    Any left = evaluate(expr->left);
    if (expr->op.getType() == TokenType::OR) {
      if (tO->isTruthy(left)) return left;
    } else {
      if (!tO->isTruthy(left)) return left;
    }
    return evaluate(expr->right);
}

Any Interpreter::interpreter::visitSetExpr(ContextFreeGrammar::Set *expr) {
    Any object = evaluate(expr->object);

    if (!instanceof<NuclearLang::NukeInstance*>(object))
        throw  runtimeerror<Interpreter::interpreter>(expr->op, "Only instances have fields.");
    Any value = evaluate(expr->value);
    auto res = std::any_cast<NuclearLang::NukeInstance*>(object);
    res->set(expr->op, value);
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
bool interpreter::instanceof(const Any object) {
    try {
        if (typeid(T) == typeid(int) || typeid(T) == typeid(double)) {
            if (bO->isNumeric<T>(&object)) return true;
            //throw catcher<Interpreter::interpreter>("Unknown Type!");
        }
        //else if (typeid(T) == typeid(String)) 
        else if (bO->isOther<T>(&object)) return true;
        return false;
    } catch (catcher<Interpreter::interpreter>& e)  {
        std::cout << e.what() << std::endl;
    }
    return false;
}

// execption methods 
//
/** --------------------------------------
 * @brief A method that is overloaded here from this class 
 * 
 * @details The runtimeerror class will call this method and it will output something to the temrinal
 * 
 * @param msg A default argument that calls in a statically inlined method to output error message
 * @param type A temp object that will eventually be destroyed once it leaves the scope. 
 *             It also calls in a statically inlined method to get the TokenType
 * 
 * @return a concated string back to the caller method
 * 
 * ---------------------------------------
*/
const char *Interpreter::interpreter::what(const TokenType &type, const char *msg) throw() {
    static String output;
    try {
        if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
            output = search->second.c_str() + String(msg);
            return output.c_str();
        }
        else 
            throw catcher<interpreter>("In interpreter class: Error! conversion has failed!");
    }
    catch(catcher<interpreter>& e) {
        #if ENABLE_LOGGING
            std::cout << "Logs have been updated!" << std::endl;
            logging<interpreter> logs(e.what());
            logs_ = logs.getLogs();
            logs.rotate();
        #endif
        std::cout << e.what() << std::endl;
    }
    return output.c_str();
}