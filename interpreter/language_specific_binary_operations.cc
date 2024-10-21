#include <language_specific_binary_operations.h>
/** -----------------
 * @brief This is a map that returns the paired types
 * 
 * @details If you need to add more to the map, use the 'register_any_visitor' method
 *          It is only avialable in in this classes defined method fields 
 * ------------------
*/
Unordered<std::type_index, std::function<void(Any const&)>> binaryOperations::any_visitor {
    to_any_visitor<int>([](int x) { return x; }),
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
    else if (instanceof<int>(left) && instanceof<int>(right)) return;
    throw new runtimeerror<binaryOperations>(op, "Operands must be numbers.");
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
/** ---------------------------------------------------------------
 * @brief A method that checks two objects to see if they are equal too
 *
 * @param a  An any container that represents the left side 
 * @param b  An any container that represents the right side
 *
 * @details .....
 * ----------------------------------------------------------------
*/
bool binaryOperations::bothEqual(const Any a, const Any b) {
    try {
        try {
            if (instanceof<int>(a) && instanceof<int>(b)) {
                String&& mutable_a = std::move(std::any_cast<String>(a));
                String&& mutable_b = std::move(std::any_cast<String>(b));
                int temp_a = std::stoi(std::move(mutable_a));
                int temp_b = std::stoi(std::move(mutable_b));
                return temp_a == temp_b;
            }
            if (instanceof<double>(a) && instanceof<double>(b)) {
                String&& mutable_a = std::move(std::any_cast<String>(a));
                String&& mutable_b = std::move(std::any_cast<String>(b));
                double temp_a = std::stod(std::move(mutable_a));
                double temp_b = std::stod(std::move(mutable_b));
                return temp_a == temp_b;
            }
        }
        catch(...) { return false; }
        throw new catcher<binaryOperations>(
            String(String("In binaryOperations bothEqual method, unsupported type detected! ") + "\n\t"  
            + std::any_cast<String>(a) + "," + std::any_cast<String>(b)).c_str()
        );
    }
    catch(catcher<binaryOperations>& e) {
        return false;
    }
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
bool binaryOperations::instanceof(const Any& object) {
    try {
        if (isNumeric<T>(object)) return true;
        else if (isOther<T>(object)) return true;
        return false;
    } catch (...) {
        return false;
    }
}
/** ---------------------------------------------------------------
 * @brief A simple method that will check an parameter object is inside the map.
 *
 * @param a An object that will be searched inside the map
 *
 * @return Return false if parameter object is not inside map, otherwise, return true.
 * ----------------------------------------------------------------
*/
bool binaryOperations::is_registered(const Any& a) {
    try {
        // cend() points one past the element. Menaing it is checking the bounds of the map
        if (const auto it = any_visitor.find(std::type_index(a.type())); it != any_visitor.cend())
            return true;
        else
           throw new catcher<binaryOperations>(
            String(String("In binaryOperations is_registered method, type has not been added to map!") + "\n\t"  
            + std::any_cast<String>(a)).c_str()
        );
    }
    catch(catcher<binaryOperations>& e) {
        std::cout << e.getMsg() << std::endl;
        std::cout << "Logs have been updated! will Atempt to regiester type..." << std::endl;
        logging<binaryOperations> logs(logs_, e.what(e.getMsg()));
        logs.update();
        logs.rotate();
    }
    return false;
}
/** ---------------------------------------------------------------
 * @brief A simple method that converts the parameter object into a supported type
 *
 * @param value Some kind of value that must be a supported type
 *
 * @details The supported types are double for more precision and integer. 
 * ----------------------------------------------------------------
*/
Any binaryOperations::toNumeric(Any& value) {
    String temp = std::any_cast<String>(value);
    // Check to see if string is a precision type and to converting it
    for (int i = 0; i < temp.length() - 1; i++) {
        if (temp[i] == '.') {
            try {
                return std::stod(temp);
            }
            catch(...) { 
                throw new catcher<binaryOperations>(
                    String(String("In binaryOperations toNumeric method, invalid percision type! ") + "\n\t"  
                    + std::any_cast<String>(value)).c_str()
                );
            }
        }
    }
    // Try to convert the string into an integer 
    try { return std::stoi(temp); }
    catch(...) { 
        throw new catcher<binaryOperations>(
            String(String("In binaryOperations toNumeric method, invalid integer type! ") + "\n\t"  
            + std::any_cast<String>(value)).c_str()
        );
    }
    return nullptr;
}

Any binaryOperations::toOther(Any& value) {
    /*String temp = std::any_cast<String>(value);
    auto toList = [&temp]() -> Any {
        try {
            if (temp.front() == '[' && temp.back() == ']') {
                // Remove brackets and trim whitespace
                String content = temp.substr(1, temp.length() - 2);
                content.erase(0, content.find_first_not_of(" \t\n\r"));
                content.erase(content.find_last_not_of(" \t\n\r") + 1);
            
                // Remove quotes from content if they exist
                if (content.front() == '"' && content.back() == '"') {
                    content = content.substr(1, content.length() - 2);
                }
            
                // Dynamically allocate new list with the processed content
                return new Nuke::core::list{content};
            }
            else 
                return nullptr;
        }
        catch(...) {
            throw new runtimeerror<binaryOperations>(temp, "Failed to convert this string into list!");
        }
        return nullptr; 
    };
    try { if (toList().has_value()) return std::any_cast<String>(toList()); }
    catch(runtimeerror<binaryOperations>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        logging<binaryOperations> logs(logs_, e.what(e.getType<String>(), e.getMsg()));
        logs.update();
        logs.rotate();
    }
    auto toMap = [&temp]() -> Any {
        try {
            if (temp.front() == '{' && temp.back() == '}') {
                // Remove brackets and trim whitespace
                String content = temp.substr(1, temp.length() - 2);
                content.erase(0, content.find_first_not_of(" \t\n\r"));
                content.erase(content.find_last_not_of(" \t\n\r") + 1);
            
                // Remove quotes from content if they exist
                if (content.front() == '"' && content.back() == '"') {
                    content = content.substr(1, content.length() - 2);
                }
            
                // Dynamically allocate new list with the processed content
                return new Nuke::core::dict{content};
            }
            else 
                return nullptr;
        }
        catch(...) {
            throw new runtimeerror<binaryOperations>(temp, "Failed to convert this string into Map!");
        }
        return nullptr; 
    };
    try { if (toMap().has_value()) return std::any_cast<String>(toMap()); }
    catch(runtimeerror<binaryOperations>& e) {
        std::cout << "Logs have been updated!" << std::endl;
        logging<binaryOperations> logs(logs_, e.what(e.getType<String>(), e.getMsg()));
        logs.update();
        logs.rotate();
    }
    throw new catcher<binaryOperations>("Unsupported Type!");*/
    return nullptr;
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
