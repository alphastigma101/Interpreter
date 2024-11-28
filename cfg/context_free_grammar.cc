#include <context_free_grammar.h>
/** --------------------------------------------------------------------------
 * @brief This class will represent the Binary node tree in a absraction syntax tree
 *
 * @details it moves the left and right resources and the token resources that were passed into it 
 *          to it's own data members 
 *
 * @param left_ A raw pointer that holds a memory address to an object it points too
 * @param right_  A raw pointer that holds a memory address to an object it points too
 * @param op_ is an instance of the token class 
 * 
 * @details A custom garbage collector is implemented to cleanup the raw pointers
 *
 *
 * ---------------------------------------------------------------------------
*/
Binary::Binary(Expr* left_, const Token& op_, Expr* right_) {
    this->left = std::move(left_);
    this->right = std::move(right_);
    this->op = std::move(op_);
    auto binary = compressedAstTree(idx + 1, String("Binary"), this);
    cTree.push_back(std::move(binary));
}
//===============================================================================
//
//                              BINARY CRTP UTILITY SECTION
//
//===============================================================================
// 
// ┌─────────────────────────────────────────────────────────────────────────────┐
// │                                                                             │
// │  Purpose: Implements type checking and conversion functionality for the      │
// │           Binary expression type using CRTP (Curiously Recurring Template    │
// │           Pattern).                                                         │
// │                                                                             │
// │  Design Pattern: CRTP enables:                                             │
// │    - Static polymorphism                                                   │
// │    - Zero-overhead abstractions                                            │
// │    - Compile-time binding                                                  │
// │                                                                             │
// │  Usage: These utilities are inherited by the Unary expression class to      │
// │         provide type-safe operations without virtual function overhead.      │
// │                                                                             │
// └─────────────────────────────────────────────────────────────────────────────┘
//
//===============================================================================

/** --------------------------
 * @brief Used for evaluating nested expressions 
 * 
 * @param a Can be an object that represents the left side of the expression
 * @param b Can be an object that represents the right side of the expression
 *
 * @details Returns a implicity converted object 
*/
Any Binary::compute(Any& a, Any& b, auto& expr) { 
    switch (expr->op.getType()) {
        case TokenType::GREATER:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) > std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) > std::any_cast<int>(eval.toNumeric(b)));
            if (eval.instanceof<String>(a) && eval.instanceof<String>(b))
                return std::any_cast<String>(a) > std::any_cast<String>(b);
            return nullptr;
        case TokenType::GREATER_EQUAL:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) >= std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) >= std::any_cast<int>(eval.toNumeric(b)));
            if (eval.instanceof<String>(a) && eval.instanceof<String>(b)) 
                return std::any_cast<String>(a) >= std::any_cast<String>(b);
            return nullptr;
        case TokenType::LESS:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) < std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) < std::any_cast<int>(eval.toNumeric(b)));
            if (eval.instanceof<String>(a) && eval.instanceof<String>(b)) 
                return std::any_cast<String>(a) < std::any_cast<String>(b);
            return nullptr;
        case TokenType::LESS_EQUAL:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))  
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) <= std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) <= std::any_cast<int>(eval.toNumeric(b)));
            if (eval.instanceof<String>(a) && eval.instanceof<String>(b)) 
                return std::any_cast<String>(a) <= std::any_cast<String>(b);
            return nullptr;
        case TokenType::MINUS:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))  
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) - std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) - std::any_cast<int>(eval.toNumeric(b)));
            return nullptr;
        case TokenType::PLUS:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))  
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) + std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) + std::any_cast<int>(eval.toNumeric(b)));
            if (eval.instanceof<String>(a) && eval.instanceof<String>(b)) 
                return std::any_cast<String>(a) + std::any_cast<String>(b);
            return nullptr;
        case TokenType::SLASH:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))  
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) / std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) / std::any_cast<int>(eval.toNumeric(b)));
            return nullptr;
        case TokenType::STAR:
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))  
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) * std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) * std::any_cast<int>(eval.toNumeric(b)));
            return nullptr;
        case TokenType::BANG_EQUAL: 
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))  
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) != std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) != std::any_cast<int>(eval.toNumeric(b)));
            return nullptr;
        case TokenType::EQUAL_EQUAL: 
            if (eval.instanceof<double>(a) && eval.instanceof<double>(b))  
                return std::to_string(std::any_cast<double>(eval.toNumeric(a)) == std::any_cast<double>(eval.toNumeric(b)));
            if (eval.instanceof<int>(a) && eval.instanceof<int>(b))
                return std::to_string(std::any_cast<int>(eval.toNumeric(a)) == std::any_cast<int>(eval.toNumeric(b)));
            return nullptr;

    }
    return nullptr;
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
template<class T>
bool Binary::instanceof(const Any& object) {
    try {
        if (isNumeric<T>(object)) return true;
        else if (isOther<T>(object)) return true;
    } catch (...) {
        return false;
    }
    return false;
}
/** --------------------------
 * @brief A generic method that, for now, checks for double and integer types
 * 
 * @param value Is an any container that will always hold a string value.
 * 
 * @details In order to support more types in the near future especially if it is numeric values,
 *          it should be iplemented in this method or in the isOther and toOther methods
*/
template<class T>
bool Binary::isNumeric(const Any value) {
    try {
        String temp = std::move(std::any_cast<String>(value));
        for (int i = 0; i < temp.length() - 1; i++) {
            if (temp[i] == '.') {
                try {
                    if (typeid(std::stod(temp)) == typeid(T)) return true;
                    return false;
                }
                catch(...) { return false; }
                return true;
            }
        }
        try {
            if (typeid(std::stoi(temp)) == typeid(T)) return true;
            return false;
        }
        catch(...) { return false; }
    } catch (...) { return false; }
    return false;    
}
/** ---------------------------------------------------------------
 * @brief A simple method that converts the parameter object into a supported type
 *
 * @param value Some kind of value that must be a supported type
 *
 * @details The supported types are double for more precision and integer. 
 * ----------------------------------------------------------------
*/
Any Binary::toNumeric(Any& value) {
    try {
        String temp = std::any_cast<String>(value);
        for (int i = 0; i < temp.length() - 1; i++) {
            if (temp[i] == '.') {
                try {
                    return std::stod(temp);
                }
                catch(...) { return nullptr; }
            }
        }
        try {
            return std::stoi(temp);
        }
        catch(...) { return nullptr; }
    } catch (...) { return nullptr; }
    return nullptr;
}
/** --------------------------------------------
 * @brief A simple but yet, complex method that accesses Tatical Nuke's struct for conversion
 * 
 * @param lhs Is an any container that will always have a string value inside of it
 * @param rhs Is an any container that will always have a string value inside of it
 * 
 * @cond If lhs and rhs are either a list or map, it will be stored in one any container.
 * 
 * @details ...
 * 
 * @return Returns a complex any container that will hold two values 
 * 
*/
Any Binary::toOther(Any& lhs, Any& rhs) {
    /*auto toList = [](String& temp) -> Any {
        try {
            if (temp.front() == '[' && temp.back() == ']') {
                // Remove brackets and trim whitespace
                String content = temp.substr(1, temp.length() - 2);
                content.erase(0, content.find_first_not_of(" \t\n\r"));
                content.erase(content.find_last_not_of(" \t\n\r") + 1);
            
                // Remove quotes from content if they exist
                if (content.front() == '"' && content.back() == '"') {
                    content = content.substr(1, content.length() - 2);
                }
            
                // Dynamically allocate new list with the processed content
                return new Nuke::core::list{content};
            }
            else 
                return nullptr;
        }
        catch(...) { return nullptr; }
        return nullptr; 
    };
    try {
        Any res = std::make_any<String>(std::any_cast<String>(toList(lhs)), std::any_cast<String>(toList(rhs)));
        if (res.has_value()) return std::any_cast<String>(res);
        return nullptr; 
    }
    catch(...) { return nullptr; }
    auto toMap = [](String& temp) -> Any {
        try {
            if (temp.front() == '{' && temp.back() == '}') {
                // Remove brackets and trim whitespace
                String content = temp.substr(1, temp.length() - 2);
                content.erase(0, content.find_first_not_of(" \t\n\r"));
                content.erase(content.find_last_not_of(" \t\n\r") + 1);
            
                // Remove quotes from content if they exist
                if (content.front() == '"' && content.back() == '"') {
                    content = content.substr(1, content.length() - 2);
                }
            
                // Dynamically allocate new list with the processed content
                return new Nuke::core::dict{content};
            }
            else 
                return nullptr;
        }
        catch(...) { return nullptr; }
        return nullptr; 
    };
    try {  
        Any res = std::make_any<String>(std::any_cast<String>(toMap(lhs)), std::any_cast<String>(toMap(rhs)));
        if (res.has_value()) return std::any_cast<String>(res);
        return nullptr; 
    }
    catch(...) { return nullptr; }*/
    return nullptr;
}
   
/** --------------------------------------------------------------------------
 * @brief This class will represent the Binary node tree in a absraction syntax tree
 *
 * @details it moves the right resources and the token resources that were passed into it 
 *          to it's own data members 
 *
 * @param right_ A raw pointer that holds a memory address to an object it points too
 * @param op_ is a indexed element from a vector of token instances 
 *
 * @details A custom garbage collector is implemented to cleanup the raw pointers
 *
 * ---------------------------------------------------------------------------
*/
Unary::Unary(Expr* right_, const Token& op_)  {
   this->right = std::move(right_);
   this->op = std::move(op_);
   auto unary = compressedAstTree(idx + 1, String("Unary"), this);
   cTree.push_back(std::move(unary));
}
//===============================================================================
//
//                             UNARY CRTP UTILITY SECTION
//
//===============================================================================
// 
// ┌─────────────────────────────────────────────────────────────────────────────┐
// │                                                                             │
// │  Purpose: Implements type checking and conversion functionality for the      │
// │           Unary expression type using CRTP (Curiously Recurring Template    │
// │           Pattern).                                                         │
// │                                                                             │
// │  Design Pattern: CRTP enables:                                             │
// │    - Static polymorphism                                                   │
// │    - Zero-overhead abstractions                                            │
// │    - Compile-time binding                                                  │
// │                                                                             │
// │  Usage: These utilities are inherited by the Unary expression class to      │
// │         provide type-safe operations without virtual function overhead.      │
// │                                                                             │
// └─────────────────────────────────────────────────────────────────────────────┘
//
//===============================================================================
/** -----------------------------
 * @brief A method that will evaluate the nested expressions within the expression
 * 
 * @param a Is an any container that will always hold a string value.
 *          But, because this is unary, the value will always be "\0"
 * @param b Is an any container that will always hold a string value.
 * 
 * @param expr Is the abstracted class called Expr that will visit the Literal class tree and return a value 
 * 
 * @details .....
 * 
 * @return A simple any container holding a string value that is not null
 * 
*/
Any Unary::compute(Any& a, Any& b, auto& expr) {
    try { 
        switch (expr->op.getType()) {
            case TokenType::BANG:
                //return !isTruthy(right);
                break;
            case TokenType::MINUS:
                if (eval.instanceof<double>(b))
                    return std::to_string(-std::any_cast<double>(eval.toNumeric(b)));
                if (eval.instanceof<int>(b)) return std::to_string(-std::any_cast<int>(eval.toNumeric(b)));
            auto& [intVal, pairVal] = cTree.at(currentEnvEle);
            if (std::holds_alternative<Expr*>(pairVal.second)) {
                auto& conv = std::get<Expr*>(pairVal.second);
                throw new runtimeerror<Unary>(
                    expr->op.getType(), String("In Unary compute method: " + String("\n\t") + 
                    String("Invalid type detected during evaluations: ")  + String("\n\t") + String(conv->op.getLexeme())).c_str()
                );
            }
        }
    }
    catch(runtimeerror<Unary>& e) {
        std:: cout << "Logs have been updated!" << std::endl;
        logging<Unary> logs(logs_, e.what(e.getType<TokenType>(), e.getMsg()));
        logs.update();
        logs.rotate();
    }
    return nullptr;
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
template<class T>
bool Unary::instanceof(const Any& object) {
    try {
        if (isNumeric<T>(object)) return true;
        else if (isOther<T>(object)) return true;
    } catch (...) {
        return false;
    }
    return false;
}
/** ---------------------------------------------------------------
 * @brief A simple method that converts the parameter object into a supported type
 *
 * @param value Some kind of value that must be a supported type
 *
 * @details The supported types are double for more precision and integer. 
 * ----------------------------------------------------------------
*/
template<class T>
bool Unary::isNumeric(const Any value) {
    try {
        String temp = std::move(std::any_cast<String>(value));
        for (int i = 0; i < temp.length() - 1; i++) {
            // TODO: Here is a bug. Both float and double both have . in it 
            // Need to absolutely make sure it is a double or a float
            if (temp[i] == '.') {
                try {
                    if (typeid(std::stod(temp)) == typeid(T)) return true;
                    return false;
                }
                catch(...) { return false; }
                return true;
            }
        }
        try {
            if (typeid(std::stoi(temp)) == typeid(T)) return true;
            return false;
        }
        catch(...) { return false; }
    } catch (...) { return false; }
    return false;    
}
/** ---------------------------------------------------------------
 * @brief A simple method that converts the parameter object into a supported type
 *
 * @param value Some kind of value that must be a supported type
 *
 * @details The supported types are double for more precision and integer. 
 * ----------------------------------------------------------------
*/
Any Unary::toNumeric(Any& value) {
    try {
        String temp = std::any_cast<String>(value);
        for (int i = 0; i < temp.length() - 1; i++) {
            if (temp[i] == '.') {
                try {
                    return std::stod(temp);
                }
                catch(...) { return nullptr; }
            }
        }
        try {
            return std::stoi(temp);
        }
        catch(...) { return nullptr; }
    } catch (...) { return nullptr; }
    return nullptr;
}
/** --------------------------------------------
 * @brief A simple but yet, complex method that accesses Tatical Nuke's struct for conversion
 * 
 * @param lhs Is an any container that will always have a string value inside of it.
 *            However, because it is unary expressions, the 'lhs' will be "\0"
 * @param rhs Is an any container that will always have a string value inside of it.
 *            However, this will not contain "\0"
 * 
 * @cond lhs holds "\0" while rhs container does not. So it shall return an any container.
 * 
 * @details ...
 * 
 * @return Returns a complex any container that will hold two values 
 * 
*/
Any Unary::toOther(Any& lhs, Any& rhs) {
    /*auto toList = [](String& temp) -> Any {
        try {
            if (temp.front() == '[' && temp.back() == ']') {
                // Remove brackets and trim whitespace
                String content = temp.substr(1, temp.length() - 2);
                content.erase(0, content.find_first_not_of(" \t\n\r"));
                content.erase(content.find_last_not_of(" \t\n\r") + 1);
            
                // Remove quotes from content if they exist
                if (content.front() == '"' && content.back() == '"') {
                    content = content.substr(1, content.length() - 2);
                }
            
                // Dynamically allocate new list with the processed content
                return new Nuke::core::list{content};
            }
            else 
                return nullptr;
        }
        catch(...) { return nullptr; }
        return nullptr; 
    };
    try {
        Any res = std::make_any<String>(std::any_cast<String>(toList(lhs)), std::any_cast<String>(toList(rhs)));
        if (res.has_value()) return std::any_cast<String>(res);
        return nullptr; 
    }
    catch(...) { return nullptr; }
    auto toMap = [](String& temp) -> Any {
        try {
            if (temp.front() == '{' && temp.back() == '}') {
                // Remove brackets and trim whitespace
                String content = temp.substr(1, temp.length() - 2);
                content.erase(0, content.find_first_not_of(" \t\n\r"));
                content.erase(content.find_last_not_of(" \t\n\r") + 1);
            
                // Remove quotes from content if they exist
                if (content.front() == '"' && content.back() == '"') {
                    content = content.substr(1, content.length() - 2);
                }
            
                // Dynamically allocate new list with the processed content
                return new Nuke::core::dict{content};
            }
            else 
                return nullptr;
        }
        catch(...) { return nullptr; }
        return nullptr; 
    };
    try {  
        Any res = std::make_any<String>(std::any_cast<String>(toMap(lhs)), std::any_cast<String>(toMap(rhs)));
        if (res.has_value()) return std::any_cast<String>(res);
        return nullptr; 
    }
    catch(...) { return nullptr; }*/
    return nullptr;
}
/** ---------------------------------------------------------------
 * @brief Initializes the expression_ and moves the resources into it 
 *
 * @param expression A raw pointer that holds a memory address to an object it points too
 * @param oP is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
Grouping::Grouping(Expr* expression) {
    this->expression = std::move(expression);
    auto grouping = compressedAstTree(idx + 1, String("Grouping"), this);
    cTree.push_back(std::move(grouping));
}
/** ---------------------------------------------------------------
 * @brief Initializes the op and constructs a node that gets pushed to a vector
 *
 * @param oP is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
Literal::Literal(const Token&& oP) {
    try { 
        this->op = std::move(oP); 
        auto literal = compressedAstTree(idx + 1, String("Literal"), this);
        cTree.push_back(std::move(literal));
    }
    catch(...) {
        catcher<Literal> cl("Undefined behavior occurred in Class Literal!");
        throw cl;
    }
}
/** -----------------------------
 * @brief ...
 * 
 * @param Expr* Looks ahead to the left and gets whatever is on the left side of the = sign
 * @param oP
 * 
 * 
*/
Variable::Variable(const Token&& oP) {
    try { 
        this->op = std::move(oP); 
        auto var = compressedAstTree(idx + 1, String("Variable"), this);
        cTree.push_back(std::move(var));
    }
    catch(...) {
        catcher<Variable> cl("Undefined behavior occurred in Class Variable!");
        throw cl;
    }
}
/** -----------------------------
 * @brief Creates a node called Print
 * 
 * @param initalizer A raw pointer that gets initalized with some kind of object
 * 
 * 
 * -------------------------------
*/
Print::Print(Expr* initalizer) {
    try { 
        this->initializer = std::move(initalizer); 
        //auto stmt = compressedAstTree(idx + 1, String("Print"), this);
        //cTree.push_back(std::move(stmt));
    }
    catch(...) {
        catcher<Print> cl("Undefined behavior occurred in Class Statement!");
        throw cl;
    }
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Var::Var(const Token& op, Expr* initalizer) {
    try { 
        this->initializer = std::move(initalizer);
        this->op = std::move(op); 
        //auto stmt = compressedAstTree(idx + 1, String("Var"), this);
        //cTree.push_back(std::move(stmt));
    }
    catch(...) {
        catcher<Print> cl("Undefined behavior occurred in Class Statement!");
        throw cl;
    }
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Expression::Expression(Expr* initalizer) {
    try { 
        this->initializer = std::move(initalizer); 
        //auto stmt = compressedAstTree(idx + 1, String("Expression"), this);
        //cTree.push_back(std::move(stmt));
    }
    catch(...) {
        catcher<Print> cl("Undefined behavior occurred in Class Statement!");
        throw cl;
    }
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Assign::Assign(const Token& op_, Expr* right) {
    try { 
        this->right = std::move(right);
        this->op = std::move(op_); 
        auto assign = compressedAstTree(idx + 1, String("Assign"), this);
        cTree.push_back(std::move(assign));
    }
    catch(...) {
        throw new catcher<Arguments>("Undefined behavior occurred in Class Arguments!");
    }
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Block::Block(Vector<ContextFreeGrammar::Statement*>&& left) {
    try { 
        this->statements = std::move(left);
    }
    catch(...) {
        throw new catcher<Block>("Undefined behavior occurred in Class Arguments!");
    }
}
/** --------------------------------------------------------------------------
 * @brief This class will represent the Function node tree in a absraction syntax tree
 *
 * @details it moves the left and right resources and the token resources that were passed into it 
 *          to it's own data members 
 *
 * @param left_ A raw pointer that holds a memory address to an object it points too
 * @param right_  A raw pointer that holds a memory address to an object it points too
 * @param op_ is an instance of the token class 
 * 
 * @details A custom garbage collector is implemented to cleanup the raw pointers
 *
 *
 * ---------------------------------------------------------------------------
*/
Functions::Functions(Expr* left_, const Token& op_, Expr* right_) {
    this->left = std::move(left_);
    this->right = std::move(right_);
    this->op = std::move(op_);
    auto functions = compressedAstTree(idx + 1, String("Functions"), this);
    cTree.push_back(std::move(functions));
}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param meth ...
 * @param op_ is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
Methods::Methods(Expr* method, const Token& op_) {
    try { 
        this->op = std::move(op_); 
        auto literal = compressedAstTree(idx + 1, String("Methods"), this);
        cTree.push_back(std::move(literal));
    }
    catch(...) {
        catcher<Methods> cl("Undefined behavior occurred in Class Methods!");
        throw cl;
    }

}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param meth ...
 * @param op_ is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
Arguments::Arguments(Expr* left, const Token& op_, Expr* right) {
    try { 
        this->left = std::move(left);
        this->right = std::move(right);
        this->op = std::move(op_); 
        auto stmt = compressedAstTree(idx + 1, String("Arguments"), this);
        cTree.push_back(std::move(stmt));
    }
    catch(...) {
        throw new catcher<Arguments>("Undefined behavior occurred in Class Arguments!");
    }
}

/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param meth ...
 * @param op_ is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
EcoSystem::EcoSystem(Expr* ecoSystem, const Token& op_) {}
// Helper methods for constructing the AST
//
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String Binary::parenthesize(String name, Expr* left, Expr* right) {
    String result = "(" + name;
    if (left) {
        result += " " + left->accept(this);
    }
    if (right) {
        result += " " + right->accept(this);
    }
    return result + ")";
}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String Unary::parenthesize(String name, Expr* expr) {
    String result = "(" + name + " ";
    if (expr) result += expr->accept(this);
    return result + ")";
}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String Grouping::parenthesize(String name, Expr* expr) {
    String result = "(" + name + " ";
    if (expr) result += expr->accept(this);
    return result + ")";
}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String Variable::parenthesize(String name, Expr* left) {
    String result = "(" + name;
    if (left) {
        result += " " + left->accept(this);
    }
    return result + ")";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String Print::parenthesize(String name, Statement* stmt) {
    if (!stmt) return "(null)";
    return "(Print " + 
          (stmt->initializer ? 
           "(" + stmt->initializer->op.getTypeStr() + " " + 
           stmt->initializer->op.getLexeme() + ")" : 
           "()") + 
          ")";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String Var::parenthesize(String name, Statement* stmt) {
    if (!stmt) return "(null)";
    return "(" + name + " statement)";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String Expression::parenthesize(String name, Statement* stmt) {
    if (!stmt) return "(null)";   
    return "(" + name + " statement)";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String Assign::parenthesize(String name, Expr* expr) {
    if (!expr) return "(null)";
    return "(" + name + " " + expr->op.getLexeme() + ")";
}

/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String Block::parenthesize(Vector<ContextFreeGrammar::Statement*>&& expr) {
    String result;
    for (auto& it : expr) {
        result += "(" + it->op.getTypeStr() + "(" + " " + it->accept(this) + ")" + ")";
    }
    return result;
}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String Methods::parenthesize(String name, Expr* expr) {
    /*builder.append("(").append(name);
    for (Expr expr : exprs) {
      builder.append(" ");
      builder.append(expr.accept(this));
    }
    builder.append(")");

    return builder.toString();*/
    return "\0";
}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String Arguments::parenthesize(String name, Expr* expr) {
    /*builder.append("(").append(name);
    for (Expr expr : exprs) {
      builder.append(" ");
      builder.append(expr.accept(this));
    }
    builder.append(")");

    return builder.toString();*/
    return "\0";
}
/** ---------------------------------------------------------------
 * @brief ...
 *
 * @param name ...
 * @param left ...
 * @param right ...
 *
 * @details .....
 * ----------------------------------------------------------------
*/
String EcoSystem::parenthesize(String name, Expr* expr) {
    /*builder.append("(").append(name);
    for (Expr expr : exprs) {
      builder.append(" ");
      builder.append(expr.accept(this));
    }
    builder.append(")");

    return builder.toString();*/
    return "\0";
}