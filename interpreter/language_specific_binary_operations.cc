#include <language_specific_binary_operations.h>
#include <languages_types.h>
#include <context_free_grammar.h>
/** ----------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that calls in isNumeric, the helper function
 * 
 * @param expr: It is an place holder type object that references the abstraction syntax, (ast) that is currently being used. 
 *              In this case, it would be the Binary ast
 * @param left: Is a generic type that must have a concrete type during run time, and will visit the binary abstract syntax tree left side (lh)
 * @param right: Is a generic type that must have a concrete type during run time, and will visit the binary abstract syntax tree right side (rh)
 * 
 * @return True if a and b are equal. Otherwise, return false 
 * ----------------------------------------------------------------------------------------------------------------------------------------------------
*/
void binaryOperations::checkNumberOperands(ExprVariant& expr, ExprVariant& left, ExprVariant& right) {
    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(std::get<Binary>(right).getToken().getLexeme()) == true)) return;
    throw new runtimeerror(std::get<Binary>(expr).getToken().getType(), "Operands must be numbers.");
}
/** -----------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that checks to see if one object equals the other
 * 
 * @param a: Is a fancy pointer that points to the object that is passed to at run time. 
 *           If not careful with this, it could lead to segfault
 * @param b: Is a fancy pointer that points to the object that is passed to at run time.
 *           If not careful with this, it could lead to segfault.
 * 
 * @return True if a and b are equal. Otherwise, return false 
 * 
 * -----------------------------------------------------------------------------------------------------------------------------------------------
*/
bool binaryOperations::isEqual(ExprVariant& a, ExprVariant& b) {
    if (std::any_cast<int>(std::get<Binary>(a).getToken().getLexeme()) == std::any_cast<int>(std::get<Binary>(b).getToken().getLexeme())) return true;
    return false;
}
/** -----------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that checks to see if there is arithmetic operations
 * 
 * @param cl Is another enum type which represents what the user has chosen
 * @param expr: Is a fancy pointer that points to the object that is passed to at run time. 
 *           If not careful with this, it could lead to segfault
 * @param left: Is a fancy pointer that points to the object that is passed to at run time.
 *           If not careful with this, it could lead to segfault.
 * @param right Is a fancy pointer that points to the object that is passed to at run time.
 *           If not careful with this, it could lead to segfault.
 * 
 * @return True if a and b are equal. Otherwise, return false 
 * 
 * -----------------------------------------------------------------------------------------------------------------------------------------------
*/
std::any binaryOperations::arithmeticOperations(LanguageTokenTypes& cl, ExprVariant& expr, ExprVariant& left, ExprVariant& right) {
    auto binary = std::get_if<Binary>(&expr);
    if (binary) {
        switch (binary->getToken().getType()) {
            case TokenType::PLUS:
                try {
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(right) == true)) {
                        // TODO: Need to find out the type and cast it into that type 
                        // toNumeric converts the type for me but it is right now a any 
                        // Find out a way to return the actual type
                        int res =  std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme()));
                        res +=  std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                        return res;
                    }
                    if ((isString(std::get<Binary>(left).getToken().getLexeme()) == true) && (isString(right) == true)) { 
                        String res = std::get<Binary>(left).getToken().getLexeme() + std::get<Binary>(right).getToken().getLexeme();
                        return res; 
                    }
                }
                catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                    return NULL;
                }
                break;
            case TokenType::MINUS:
                try {
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(right) == true)) { 
                        // TODO: Need to find out the type and cast it into that type 
                        int res =  std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme()));
                        res -=  std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                        return res;
                    }
                }
                catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                    return NULL;
                }
                break;
            case TokenType::SLASH:
                try {
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(right) == true)) { 
                        // TODO: Need to find out the type and cast it into that type 
                        int res =  std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme()));
                        res /=  std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                        return res;
                    }
                }
                catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                }
                break;
            case TokenType::STAR:
                try { 
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(right) == true)) { 
                        // TODO: Need to find out the type and cast it into that type 
                        int res =  std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme()));
                        res *=  std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                        return res;
                    }
                }
                catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                    return NULL;
                }
                break;
            case TokenType::GREATER:
                try {
                    checkNumberOperands(expr, left, right);
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(std::get<Binary>(right).getToken().getLexeme()) == true)) { 
                        return std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme())) > std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                    }
                }
                catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                    return NULL;
                }
                break;
            case TokenType::GREATER_EQUAL:
                try {
                    checkNumberOperands(expr, left, right);
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(std::get<Binary>(right).getToken().getLexeme()) == true)) { 
                        return std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme())) >= std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                    }
                } catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                    return NULL;
                }
            case TokenType::LESS:
                try {
                    checkNumberOperands(expr, left, right);
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(std::get<Binary>(right).getToken().getLexeme()) == true)) { 
                        return std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme())) < std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                    }
                } catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                    return NULL;
                }
                break;
            case TokenType::LESS_EQUAL:
                try {
                    checkNumberOperands(expr, left, right);
                    if ((isNumeric(std::get<Binary>(left).getToken().getLexeme()) == true) && (isNumeric(std::get<Binary>(right).getToken().getLexeme()) == true)) { 
                        return std::any_cast<int>(toNumeric(std::get<Binary>(left).getToken().getLexeme())) <= std::any_cast<int>(toNumeric(std::get<Binary>(right).getToken().getLexeme()));
                    }
                }
                catch(runtimeerror<binaryOperations>& e) {
                    //std::cout << e.what() << std::endl;
                    return NULL;
                }
                break;
            case TokenType::BANG_EQUAL: return !isEqual(left, right);
            case TokenType::EQUAL_EQUAL: return isEqual(left, right);
            default: return NULL;
        }
    }
    return NULL;
}