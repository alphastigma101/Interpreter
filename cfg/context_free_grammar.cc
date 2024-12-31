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
Literal::Literal(const Token&& oP) { this->op = std::move(oP); }

/** -----------------------------
 * @brief ...
 * 
 * @param Expr* Looks ahead to the left and gets whatever is on the left side of the = sign
 * @param oP
 * 
 * 
*/
Variable::Variable(const Token&& oP) { this->op = std::move(oP); }

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
ContextFreeGrammar::Call::Call(ContextFreeGrammar::Expr* callee, Token paren, Vector<ContextFreeGrammar::Expr*> arguments) {
    this->callee = std::move(callee);
    // Now create a thread that will run the for loop concurrently 
    for (auto& arg : arguments) {
        this->arguments.push_back(std::move(Any(arg)));
    }
    this->op = std::move(paren);

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
ContextFreeGrammar::Get::Get(ContextFreeGrammar::Expr* object_, Token op_)  {
   this->object = std::move(object_);
   this->op = std::move(op_);   
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
/** -----------------------------
 * @brief Creates a node called Print
 * 
 * @param initalizer A raw pointer that gets initalized with some kind of object
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Print::Print(ContextFreeGrammar::Expr* initalizer) { this->initializer = std::move(initalizer);  }

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
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Expression::Expression(ContextFreeGrammar::Expr* initalizer) { this->expression = std::move(initalizer);  }

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
Block::Block(Vector<ContextFreeGrammar::Statement*>&& left) { this->statements = std::move(left); }
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
Functions::Functions(Token name, Vector<Token> params, Vector<Statement*>& body) {
    this->op = std::move(name);
    this->params = std::move(params);
    //this->body
    this->statements = std::move(body);
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