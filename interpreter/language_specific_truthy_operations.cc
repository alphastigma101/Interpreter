#include <language_specific_truthy_operations.h>
// TODO: Use Crtp to group up the code but also allow the flexibility
// Refer to context_free_grammar.h Evaluation class. Basically, create Conv<Derived> conv; Check<Derived> check
// Embed the methods back into the classes respectively and replace each method with conv.<name of method>
// Create some static template free functions to avoid ambugity
// For now. Until the Crtp classes inside interface are used 
template<typename T>
static bool instanceof(const Any& object);
template<typename T>
static bool isNumeric(const Any value);
template<typename T>
static bool isOther(const Any value);

Unordered<std::type_index, std::function<void(Any const&)>> truthyOperations::any_visitor {
    to_any_visitor<void>([] { return; }),
    to_any_visitor<bool>([](bool s) { return s; })
};
/** ---------------------------------------------------------------------------------------------------------
 * @brief Is a method that will return an concrete type if the language the user specifies supports truthy/falsy
          Depending on the language, truthy can be an int, string, bool or NULL
 * @param Type: Is a generic type that must have a concrete type during run time
 * @return
    True if the object was successfully casted into a c++ supported type
    Otherwise, return false
 * ---------------------------------------------------------------------------------------------------------
*/
bool truthyOperations::isTruthy(Any& object) {
    if (!object.has_value()) return false;
    //if (is_registered(object)) return std::any_cast<bool>(object);
    return true;
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
/** --------------------------------------------------------------
 * @brief Returns a pair 
 * 
 * @param F It is a generic type such that is deduced at compile time. 
 *          A pair will be constructed if type is not void 
 * @param T If the objcet that was passed at run time is not found, it will create a new pair 
 * 
 * @details .first is the typeid of the object while .second is a callable object.
 * 
 * @return Returns a constructed pair with the targeted, otherwise it will return void
 * ----------------------------------------------------------------
*/
template<class T, class F>
std::pair<const std::type_index, std::function<void(std::any const&)>> truthyOperations::to_any_visitor(F const& f) {
    return
    {
        std::type_index(typeid(T)),
        [g = f](std::any const& a)
        {
            if constexpr (std::is_void_v<T>)
                g();
            else
                g(std::any_cast<T const&>(a));
        }
    };
}