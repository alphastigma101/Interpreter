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
Assign::Assign(const Token& op_, Expr* right) {
    try { 
        this->right = std::move(right);
        this->op = std::move(op_); 
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
Arguments::Arguments(Expr* left, const Token& op_, Expr* right) {
    try { 
        this->left = std::move(left);
        this->right = std::move(right);
        this->op = std::move(op_); 
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
String Binary::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
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
    if (expr) result += expr->accept(this);
    return result + ")";
}
String Unary::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
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
    if (expr) result += expr->accept(this);
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
    String result = "(" + name;
    if (!stmt) return "(null)";
    if (initializer)
        result += initializer->accept(initializer);
    return result + ")";
}
String Print::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        return std::any_cast<String>(interp->visitPrintStmt(this));
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
    if (initializer) result += initializer->accept(initializer);
    return result + "))";
}
String Var::acceptHelper(Statement* visitor, bool tree) {
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
    if (initializer) result += initializer->accept(initializer);
    return result + "))";
}
String Expression::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        return std::any_cast<String>(interp->visitExpressionStmt(this));
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
    if (expr) result += expr->accept(this);
    return result + ")";
}
String Assign::acceptHelper(Expr* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        return std::any_cast<String>(interp->visitAssignExpr(this));
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
            result += "(Block"  + String("(") + " " + it->accept(this) + ")" + ")";
        else continue;
    }
    return result;
}
String Block::acceptHelper(Statement* visitor, bool tree) {
    if (tree) 
        return visit(this, true);
    else 
        interp->visitBlockStmt(this);
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