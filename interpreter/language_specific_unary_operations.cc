#include <language_specific_unary_operations.h>
#include <context_free_grammar.h>
// TODO: Use Crtp to group up the code but also allow the flexibility
// Create some static template free functions to avoid ambugity
// For now. Until the Crtp classes inside interface are used 
template<typename T>
static bool instanceof(const Any& object);
template<typename T>
static bool isNumeric(const Any value);
template<typename T>
static bool isOther(const Any value);
/** ----------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that checks to see if the value inside the any container is supported
 * 
 * @param object: Is a Any type that will get registered if it is a valid object type
 * @param op A token class object 
 * 
 * @returns: Returns nothing. 
 * ----------------------------------------------------------------------------------------------------------------------------------------------------
*/
void unaryOperations::checkNumberOperand(Token& op, const Any& object) {
    if (instanceof<double>(object)) return;
    if (instanceof<int>(object)) return;
    throw new runtimeerror<unaryOperations>(op, "Operand must be a number.");
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
bool isNumeric(const Any value) {
    try {
        String temp = std::move(std::any_cast<String>(value));
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
 * @brief A complex method that will check the generic type T is a type that Tatical Nuke Suppports
 *
 * @param value Is an Any container that will always hold a stirng
 *
 * @details .....
 * @return Returns true if the generic type T is supported. 
 *         Otherwise, throw an exception and return false. 
 * ----------------------------------------------------------------
*/
template<typename T>
bool isOther(const Any value) {
    /*if (auto search = any_visitor.find(value); search != any_visitor.end())
        return true;
    else
        return false;*/
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
bool instanceof(const Any& object) {
    try {
        if (isNumeric<T>(object)) return true;
        else if (isOther<T>(object)) return true;
        return false;
    } catch (...) {
        return false;
    }
}