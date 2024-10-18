#include <interpreter.h>
#include <abstraction_tree_syntax.h>
/** -------------------------------------------------
 * @brief Calls in evaluate mehtod to begin the evaluation 
 * 
*/
interpreter::interpreter(Set<astTree<int, String, ExprVariant>>& expr) {
    try {
        for (auto& it : expr) {
            auto& [intVal, pairVal] = it;
            if (pairVal.first == "Binary") {
                if (std::holds_alternative<Expr*>(pairVal.second)) {
                    auto& conv = std::get<Expr*>(pairVal.second);
                    if (auto binary = dynamic_cast<Binary*>(conv)) {
                        evaluatedExpressions.push_back(std::move(std::any_cast<String>(visitBinaryExpr(binary))));
                    }   
                }
            }
            if (pairVal.first == "Statement") {
                if (std::holds_alternative<Expr*>(pairVal.second)) {
                    auto& conv = std::get<Expr*>(pairVal.second);
                    //if (auto stmt = dynamic_cast<Statement*>(conv))
                       //value.insert(std::any_cast<String>(visitStmtExpr(stmt)));
                }
            }
            if (pairVal.first == "EcoSystem") {
                if (std::holds_alternative<Expr*>(pairVal.second)) {
                    auto& conv = std::get<Expr*>(pairVal.second);
                    //if (auto ecosystem = dynamic_cast<EcoSystem*>(conv))
                        //value.push_back(std::any_cast<String>(visitEcoSystemExpr(binary)));
                }
            }
        }
    } 
    catch (runtimeerror<interpreter>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        logging<interpreter> logs(logs_, e.what(e.getType<TokenType>(), e.getMsg()));
        logs.update();
        logs.rotate();
    }                              
}
/** ------------------------------------------------
 * @brief Calls the accept method to begin the recrusive tree walk
 * 
 * @param temp A type safe union that is useful to return multiple types inside a conatinaer 
 * 
 */
String interpreter::evaluate(auto conv) {
    if (auto binary = dynamic_cast<Binary*>(conv)) return conv->accept(binary, false);
    else if (auto stmt = dynamic_cast<Statement*>(conv)) return conv->accept(stmt, false);
    else if (auto literal = dynamic_cast<Literal*>(conv)) return conv->accept(literal, false);
    else if (auto unary = dynamic_cast<Unary*>(conv)) return conv->accept(unary, false);
    else if (auto grouping = dynamic_cast<Grouping*>(conv)) return conv->accept(grouping, false); 
    else { throw new catcher<interpreter>("Unexpected type in evaluate function"); }
    return nullptr;
}
/** ---------------------------------------------------------------------------
 * @brief A method that visits the unary abstract syntax tree
 *
 * @param right: Is a fancy pointer that will point to Expr<Unary> at run time.
 * 
 * @return A Unary abstraction tree syntax node in the form of a string 
 * ---------------------------------------------------------------------------
*/
Any interpreter::visitUnaryExpr(Expr& expr) {
    Any right = evaluate(expr.right);
    switch (expr.op.getType()) {
        case TokenType::BANG:
            return !isTruthy(right);
        case MINUS:
            checkNumberOperand(expr.op, right);
            return -std::any_cast<double>(right);
    }
    // Unreachable.
    return nullptr;
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
Any interpreter::visitBinaryExpr(auto& expr) {
    Any left = evaluate(expr->left);
    Any right = evaluate(expr->right);
    switch (expr->op.getType()) {
        case TokenType::GREATER:
            checkNumberOperands(expr->op, left, right);
            return std::to_string(toNumeric<double>(left) > toNumeric<double>(right));
        case TokenType::GREATER_EQUAL:
            checkNumberOperands(expr->op, left, right);
            return std::to_string(toNumeric<double>(left) >= toNumeric<double>(right));
        case TokenType::LESS:
            checkNumberOperands(expr->op, left, right);
            return std::to_string(toNumeric<double>(left) < toNumeric<double>(right));
        case TokenType::LESS_EQUAL:
            checkNumberOperands(expr->op, left, right);
            return std::to_string(toNumeric<double>(left) <= toNumeric<double>(right));
        case TokenType::MINUS:
            checkNumberOperands(expr->op, left, right);
            return std::to_string(toNumeric<double>(left) - toNumeric<double>(right));
        case PLUS:
            if (instanceof<double>(left) && instanceof<double>(right)) {
                return std::to_string(toNumeric<double>(left) + toNumeric<double>(right));
            }
            if (instanceof<double>(left) && instanceof<double>(right)) {
                return std::to_string(toNumeric<double>(left) + toNumeric<double>(right));
            }
            if (instanceof<String>(left) && instanceof<String>(right)) { 
                return std::any_cast<String>(left) + std::any_cast<String>(right);
            }
            throw new runtimeerror<interpreter>(expr->op.getType(), "Operands must be two numbers or two strings.");
            break;
        case TokenType::SLASH:
            checkNumberOperands(expr->op, left, right);
            return std::to_string(toNumeric<double>(left) / toNumeric<double>(right));
        case TokenType::STAR:
            checkNumberOperands(expr->op, left, right);
            return std::to_string(toNumeric<double>(left) * toNumeric<double>(right));
        case TokenType::BANG_EQUAL: return !isEqual(left, right);
        case TokenType::EQUAL_EQUAL: return isEqual(left, right);
    }
    // Unreachable.
    return nullptr;
}

String interpreter::stringify(Any object) {
    if (!object.has_value()) return "nil";
    if (instanceof<double>(object)) {
        double value = std::any_cast<double>(object);
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(15) << value;
        String text = oss.str();
        
        // Remove trailing zeros
        while (text.find('.') != String::npos && (text.back() == '0' || text.back() == '.')) {
            text.pop_back();
            if (text.back() == '.') {
                text.pop_back();
                break;
            }
        }
        return text;
    }
    if (instanceof<bool>(object)) {
        return std::any_cast<bool>(object) ? "true" : "false";
    }
    if (instanceof<String>(object)) {
        return std::any_cast<String>(object);
    }
    if (instanceof<int>(object)) {
        return std::to_string(std::any_cast<int>(object));
    }
    
    // Add more type checks as needed here!
    
    // Try to convert object to string if there was no match
    try {
        return std::any_cast<String>(object);
    } catch (const std::bad_any_cast&) {
        return "<?>";  // Unknown type
    }
}