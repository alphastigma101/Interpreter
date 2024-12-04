#include <interpreter.h>
#include <return.h>
Environment::environment* interpreter::globals = new Environment::environment();

interpreter::interpreter() {
    globals->define("launch", new NuclearLang::Nuke<interpreter>());
    // TODO Need to also add other functions like fussion and fission
    // One is for concating and the other is for splitting

}

Any interpreter::call(Interpreter::interpreter* interpreter, Vector<Any>& arguments) {
    //return launch();
    launch();
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
        std::cout << "Logs have been updated!" << std::endl;
        logging<interpreter> logs(e.what(e.getType<TokenType>(), e.getMsg()));
        logs.rotate();
        logs_ = logs.getLogs();
    }                              
}
/** ------------------------------------------------
 * @brief Calls the accept method to begin the recrusive tree walk
 * 
 * @param temp A type safe union that is useful to return multiple types inside a conatinaer 
 * 
 */
Any interpreter::evaluate(ContextFreeGrammar::Expr* conv) {
    if (auto call = dynamic_cast<Call*>(conv)) return conv->accept(call, false);
    if (auto binary = dynamic_cast<Binary*>(conv)) return conv->accept(binary, false);
    else if (auto literal = dynamic_cast<Literal*>(conv)) return conv->accept(literal, false);
    else if (auto unary = dynamic_cast<Unary*>(conv)) return conv->accept(unary, false);
    else if (auto grouping = dynamic_cast<Grouping*>(conv)) return conv->accept(grouping, false);
    else if (auto assign = dynamic_cast<Assign*>(conv)) return conv->accept(assign, false);
    else if (auto logic = dynamic_cast<Logical*>(conv)) return conv->accept(logic, false);
    else if (auto var = dynamic_cast<Variable*>(conv)) return conv->accept(var, false);
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
            arguments.push_back(evaluate(std::any_cast<Expr*>(it)));
        }
        catch(...) {
            throw runtimeerror<interpreter>(expr->op, "Failed to convert one of the elements in arguments into Expr*");
        }
    }
    if (!(instanceof<NuclearLang::Nuke<interpreter>>(callee))) {
      throw runtimeerror<interpreter>(expr->paren,
          "Can only call functions and classes.");
    }
    auto function = std::any_cast<NuclearLang::Nuke<interpreter>*>(callee);
    if (arguments.size() != function->arity()) {
      throw runtimeerror<interpreter>(expr->paren, String("Expected " +
          std::to_string(function->arity()) + " arguments but got " +
          std::to_string(arguments.size()) + ".").c_str());
    }
    //return function->call(this, arguments);
    return "\0";
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
Any interpreter::visitExpressionStmt(ContextFreeGrammar::Expression* stmt) {
    if (auto conv = dynamic_cast<Expression*>(stmt))
        evaluate(conv->initializer->expression);
    return "\0";
}
Any interpreter::visitFunctionStmt(ContextFreeGrammar::Functions* stmt) {
    NukeFunction* function = new NukeFunction(stmt, environment);
    environment->define(stmt->op.getLexeme(), function);
    return "\0";
}

Any interpreter::visitPrintStmt(ContextFreeGrammar::Print* stmt) {
    if (auto conv = dynamic_cast<Print*>(stmt))
        globals->define("radiate", evaluate(conv->initializer));
    //TODO: It should be returning nullptr, but accept needs specifier needs to be changed to Any 
    //return nullptr;
    return "\0";
}
void interpreter::visitReturnStmt(ContextFreeGrammar::Return* stmt) {
    Any value = nullptr;
    if (stmt->value != nullptr) value = evaluate(stmt->value);
    throw new NukeReturn(value);
}
Any interpreter::visitVariableExpr(ContextFreeGrammar::Variable* expr) {
    if (auto conv = dynamic_cast<Variable*>(expr))
        return globals->get(expr->op);
    throw catcher<interpreter>("Data member of interpreter 'visitVariableExpr', failed to convert its parameter into Variable class!");
}
void interpreter::visitVarStmt(ContextFreeGrammar::Var* stmt) {
    Any value = nullptr;
    if (stmt->initializer != nullptr) {
      value = evaluate(stmt->initializer);
    }
    globals->define(stmt->op.getLexeme(), value);
    return;
}
void interpreter::visitWhileStmt(ContextFreeGrammar::While* stmt) {
    Any res = evaluate(stmt->condition);
    while (isTruthy(res)) {
        execute(stmt->body);
    }
    return;
}
Any interpreter::visitAssignExpr(ContextFreeGrammar::Assign* expr) {
    Any value = evaluate(expr->expression);
    globals->assign(expr->op, value);
    return value;
}
void interpreter::visitIfStmt(ContextFreeGrammar::If* stmt) {
    Any res = evaluate(stmt->condition);
    if (isTruthy(res)) {
        execute(stmt->thenBranch);
    } else if (stmt->elseBranch != nullptr) {
        execute(stmt->elseBranch);
    }
    return;
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
void interpreter::moveCursor(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void interpreter::drawStickFigures() {
    std::cout << "   O   O   \n";
    std::cout << "   |   |   \n";
    std::cout << "   |   |   \n";
    std::cout << "  / \\ / \\  \n";
    std::cout << "-------------\n";
}

void interpreter::drawNuke(int height) {
    // Print spaces to position the nuke
    for (int i = 0; i < height; i++) {
        std::cout << std::endl;
    }
    std::cout << "            '--' \n";
    std::cout << "           /_____\\\n";
    std::cout << "           |     |\n";
    std::cout << "           |     |\n";
    std::cout << "           |_____|\n";
    std::cout << "           |     |\n";
    std::cout << "           |     |\n";
    std::cout << "            \\   /\n";
    std::cout << "             | |\n";
    std::cout << "             | |\n";
    std::cout << "             | |\n";
    std::cout << "             | |\n";
    std::cout << "           /     \\\n";
    std::cout << "          |_______|\n";
    std::cout << "          |       |\n";
    std::cout << "           \\_|__/ \n";
    std::cout << "            \\ | /\n";
    std::cout << "             \\|/ \n";
}

void interpreter::drawExplosion() {
    std::cout << "       . . .      \n";
    std::cout << "     . . . . .    \n";
    std::cout << "   . . . . . . .  \n";
    std::cout << " . . . . . . . . .\n";
    std::cout << "     . . . . .    \n";
    std::cout << "       . . .      \n";
}

void interpreter::clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
}
void interpreter::drawMiniatureNuke(int x, int y) {
    moveCursor(x, y);
    std::cout << "  '--'  \n";
    std::cout << " /_____\\\n";
    std::cout << " |     |\n";
    std::cout << " |     |\n";
    std::cout << " |_____|\n";
    std::cout << " |     |\n";
    std::cout << " |     |\n";
    std::cout << "  \\   /\n";
    std::cout << "   | |\n";
    std::cout << "   | |\n";
    std::cout << "   | |\n";
    std::cout << "   | |\n";
    std::cout << " /     \\\n";
    std::cout << "|_______|\n";
    std::cout << "|       |\n";
    std::cout << " \\_|__/ \n";
    std::cout << "  \\ | /\n";
    std::cout << "   \\|/ \n";
}

void interpreter::drawMiniatureNukeGrid(int numRows, int numCols) {
    int spacing = 6; // Space between each nuke

    for (int y = 0; y < numRows; y++) {
        for (int x = 0; x < numCols; x++) {
            drawMiniatureNuke(x * spacing, y * spacing);
        }
    }
}

void interpreter::launch() {
    int nukeDropHeight = 20;  // Increased height for better visibility
    int groundLevel = 25;     // Position where stick figures will be drawn

    clearScreen();
    
    // Draw stick figures at fixed position
    moveCursor(0, groundLevel);
    drawStickFigures();

    // Simulate dropping
    for (int i = 0; i < 15; i++) {
        // Clear previous position of falling object
        moveCursor(0, i - 1);
        std::cout << String(20, ' ') << std::endl;  // Clear previous position, this is not working!
        
        // Draw falling object at new position
        moveCursor(0, i);
        drawNuke(0);
        //drawMiniatureNukeGrid(i, i);
        
        
        // Redraw stick figures (they stay in place)
        moveCursor(0, groundLevel);
        drawStickFigures();
        if (i == groundLevel) break;
        
        //this_thread::sleep_for(chrono::milliseconds(500));
    }
    // Draw explosion where the stick figures were
    clearScreen();
    drawExplosion();
    return;
}