#include <context_free_grammar.h>
#include <interpreter.h>
Environment::environment* Interpreter::interpreter::globals = new Environment::environment();
/** ------------------------------------------------
 * @brief Default constructor that calls in native functions 
 * 
 * @details Native functions are built in and come with the language  
 * 
*/
Interpreter::interpreter::interpreter() {
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
Any Interpreter::interpreter::call(Interpreter::interpreter* interpreter, Vector<Any> arguments) {
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
Interpreter::interpreter::interpreter(Vector<ContextFreeGrammar::Statement*> stmt): Interpreter::interpreter::interpreter() {
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
Any Interpreter::interpreter::evaluate(ContextFreeGrammar::Expr* conv) {
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
    else if (auto this_ = dynamic_cast<ContextFreeGrammar::This*>(conv)) return conv->accept(this);
    else if (auto super = dynamic_cast<ContextFreeGrammar::Super*>(conv)) return conv->accept(this);
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
Any Interpreter::interpreter::visitBinaryExpr(ContextFreeGrammar::Binary* expr) {
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

Any Interpreter::interpreter::visitCallExpr(ContextFreeGrammar::Call* expr) {
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
    String error = String(" [Line Error ") + std::to_string(expr->op.getLine()) + String( "]:") + String(" Can only call functions and classes."); 
    throw runtimeerror<Interpreter::interpreter>(expr->paren, error.c_str());
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

Any Interpreter::interpreter::visitUnaryExpr(ContextFreeGrammar::Unary* expr) {
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
    // TODO: The code should work or might need some modifications, but it does what it is supposed to do
    // TODO: It needs to be placed somewhere else to handle cases when the class property contains statement fields 
    // Code below should work for properties defined inside of the class and for free functions
    /*if (!stmt->body->fields.empty()) {
        for (const auto it: stmt->body->fields) {
            Fields.push_back(it);
        }
    }*/
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
    Map<String, NuclearLang::NukeFunction> methods;
    Map<String, NuclearLang::NukeProperties> fieldProperties;
    NuclearLang::NukeProperties* propertyFields;
    Any superclass = nullptr;
    if (stmt->superclass != nullptr) {
        superclass = evaluate(stmt->superclass);
        if (!(superclass.type() == typeid(NuclearLang::NukeClass*))) {
            throw runtimeerror<Interpreter::interpreter>(stmt->superclass->op, "Superclass must be a class.");
        }
    }
    environment->define(stmt->op.getLexeme(), nullptr);
    if (stmt->superclass != nullptr) {
      environment = new Environment::environment(environment);
      environment->define("super", superclass);
    }
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
        if (i < stmt->fields.size() && !stmt->fields.empty()) {
            propertyFields = new NuclearLang::NukeProperties(
                &(stmt->fields.at(i)->types.at(0)),
                &(stmt->fields.at(i)->op),
                &(stmt->methods.at(i)->types.at(0))
            );
            fieldProperties.insert_or_assign(stmt->op.getLexeme(), std::move(*propertyFields));
            j++;
        }
        else {
            // There are more properties than fields
            propertyFields = new NuclearLang::NukeProperties(
                nullptr,
                nullptr,
                &(stmt->methods.at(i)->types.at(0))
            );
            fieldProperties.insert_or_assign(stmt->op.getLexeme(), std::move(*propertyFields));
        }  
      methods.insert_or_assign(stmt->methods.at(i)->op.getLexeme(), std::move(*function));
    }
    for (int i = j; i < stmt->fields.size(); i++) {
        propertyFields = new NuclearLang::NukeProperties(
            stmt->fields.at(i)->types.at(0),
            stmt->fields.at(i),
            nullptr
        );
        fieldProperties.insert_or_assign(stmt->op.getLexeme(), std::move(*propertyFields));
    }
    NuclearLang::NukeClass* klass = new NuclearLang::NukeClass(stmt->op.getLexeme(), methods, superclass, propertyFields);
    if (!(superclass.has_value())) {
      environment = environment->enclosing;
    }
    environment->assign(stmt->op, std::move(klass));
    className = stmt->op;
    return nullptr;
}
Any Interpreter::interpreter::visitExpressionStmt(ContextFreeGrammar::Expression *stmt) {
    if (auto conv = dynamic_cast<ContextFreeGrammar::Expression*>(stmt))
        evaluate(conv->expression);
    return nullptr;
}
Any Interpreter::interpreter::visitFunctionStmt(ContextFreeGrammar::Functions* stmt) {
    NuclearLang::NukeFunction* function = new NuclearLang::NukeFunction(stmt, environment, false);
    /*if (&className != nullptr) {
        NuclearLang::NukeClass* property;
        Map<String, String> stmtFields;
        if (auto search = globals->getMap().find(className.getLexeme()); search != globals->getMap().end())
            property = std::any_cast<NuclearLang::NukeClass*>(search->second);
        else 
            throw;
        auto map = reinterpret_cast<Map<String, NuclearLang::NukeProperties>*>(property->fieldProperties);
        for (int i = 0; i < stmt->body->fields.size(); i++) {
            // Find the property name that has the statement fields
            if (auto search = map->find(stmt->op.getLexeme()); search != map->end()) {
                if (search->second.stmtFields == nullptr)
                    search->second.stmtFields = new Map<String, String>();
                auto tmp = reinterpret_cast<Map<String, String>*>(search->second.stmtFields);
                stmtFields = *tmp;
                stmtFields[std::any_cast<String>(Fields.at(i))] = stmt->body->fields.at(i)->op.getLexeme();
            }
        }
        if (auto search = map->find(stmt->op.getLexeme()); search != map->end())
            if (!stmtFields.empty())
                search->second.stmtFields = std::move(&stmtFields); 

    }*/
    environment->define(stmt->op.getLexeme(), std::move(function));
    /*try {
        // Get the type globably 
        globalType = stmt->properties.at(globals->count(stmt->op.getLexeme()))->op.getLexeme();
        std::cout << globalType << std::endl;
    }
    catch(...) {}*/
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
Any Interpreter::interpreter::visitPrintStmt(ContextFreeGrammar::Print* stmt) {
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
Any Interpreter::interpreter::visitReturnStmt(ContextFreeGrammar::Return* stmt) {
    Any value = nullptr;
    if (stmt->value != nullptr) { 
        value = evaluate(stmt->value);
        //environment->define(std::move(*((String*)functionName)), value);
    }
    throw new NuclearLang::NukeReturn(value);
}

Any Interpreter::interpreter::visitVariableExpr(ContextFreeGrammar::Variable* expr) {
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
Any Interpreter::interpreter::visitVarStmt(ContextFreeGrammar::Var* stmt) {
    // TODO: Need to get the type locally.
    Any value = nullptr;
    if (stmt->initializer != nullptr) {
      value = evaluate(stmt->initializer);
    }
    if (value.type() == typeid(void*)) {
        // Could be either NukeClass or NukeFunction
        void* tmp = std::any_cast<void*>(value);
        auto nukeFunction = reinterpret_cast<NuclearLang::NukeFunction*>(tmp);
        if (nukeFunction != nullptr)
            globals->define(stmt->op.getLexeme(), std::move(nukeFunction));
        else {
            auto nukeClass = reinterpret_cast<NuclearLang::NukeClass*>(tmp);
            globals->define(stmt->op.getLexeme(), std::move(nukeClass));
        }
    }
    else 
        globals->define(stmt->op.getLexeme(), value);
    return nullptr;
}
Any Interpreter::interpreter::visitWhileStmt(ContextFreeGrammar::While* stmt) {
    while (tO->isTruthy(evaluate(stmt->condition))) {
        execute(stmt->body);
    }
    return nullptr;
}
Any Interpreter::interpreter::visitAssignExpr(ContextFreeGrammar::Assign* expr) {
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
Any Interpreter::interpreter::visitIfStmt(ContextFreeGrammar::If* stmt) {
    Any res = evaluate(stmt->condition);
    if (tO->isTruthy(res)) {
        execute(stmt->thenBranch);
    } else if (stmt->elseBranch != nullptr) {
        execute(stmt->elseBranch);
    }
    return nullptr;
}
Any Interpreter::interpreter::visitLogicalExpr(ContextFreeGrammar::Logical* expr) {
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

Any Interpreter::interpreter::visitSuperExpr(ContextFreeGrammar::Super *expr) {
    int* distance = nullptr;
    try {
        if (locals.size() != 0)
            distance = new int(locals.count(expr));
        else 
            distance = nullptr;
    } catch(...) {}
    if (distance != nullptr) {
        NuclearLang::NukeClass* superclass = std::any_cast<NuclearLang::NukeClass*>(environment->getAt(
        *distance, String("super")));
        NuclearLang::NukeInstance* object = std::any_cast<NuclearLang::NukeInstance*>(environment->getAt(
        *distance - 1, String("this")));
        auto name = expr->method.getLexeme();
        NuclearLang::NukeFunction* method = superclass->findMethod(&name);
        if (method == nullptr) {
            throw runtimeerror<Interpreter::interpreter>(expr->method,  String("Undefined property '" + expr->method.getLexeme() + String("'.")).c_str());
        }
        return method->bind(object);
    }
    return nullptr;
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
bool Interpreter::interpreter::instanceof(const Any object) {
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