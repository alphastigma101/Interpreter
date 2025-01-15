#include <language_specific_truthy_operations.h>
/** ---------------------------------------------------------------------------------------------------------
 * @brief Is a method that will return an concrete type if the language the user specifies supports truthy/falsy
          Depending on the language, truthy can be an int, string, bool or NULL
 * @param Type: Is a generic type that must have a concrete type during run time
 * @return
    True if the object was successfully casted into a c++ supported type
    Otherwise, return false
 * ---------------------------------------------------------------------------------------------------------
*/
bool TruthyOperations::truthyOperations::isTruthy(const Any object) {
    if (!object.has_value()) return false;
    try {
        if (object.type() == typeid(bool)) return std::any_cast<bool>(object);
        String value = std::any_cast<String>(object);
        if (value == String("true")) return true;
        if (value == String("false")) return false;
        if (value == String("null") || value == String("nil")) return false;
        try {
            int intValue = std::stoi(value);
            return intValue != 0;
        }
        catch (const std::invalid_argument&) {
            try {
                double doubleValue = std::stod(value);
                return doubleValue != 0.0;
            }
            catch (const std::invalid_argument&) {
                return !value.empty();
            }
        }
    }
    catch (const std::bad_any_cast& e) {
        return true;
    }
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
bool TruthyOperations::truthyOperations::isNumeric(const void* value) {
    try {
        auto& v = *reinterpret_cast<const Any*>(value);
        String temp = std::move(std::any_cast<String>(v));
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
bool TruthyOperations::truthyOperations::instanceof(const void* object) {
    try {
        if (isNumeric<T>(object)) return true;
        else if (isOther<T>(object)) return true;
        return false;
    } catch (...) {
        return false;
    }
}