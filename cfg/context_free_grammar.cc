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
    //cTree.insert(std::move(binary));
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
   //cTree.insert(std::move(unary));
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
    //cTree.insert(std::move(grouping));
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
        //cTree.insert(std::move(literal));
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
        //cTree.insert(std::move(var));
    }
    catch(...) {
        catcher<Variable> cl("Undefined behavior occurred in Class Variable!");
        throw cl;
    }
}
/** -----------------------------
 * @brief Creates a node called Statement
 * 
 * @param initalizer A raw pointer that gets initalized with some kind of object
 * @param oP A class instance that holds getter methods to get the lexeme or literal
 * 
 * 
 * -------------------------------
*/
Statement::Statement(Expr* initalizer, const Token&& oP) {
    try { 
        this->op = std::move(oP); 
        auto stmt = compressedAstTree(idx + 1, String("Statement"), this);
        //cTree.insert(std::move(stmt));
    }
    catch(...) {
        catcher<Statement> cl("Undefined behavior occurred in Class Statement!");
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
Methods::Methods(Expr* meth, const Token& op_) {
    try { 
        this->op = std::move(op_); 
        auto literal = compressedAstTree(idx + 1, String("Methods"), this);
        //cTree.insert(std::move(literal));
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
        //cTree.insert(std::move(stmt));
    }
    catch(...) {
        catcher<Arguments> cl("Undefined behavior occurred in Class Arguments!");
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
EcoSystem::EcoSystem(Expr* ecoSystem, const Token& op_) {


}
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
String Variable::parenthesize(String name, Expr* left, Expr* right) {
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