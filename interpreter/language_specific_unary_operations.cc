#include <language_specific_unary_operations.h>
/** ----------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that checks to see if the value inside the any container is supported
 * 
 * @param object: Is a Any type that will get registered if it is a valid object type
 * @param op A token class object 
 * 
 * @returns: Returns nothing. 
 * ----------------------------------------------------------------------------------------------------------------------------------------------------
*/
void unaryOperations::checkNumberOperand(Token op, const Any object) {
    if (instanceof<double>(&object)) return;
    if (instanceof<int>(&object)) return;
    throw runtimeerror<Interpreter::interpreter>(op, "Operand must be a number.");
}
/** ---------------------------------------------------------------
 * @brief isNumeric Is a helper function for (checkNumberOperands) and (checkNumberOperands)
 * 
 * @param Type: Is a generic type that must have a concrete type during run time
 *
 * @return True if the object at runtime is type: int, int64_t, float, double, etc.
 *         Otherwise, return false
 * ----------------------------------------------------------------
*/
template<typename T>
bool unaryOperations::isNumeric(const void* value) {
    auto& v = *reinterpret_cast<const Any*>(value); 
    try {
        String temp = std::move(std::any_cast<String>(std::move(v)));
        for (int i = 0; i < temp.length() - 1; i++) {
            if (temp[i] == '.') {
                try {
                    if (typeid(std::stod(temp)) == typeid(T)) return true;
                    return false;
                }
                catch(...) { return false; }
                return true;
            }
        }
        try {
            if (typeid(std::stoi(temp)) == typeid(T)) return true;
            return false;
        }
        catch(...) { return false; }
    } catch (...) { return false; }
    return false;    
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
bool unaryOperations::instanceof(const void* object) {
    try {
        if (isNumeric<T>(object)) return true;
        else if (isOther<T>(object)) return true;
        return false;
    } catch (...) {
        return false;
    }
}