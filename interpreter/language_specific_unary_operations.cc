#include <language_specific_unary_operations.h>
#include <context_free_grammar.h>
/** -----------------
 * @brief This is a map that returns the paired types
 * 
 * @details If you need to add more to the map, use the 'register_any_visitor' method
 *          It is only avialable in in this classes defined method fields 
 * ------------------
*/
std::unordered_map<std::type_index, std::function<void(std::any const&)>> unaryOperations::any_visitor {
    to_any_visitor<int>([](int x) { return x; }),
    to_any_visitor<unsigned>([](unsigned x) { return x; }),
    to_any_visitor<float>([](float x) { return x; }),
    to_any_visitor<double>([](double x) { return x; }),
};
/** ----------------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that calls in isNumeric, the helper function
 * @param object: Is a Any type that will get registered if it is a valid object type
 * @returns: ...
 * ----------------------------------------------------------------------------------------------------------------------------------------------------
*/
void unaryOperations::checkNumberOperand(Token& op, const Any& object) {
    if (instanceof<double>(object)) return;
    throw new runtimeerror<unaryOperations>(op.getType(), "Operand must be a number.");
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
std::pair<const std::type_index, std::function<void(std::any const&)>> unaryOperations::to_any_visitor(F const& f) {
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


/* ----------------------------------------------------------------------------
 *
 *
*/
