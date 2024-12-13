#include <context_free_grammar.h>
#include <interpreter.h>
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
    }
    catch(...) {
        catcher<Variable> cl("Undefined behavior occurred in Class Variable!");
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
    }
    catch(...) {
        throw new catcher<Assign>("Undefined behavior occurred in Class Arguments!");
    }
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Logical::Logical(Expr* left_, const Token& op_, Expr* right_) {
    this->left = std::move(left_);
    this->right = std::move(right_);
    this->op = std::move(op_);
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
Call::Call(Expr* callee, Token& paren, Vector<Expr*> arguments) {
    this->callee = std::move(callee);
    // Now create a thread that will run the for loop concurrently 
    for (auto& arg : arguments) {
        this->arguments.push_back(std::move(Any(arg)));
    }
    this->op = std::move(paren);

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
Return::Return(const Token& keyword, Expr* value) {
    try { 
        this->value = std::move(value);
        this->op = std::move(keyword); 
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
While::While(Expr* condition, Statement* body) {
    try { 
        this->condition = std::move(condition);
        this->body = std::move(body); 
    }
    catch(...) {
        throw catcher<While>("Undefined behavior occurred in Class Statement!");
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
Block::Block(Vector<ContextFreeGrammar::Statement*>&& left) {
    try { 
        this->statements = std::move(left);
    }
    catch(...) {
        throw new catcher<Block>("Undefined behavior occurred in Class Arguments!");
    }
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
If::If(Expr* cond, Statement* thenbranch, Statement* elsebranch) {
    this->condition = std::move(cond);
    this->thenBranch = std::move(thenbranch);
    this->elseBranch = std::move(elsebranch);
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
Functions::Functions(Token& name, Vector<Token> params, Vector<Statement*>& body) {
    this->op = std::move(name);
    this->params = std::move(params);
    this->statements = std::move(body);
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
        result += " " + std::any_cast<String>(left->accept(this));
    }
    if (right) {
        result += " " + std::any_cast<String>(right->accept(this));
    }
    return result + ")";
}
Any Binary::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    return std::any_cast<String>(interp->visitBinaryExpr(this));
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
    if (expr) result += std::any_cast<String>(expr->accept(this));
    return result + ")";
}
Any Unary::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    return std::any_cast<String>(interp->visitUnaryExpr(this));
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
    if (expr) result += std::any_cast<String>(expr->accept(this));
    return result + ")";
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
    String result = "(" + name + " ";
    if (expr) result += std::any_cast<String>(expr->accept(this));
    return result + ")";
}
Any Assign::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    return std::any_cast<String>(interp->visitAssignExpr(this));
}

Any Variable::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    return interp->visitVariableExpr(this);
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
String Logical::parenthesize(String name, Expr* left, Expr* right) {
    String result = "(" + name;
    if (left) {
        result += " " + std::any_cast<String>(left->accept(this));
    }
    if (right) {
        result += " " + std::any_cast<String>(right->accept(this));
    }
    return result + ")";
}
Any Logical::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    return std::any_cast<String>(interp->visitLogicalExpr(this));
}
String Call::parenthesize(String name, Expr* left, Expr* right) {
    String result = "(" + name;
    if (left) {
        result += " " + std::any_cast<String>(left->accept(this));
    }
    if (right) {
        result += " " + std::any_cast<String>(right->accept(this));
    }
    return result + ")";
}
Any Call::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    return interp->visitCallExpr(this);
    
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String Print::parenthesize(String name, Statement* stmt) {
    String result = "(" + name;
    if (!stmt) return "(null)";
    if (initializer)
        result += std::any_cast<String>(initializer->accept(initializer));
    return result + ")";
}
Any Print::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        return interp->visitPrintStmt(this);
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
    String result = "(Var" + String("(") + name + " ";
    if (initializer) result += std::any_cast<String>(initializer->accept(initializer));
    return result + "))";
}
Any Var::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        interp->visitVarStmt(this);
    return "\0";
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
    String result = "(Expression" + String("(") + name + " ";
    if (initializer) result += std::any_cast<String>(initializer->accept(initializer));
    return result + "))";
}
Any Expression::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        return interp->visitExpressionStmt(this);
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
        if (it) 
            result += "(Block"  + String("(") + " " + std::any_cast<String>(it->accept(this)) + ")" + ")";
        else continue;
    }
    return result;
}
Any Block::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        interp->visitBlockStmt(this);
    return "\0";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String If::parenthesize(String name, Statement* stmt) {
    String result = "(" + name;
    if (!stmt) return "(null)";
    if (initializer)
        result += std::any_cast<String>(initializer->accept(initializer));
    return result + ")";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Any If::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        interp->visitIfStmt(this);
    return "\0";
}
String While::parenthesize(String name, Statement* left) {
    /*String result = "(" + name;
    if (left) {
        result += " " + left->accept(this);
    }
    if (right) {
        result += " " + right->accept(this);
    }
    return result + ")";*/
    return "\0";
}
Any While::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        interp->visitWhileStmt(this);
    return "\0";
}
String Functions::parenthesize(String name, Statement* left, Statement* right) {
    String result = "(" + name;
    if (left) {
        result += " " + std::any_cast<String>(left->accept(this));
    }
    if (right) {
        result += " " + std::any_cast<String>(right->accept(this));
    }
    return result + ")";
}
Any Functions::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    return interp->visitFunctionStmt(this);
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String Return::parenthesize(String name, Statement* stmt) {
    if (!stmt) return "(null)";
    String result = "(Var" + String("(") + name + " ";
    if (initializer) result += std::any_cast<String>(initializer->accept(initializer));
    return result + "))";
}
Any Return::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    interp->visitReturnStmt(this);
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