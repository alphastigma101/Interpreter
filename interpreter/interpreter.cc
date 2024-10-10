#include <interpreter.h>
#include <abstraction_tree_syntax.h>
/** -------------------------------------------------
 * @brief Calls in evaluate mehtod to begin the evaluation 
 * 
*/
interpreter::interpreter(Set<astTree<int, String, ExprVariant>>& expr) {
    String value;
    try {
        for (auto& it : expr) {
            auto& [intVal, pairVal] = it;
            if (pairVal.first == "Binary") {
                if (std::holds_alternative<Expr*>(pairVal.second)) {
                    auto& conv = std::get<Expr*>(pairVal.second);
                    if (auto binary = dynamic_cast<Binary*>(conv))
                        value += evaluate(binary);
                }
            }
            if (pairVal.first == "Statement") {
                if (std::holds_alternative<Expr*>(pairVal.second)) {
                    auto& conv = std::get<Expr*>(pairVal.second);
                    if (auto stmt = dynamic_cast<Statement*>(conv))
                        value += evaluate(stmt);
                }
            }
            if (pairVal.first == "EcoSystem") {
                if (std::holds_alternative<Expr*>(pairVal.second)) {
                    auto& conv = std::get<Expr*>(pairVal.second);
                    if (auto ecosystem = dynamic_cast<EcoSystem*>(conv))
                        value += conv->accept(ecosystem);
                }
            }
        }
    } 
    catch (catcher<interpreter>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        logging<interpreter> logs(logs_, e.what());
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
    else { throw catcher<interpreter>("Unexpected type in evaluate function"); }
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
std::any interpreter::visitUnaryExpr(auto& expr) {
    auto unaryR = std::get_if<Unary>(&expr);
    auto right = evaluate(*unaryR->getRight());
    switch (unaryR->getToken().getType()) {
        case TokenType::BANG:
            return !isTruthy(*unaryR->getRight(), currentLanguage);
        case TokenType::MINUS:
            switch(currentLanguage) {
                case LanguageTokenTypes::Python:
                    return dynamicLanguages::uPython(currentLanguage, *unaryR->getRight());
               
                default:
                    throw runtimeerror<interpreter>(unaryR->getToken().getType(), "Operand must be a number.");           
            }
        default:
            throw runtimeerror<interpreter>(unaryR->getToken().getType(), "Operand must be a number.");
    }
    // Unreachable.
    return NULL;
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
std::any interpreter::visitBinaryExpr(auto& expr) {
    auto binaryL = std::get_if<Binary>(&expr);
    auto left = evaluate(*binaryL->getLeft());
    auto binaryR = std::get_if<Binary>(&expr);
    auto right = evaluate(*binaryR->getRight());
    switch (currentLanguage) {
        case LanguageTokenTypes::Python:
            if (arithmeticOperations(currentLanguage, expr, *binaryL->getLeft(), *binaryL->getRight()).has_value()) {

            }
            break;
        default:
            throw catcher<interpreter>("Operand must be a number.");           
    }
    // Unreachable.
    return NULL;
}