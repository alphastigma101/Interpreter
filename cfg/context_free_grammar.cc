#include <context_free_grammar.h>
#include <resolver.h>
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
//Any Binary::accept(Visitor<Any*> visitor) { return visit(visitor);}
Any Binary::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitBinaryExpr(dynamic_cast<ContextFreeGrammar::Binary*>(this));
        }
    }
    catch(...) {} 
    if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
        return visit->visitBinaryExpr(dynamic_cast<ContextFreeGrammar::Binary*>(this));
    }
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
ContextFreeGrammar::Unary::Unary(Expr* right_, const Token& op_)  {
   this->right = std::move(right_);
   this->op = std::move(op_);   
}
//Any Unary::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any Unary::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitUnaryExpr(dynamic_cast<ContextFreeGrammar::Unary*>(this));
        }
    }
    catch(...) {}
    // Check if the visitor is a Resolver
    if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
        return visit->visitUnaryExpr(dynamic_cast<ContextFreeGrammar::Unary*>(this));
    }
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
}
//Any ContextFreeGrammar::Grouping::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Grouping::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitGroupingExpr(dynamic_cast<ContextFreeGrammar::Grouping*>(this));
        }
    }
    catch(...) {}
    if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
        return visit->visitGroupingExpr(dynamic_cast<ContextFreeGrammar::Grouping*>(this));
    }
    return nullptr;  
}
/** ---------------------------------------------------------------
 * @brief Initializes the op and constructs a node that gets pushed to a vector
 *
 * @param oP is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
Literal::Literal(const Token&& oP) { this->op = std::move(oP); }
//Any ContextFreeGrammar::Literal::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Literal::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitLiteralExpr(dynamic_cast<ContextFreeGrammar::Literal*>(this));
        }
    }
    catch(...) {}
    if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
        return visit->visitLiteralExpr(dynamic_cast<ContextFreeGrammar::Literal*>(this));
    } 
    return nullptr; 
}
/** -----------------------------
 * @brief ...
 * 
 * @param Expr* Looks ahead to the left and gets whatever is on the left side of the = sign
 * @param oP
 * 
 * 
*/
Variable::Variable(const Token&& oP) { this->op = std::move(oP); }
//Any ContextFreeGrammar::Variable::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Variable::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitVariableExpr(dynamic_cast<ContextFreeGrammar::Variable*>(this));
        }
    }
    catch(...) {}
    if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
        return visit->visitVariableExpr(dynamic_cast<ContextFreeGrammar::Variable*>(this));
    } 
    return nullptr; 
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Assign::Assign(const Token& op_, Expr* right) {
    this->right = std::move(right);
    this->op = std::move(op_); 
}
//Any ContextFreeGrammar::Assign::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Assign::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitAssignExpr(dynamic_cast<ContextFreeGrammar::Assign*>(this));
        }
    }
    catch(...) {}
    if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
        return visit->visitAssignExpr(dynamic_cast<ContextFreeGrammar::Assign*>(this));
    } 
    return nullptr; 
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
//Any ContextFreeGrammar::Logical::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Logical::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitLogicalExpr(dynamic_cast<ContextFreeGrammar::Logical*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitLogicalExpr(dynamic_cast<ContextFreeGrammar::Logical*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
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
Call::Call(Expr* callee, Token paren, Vector<Expr*> arguments) {
    this->callee = std::move(callee);
    // Now create a thread that will run the for loop concurrently 
    for (auto& arg : arguments) {
        this->arguments.push_back(std::move(Any(arg)));
    }
    this->op = std::move(paren);

}
//Any ContextFreeGrammar::Call::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Call::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitCallExpr(dynamic_cast<ContextFreeGrammar::Call*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitCallExpr(dynamic_cast<ContextFreeGrammar::Call*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Set::Set(Expr* object_, const Token& op_, Expr* value_) {
    this->object = std::move(object_);
    this->value = std::move(value_);
    this->op = std::move(op_);
}
//Any ContextFreeGrammar::Set::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Set::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitSetExpr(dynamic_cast<ContextFreeGrammar::Set*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitSetExpr(dynamic_cast<ContextFreeGrammar::Set*>(this));
        }
    }
    catch(...) {} 
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
Get::Get(Expr* object_, Token op_)  {
   this->object = std::move(object_);
   this->op = std::move(op_);   
}
//Any ContextFreeGrammar::Get::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Get::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitGetExpr(dynamic_cast<ContextFreeGrammar::Get*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitGetExpr(dynamic_cast<ContextFreeGrammar::Get*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** ---------------------------------------------------------------
 * @brief Initializes the op and constructs a node that gets pushed to a vector
 *
 * @param oP is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
This::This(const Token&& oP) { this->op = std::move(oP); }

//Any ContextFreeGrammar::This::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::This::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitThisExpr(dynamic_cast<ContextFreeGrammar::This*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitThisExpr(dynamic_cast<ContextFreeGrammar::This*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** -----------------------------
 * @brief Creates a node called Print
 * 
 * @param initalizer A raw pointer that gets initalized with some kind of object
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Print::Print(ContextFreeGrammar::Expr* initalizer) {
    this->initializer = std::move(initalizer); 
}
//Any ContextFreeGrammar::Print::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Print::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitPrintStmt(dynamic_cast<ContextFreeGrammar::Print*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitPrintStmt(dynamic_cast<ContextFreeGrammar::Print*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Return::Return(const Token& keyword, Expr* value) {
    this->value = std::move(value);
    this->op = std::move(keyword); 
}
//Any ContextFreeGrammar::Return::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Return::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitReturnStmt(dynamic_cast<ContextFreeGrammar::Return*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitReturnStmt(dynamic_cast<ContextFreeGrammar::Return*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Var::Var(const Token& op, Expr* initalizer) {
    this->initializer = std::move(initalizer);
    this->op = std::move(op);
}
//Any ContextFreeGrammar::Var::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Var::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitVarStmt(dynamic_cast<ContextFreeGrammar::Var*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitVarStmt(dynamic_cast<ContextFreeGrammar::Var*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
While::While(Expr* condition, Statement* body) {
    this->condition = std::move(condition);
    this->body = std::move(body); 
}
//Any ContextFreeGrammar::While::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::While::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitWhileStmt(dynamic_cast<ContextFreeGrammar::While*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitWhileStmt(dynamic_cast<ContextFreeGrammar::While*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Expression::Expression(Expr* initalizer) { this->expression = std::move(initalizer);  }
//Any ContextFreeGrammar::Expression::accept(Visitor<Any*> visitor) { return visit(visitor); }

Any ContextFreeGrammar::Expression::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitExpressionStmt(dynamic_cast<ContextFreeGrammar::Expression*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitExpressionStmt(dynamic_cast<ContextFreeGrammar::Expression*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Block::Block(Vector<ContextFreeGrammar::Statement*>&& left) { this->statements = std::move(left); }
//Any ContextFreeGrammar::Block::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Block::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitBlockStmt(dynamic_cast<ContextFreeGrammar::Block*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitBlockStmt(dynamic_cast<ContextFreeGrammar::Block*>(this));
        }
    }
    catch(...) {}
    return nullptr; 
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
//Any ContextFreeGrammar::If::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::If::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitIfStmt(dynamic_cast<ContextFreeGrammar::If*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitIfStmt(dynamic_cast<ContextFreeGrammar::If*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
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
    //this->body
    this->statements = std::move(body);
}
//Any ContextFreeGrammar::Functions::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Functions::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitFunctionStmt(dynamic_cast<ContextFreeGrammar::Functions*>(this));
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitFunctionStmt(dynamic_cast<ContextFreeGrammar::Functions*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
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
Class::Class(Token name, Vector<ContextFreeGrammar::Functions*> methods) {
    this->op = std::move(name);
    this->methods = std::move(methods);
}
//Any ContextFreeGrammar::Class::accept(Visitor<Any*> visitor) { return visit(visitor); }
Any ContextFreeGrammar::Class::visit(Any visitor) {
    try {
        if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
            return visit->visitClassStmt(this);
        }
    }
    catch(...) {}
    try {
        if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
            return visit->visitClassStmt(dynamic_cast<ContextFreeGrammar::Class*>(this));
        }
    }
    catch(...) {} 
    return nullptr; 
}