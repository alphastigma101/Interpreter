#include <language_specific_binary_operations.h>
/** -----------------
 * @brief This is a map that returns the paired types
 * 
 * @details If you need to add more to the map, use the 'register_any_visitor' method
 *          It is only avialable in in this classes defined method fields 
 * ------------------
*/
std::unordered_map<std::type_index, std::function<void(std::any const&)>> binaryOperations::any_visitor {
    to_any_visitor<int>([](int x) { return x; }),
    to_any_visitor<unsigned>([](unsigned x) { return x; }),
    to_any_visitor<float>([](float x) { return x; }),
    to_any_visitor<double>([](double x) { return x; })
};
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
void binaryOperations::checkNumberOperands(Token& op, Any& left, Any& right) {
    if (instanceof<double>(left) && instanceof<double>(right)) return;
    throw new runtimeerror<binaryOperations>(op.getType(), "Operands must be numbers.");
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
bool binaryOperations::isEqual(Any& a, Any& b) {
    if (a.has_value() && b.has_value()) return true;
    if (!a.has_value()) return false;
    return bothEqual(a,b);
}

bool binaryOperations::bothEqual(const Any a, const Any b) {
    if (instanceof<int>(a) && instanceof<int>(b)) {
        int temp_a = std::any_cast<int>(a);
        int temp_b = std::any_cast<int>(b);
        if (temp_a == temp_b) return true;
        else return false;
    }
    if (instanceof<double>(a) && instanceof<double>(b)) {
        double temp_a = std::any_cast<double>(a);
        double temp_b = std::any_cast<double>(b);
        if (temp_a == temp_b) return true;
        else return false;
    }
    if (instanceof<float>(a) && instanceof<float>(b)) {
        float temp_a = std::any_cast<float>(a);
        float temp_b = std::any_cast<float>(b);
        if (temp_a == temp_b) return true;
        else return false;
    }
    return false;
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
std::pair<const std::type_index, std::function<void(std::any const&)>> binaryOperations::to_any_visitor(F const& f) {
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
