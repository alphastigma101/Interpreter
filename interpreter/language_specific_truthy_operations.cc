#include <language_specific_truthy_operations.h>
std::unordered_map<std::type_index, std::function<void(std::any const&)>> truthyOperations::any_visitor {
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
    if (is_registered(object)) return std::any_cast<bool>(object);
    return true;
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