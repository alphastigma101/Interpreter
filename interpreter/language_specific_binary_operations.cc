#include <language_specific_binary_operations.h>
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
void binaryOperations::checkNumberOperands(Token op, Any left, Any right) {
    if (instanceof<double>(&left) && instanceof<double>(&right)) return;
    else if (instanceof<int>(&left) && instanceof<int>(&right)) return;
    throw runtimeerror<Interpreter::interpreter>(op.getType(), "Operands must be numbers.");
}
/** -----------------------------------------------------------------------------------------------------------------------------------------------
 * @brief Is a method that checks to see if one object equals the other
 * 
 * @param a: Is a Any that references to an object that is passed to at run time. 
 *           If not careful with this, it could lead to segfault
 * @param b: Is a Any that references to an object that is passed to at run time.
 *           If not careful with this, it could lead to segfault.
 * 
 * @return True if a and b are equal. Otherwise, return false 
 * 
 * -----------------------------------------------------------------------------------------------------------------------------------------------
*/
bool binaryOperations::isEqual(Any a, Any b) {
    if (!a.has_value() && !b.has_value()) return true;
    if (!a.has_value()) return false;
    return bothEqual(a,b);
}

bool BinaryOperations::binaryOperations::isInt(const String value) {
    try {
        size_t processed = 0;
        std::stoi(value, &processed);
        if (processed == value.length()) return true;
    }
    catch(...) {}
    return false;
}

bool BinaryOperations::binaryOperations::isDouble(const String value) {
    auto result = double();
    auto i = std::istringstream(value);
    i >> result;      
    return !i.fail() && i.eof();
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
            if (instanceof<int>(&a) && instanceof<int>(&b))
                return std::any_cast<int>(a) == std::any_cast<int>(b);
            if (instanceof<double>(&a) && instanceof<double>(&b))
                return std::any_cast<double>(a) == std::any_cast<double>(b);
            else
                return std::any_cast<String>(a) == std::any_cast<String>(b);
        }
        catch(...) { return false; }
        throw catcher<Interpreter::interpreter>(
            String(String("In binaryOperations bothEqual method, unsupported type detected! ") + "\n\t"  
            + std::any_cast<String>(a) + "," + std::any_cast<String>(b)).c_str()
        );
    }
    catch(catcher<Interpreter::interpreter>& e) {
        std::cout << e.what() << std::endl;
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
bool binaryOperations::instanceof(const void* object) {
    try {
        if (typeid(T) == typeid(int) || typeid(T) == typeid(double)) {
            if (isNumeric<T>(object)) return true;
        }
        else if (isOther<T>(object)) return true;
        return false;
    } catch (...) {
        return false;
    }
}

/** ---------------------------------------------------------------
 * @brief A simple method that converts the parameter object into a supported type
 *
 * @param value Some kind of value that must be a supported type
 *
 * @details The supported types are double for more precision and integer.
 * ----------------------------------------------------------------
 */
Any binaryOperations::toNumeric(Any value) {
    String temp = std::any_cast<String>(value);
    // Check to see if string is a precision type and to converting it
    for (int i = 0; i < temp.length() - 1; i++) {
        if (temp[i] == '.') {
            try {
                return std::stod(temp);
            }
            catch(...) { 
                throw catcher<Interpreter::interpreter>(
                    String(String("In binaryOperations toNumeric method, invalid percision type! ") + "\n\t"  
                    + std::any_cast<String>(value)).c_str()
                );
            }
        }
    }
    // Try to convert the string into an integer 
    try { return std::stoi(temp); }
    catch(...) { 
        throw catcher<Interpreter::interpreter>(
            String(String("In binaryOperations toNumeric method, invalid integer type! ") + "\n\t"  
            + std::any_cast<String>(value)).c_str()
        );
    }
    return nullptr;
}

Any binaryOperations::toOther(Any value) {
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