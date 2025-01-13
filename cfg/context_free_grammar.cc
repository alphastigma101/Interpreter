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
ContextFreeGrammar::Binary::Binary(Expr* left_, const Token& op_, Expr* right_) {
    this->left = std::move(left_);
    this->right = std::move(right_);
    this->op = std::move(op_);
}

Any ContextFreeGrammar::Binary::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitBinaryExpr(dynamic_cast<ContextFreeGrammar::Binary*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitBinaryExpr(dynamic_cast<ContextFreeGrammar::Binary*>(this));
            } 
        return nullptr;
    #else 
        return nullptr;
    #endif 
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
ContextFreeGrammar::Unary::Unary(ContextFreeGrammar::Expr* right_, const Token op_)  {
   this->right = std::move(right_);
   this->op = std::move(op_);   
}

Any ContextFreeGrammar::Unary::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        //#pragma message "visitUnaryExpr is being compiled!"
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitUnaryExpr(dynamic_cast<ContextFreeGrammar::Unary*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitUnaryExpr(dynamic_cast<ContextFreeGrammar::Unary*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif  
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
ContextFreeGrammar::Grouping::Grouping(Expr* expression) { this->expression = std::move(expression); }

Any ContextFreeGrammar::Grouping::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        //#pragma message "visitGroupingExpr is being compiled!"
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitGroupingExpr(dynamic_cast<ContextFreeGrammar::Grouping*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*)) 
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitGroupingExpr(dynamic_cast<ContextFreeGrammar::Grouping*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif 
}

/** ---------------------------------------------------------------
 * @brief Initializes the op and constructs a node that gets pushed to a vector
 *
 * @param oP is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
ContextFreeGrammar::Literal::Literal(const Token oP) { this->op = std::move(oP); }

Any ContextFreeGrammar::Literal::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        //#pragma message "visitLiteralExpr is being compiled!"
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitLiteralExpr(dynamic_cast<ContextFreeGrammar::Literal*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*)) 
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitLiteralExpr(dynamic_cast<ContextFreeGrammar::Literal*>(this));
            }
        return nullptr;  
    #else 
        return nullptr;
    #endif
}

/** -----------------------------
 * @brief ...
 * 
 * @param Expr* Looks ahead to the left and gets whatever is on the left side of the = sign
 * @param oP
 * 
 * 
*/
ContextFreeGrammar::Variable::Variable(const Token&& oP) { this->op = std::move(oP); }

Any ContextFreeGrammar::Variable::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitVariableExpr(dynamic_cast<ContextFreeGrammar::Variable*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitVariableExpr(dynamic_cast<ContextFreeGrammar::Variable*>(this));
            }
        return nullptr;  
    #else 
        return nullptr;
    #endif
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Assign::Assign(const Token op_, ContextFreeGrammar::Expr* right) {
    this->right = std::move(right);
    this->op = std::move(op_); 
}
Any ContextFreeGrammar::Assign::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitAssignExpr(dynamic_cast<ContextFreeGrammar::Assign*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitAssignExpr(dynamic_cast<ContextFreeGrammar::Assign*>(this));
            }
        return nullptr; 
    #else 
        return nullptr;
    #endif
}
/** -----------------------------
 * @brief .....
 *
 *
 *
 * -------------------------------
 */
ContextFreeGrammar::Logical::Logical(ContextFreeGrammar::Expr* left_, const Token& op_, ContextFreeGrammar::Expr* right_) {
    this->left = std::move(left_);
    this->right = std::move(right_);
    this->op = std::move(op_);
}

Any ContextFreeGrammar::Logical::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitLogicalExpr(dynamic_cast<ContextFreeGrammar::Logical*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*)) 
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitLogicalExpr(dynamic_cast<ContextFreeGrammar::Logical*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif
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

Any ContextFreeGrammar::Call::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitCallExpr(dynamic_cast<ContextFreeGrammar::Call*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitCallExpr(dynamic_cast<ContextFreeGrammar::Call*>(this));
            }
        return nullptr; 
    #else 
        return nullptr;
    #endif  
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Set::Set(ContextFreeGrammar::Expr* object_, const Token op_, ContextFreeGrammar::Expr* value_) {
    this->object = std::move(object_);
    this->value = std::move(value_);
    this->op = std::move(op_);
}

Any ContextFreeGrammar::Set::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitSetExpr(dynamic_cast<ContextFreeGrammar::Set*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitSetExpr(dynamic_cast<ContextFreeGrammar::Set*>(this));
            }
        return nullptr; 
    #else 
        return nullptr;
    #endif
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

Any ContextFreeGrammar::Get::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        //#pragma message "visitGetExpr is being compiled!"
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitGetExpr(dynamic_cast<ContextFreeGrammar::Get*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitGetExpr(dynamic_cast<ContextFreeGrammar::Get*>(this));
            }
        return nullptr; 
    #else 
        return nullptr;
    #endif
}

/** ---------------------------------------------------------------
 * @brief Initializes the op and constructs a node that gets pushed to a vector
 *
 * @param oP is a indexed element from a vector of Token instances
 *
 * @details  A custom garbage collector is implemented to cleanup the raw pointers
 * ----------------------------------------------------------------
*/
ContextFreeGrammar::This::This(const Token oP) { this->op = std::move(oP); }

Any ContextFreeGrammar::This::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitThisExpr(dynamic_cast<ContextFreeGrammar::This*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitThisExpr(dynamic_cast<ContextFreeGrammar::This*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif
}

/** -----------------------------
 * @brief Creates a node called Print
 * 
 * @param initalizer A raw pointer that gets initalized with some kind of object
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Print::Print(ContextFreeGrammar::Expr* initalizer) { this->initializer = std::move(initalizer);  }

Any ContextFreeGrammar::Print::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        //#pragma message "Enabled visitPrintStmt!"
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitPrintStmt(dynamic_cast<ContextFreeGrammar::Print*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitPrintStmt(dynamic_cast<ContextFreeGrammar::Print*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif   
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Return::Return(const Token keyword, ContextFreeGrammar::Expr* value) {
    this->value = std::move(value);
    this->op = std::move(keyword); 
}

Any ContextFreeGrammar::Return::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        //#pragma message "visitReturnStatement is being compiled!"
        // TODO: Each visit method that contains a try and catch statement needs to either use typeid() or visitor.type()
        // This will help prevent any other try and accept statements being intercepted
        // TODO Move the visit methods inside the header and use directives to include the interpreter.h 
        if (visitor.type() == typeid(Interpreter::interpreter*)) {
            auto visit = std::any_cast<Interpreter::interpreter*>(visitor);
            return visit->visitReturnStmt(dynamic_cast<ContextFreeGrammar::Return*>(this));
        }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitReturnStmt(dynamic_cast<ContextFreeGrammar::Return*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Var::Var(const Token op, ContextFreeGrammar::Expr* initalizer) {
    this->initializer = std::move(initalizer);
    this->op = std::move(op);
}

Any ContextFreeGrammar::Var::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitVarStmt(dynamic_cast<ContextFreeGrammar::Var*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitVarStmt(dynamic_cast<ContextFreeGrammar::Var*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif 
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::While::While(ContextFreeGrammar::Expr* condition, ContextFreeGrammar::Statement* body) {
    this->condition = std::move(condition);
    this->body = std::move(body); 
}

Any ContextFreeGrammar::While::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitWhileStmt(dynamic_cast<ContextFreeGrammar::While*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitWhileStmt(dynamic_cast<ContextFreeGrammar::While*>(this));
            }
        return nullptr;
    #else
        return nullptr;
    #endif
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Expression::Expression(ContextFreeGrammar::Expr* initalizer) { this->expression = std::move(initalizer);  }

Any ContextFreeGrammar::Expression::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitExpressionStmt(dynamic_cast<ContextFreeGrammar::Expression*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitExpressionStmt(dynamic_cast<ContextFreeGrammar::Expression*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif 
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::Block::Block(Vector<ContextFreeGrammar::Statement*> left) { this->statements = std::move(left); }

Any ContextFreeGrammar::Block::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*)) 
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitBlockStmt(dynamic_cast<ContextFreeGrammar::Block*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitBlockStmt(dynamic_cast<ContextFreeGrammar::Block*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif
}

/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
ContextFreeGrammar::If::If(ContextFreeGrammar::Expr* cond, ContextFreeGrammar::Statement* thenbranch, ContextFreeGrammar::Statement* elsebranch) {
    this->condition = std::move(cond);
    this->thenBranch = std::move(thenbranch);
    this->elseBranch = std::move(elsebranch);
}

Any ContextFreeGrammar::If::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitIfStmt(dynamic_cast<ContextFreeGrammar::If*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitIfStmt(dynamic_cast<ContextFreeGrammar::If*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif
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
ContextFreeGrammar::Functions::Functions(Token name, Vector<Token> params, Vector<Statement*>& body) {
    this->op = std::move(name);
    this->params = std::move(params);
    //this->body
    this->statements = std::move(body);
}

Any ContextFreeGrammar::Functions::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitFunctionStmt(dynamic_cast<ContextFreeGrammar::Functions*>(this));
            }
        if (visitor.type() == typeid(Resolver::resolver*)) 
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitFunctionStmt(dynamic_cast<ContextFreeGrammar::Functions*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif 
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
ContextFreeGrammar::Class::Class(Token name, Vector<ContextFreeGrammar::Functions*> methods) {
    this->op = std::move(name);
    this->methods = std::move(methods);
}

Any ContextFreeGrammar::Class::visit(Any visitor) {
    #if ENABLE_VISITOR_PATTERN
        if (visitor.type() == typeid(Interpreter::interpreter*))
            if (auto visit = std::any_cast<Interpreter::interpreter*>(visitor)) {
                return visit->visitClassStmt(this);
            }
        if (visitor.type() == typeid(Resolver::resolver*))
            if (auto visit = std::any_cast<Resolver::resolver*>(visitor)) {
                return visit->visitClassStmt(dynamic_cast<ContextFreeGrammar::Class*>(this));
            }
        return nullptr;
    #else 
        return nullptr;
    #endif 
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
String ContextFreeGrammar::Binary::parenthesize(String name, Expr* left, Expr* right) {
    String result = "(" + name;
    if (left) {
        result += " " + std::any_cast<String>(left->accept(this));
    }
    if (right) {
        result += " " + std::any_cast<String>(right->accept(this));
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
String ContextFreeGrammar::Unary::parenthesize(String name, ContextFreeGrammar::Expr* expr) {
    String result = "(" + name + " ";
    if (expr) result += std::any_cast<String>(expr->accept(this));
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
String ContextFreeGrammar::Grouping::parenthesize(String name, Expr* expr) {
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
String ContextFreeGrammar::Print::parenthesize(String name, Statement* stmt) {
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
String ContextFreeGrammar::Var::parenthesize(String name, Statement* stmt) {
    if (!stmt) return "(null)";
    String result = "(Var" + String("(") + name + " ";
    if (initializer) result += std::any_cast<String>(initializer->accept(initializer));
    return result + "))";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String ContextFreeGrammar::Expression::parenthesize(String name, Statement* stmt) {
    if (!stmt) return "(null)";
    String result = "(Expression" + String("(") + name + " ";
    if (initializer) result += std::any_cast<String>(initializer->accept(initializer));
    return result + "))";
}
/** -----------------------------
 * @brief .....
 * 
 * 
 * 
 * -------------------------------
*/
String ContextFreeGrammar::Assign::parenthesize(String name, Expr* expr) {
    if (!expr) return "(null)";
    String result = "(" + name + " ";
    if (expr) result += std::any_cast<String>(expr->accept(this));
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
String ContextFreeGrammar::Block::parenthesize(Vector<ContextFreeGrammar::Statement*>&& expr) {
    String result;
    for (auto it : expr) {
        if (it) 
            result += "(Block"  + String("(") + " " + std::any_cast<String>(it->accept(this)) + ")" + ")";
        else continue;
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
String ContextFreeGrammar::Functions::parenthesize(String name, ContextFreeGrammar::Statement* left, ContextFreeGrammar::Statement* right) {
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
//String Import::parenthesize(String name, Expr* expr) {
    /*builder.append("(").append(name);
    for (Expr expr : exprs) {
      builder.append(" ");
      builder.append(expr.accept(this));
    }
    builder.append(")");

    return builder.toString();*/
    //return "\0";
//}