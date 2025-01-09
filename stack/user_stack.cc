#include <user_stack.h>
const void* Stack::stack::getType() {
    return reinterpret_cast<String*>(runtimeerror<Stack::stack>::type);
}
/** --------------------------------------
 * @brief A method that is overloaded here from this class
 *
 * @details The runtimeerror class will call this method and it will output something to the temrinal
 *
 * @param msg A default argument that calls in a static method that will output an error message
 * @param type This can hold whatever type is pass into implicity. For this case, it will be Strings
 *             It will have the name of the key that was not found inside of the stack
 * @details 
 * @return a concated string back to the caller method
 *
 * ---------------------------------------
*/
const char* Stack::stack::what(const void* type, const char *msg) throw() {
    auto a = reinterpret_cast<const String*>(type);
    return String("Error: " + std::move(*a) + String(msg)).c_str();
}
// Function to add an element x to the top of the stack
void Stack::stack::push(Map<String, bool>* lexical_scope) {
    arr.push_back(std::move(*lexical_scope));
    top++;
}

// Function to remove the top element from the stack
void Stack::stack::pop() {
    if (top < 0) throw runtimeerror<Stack::stack>("Stack is empty!", "There is nothing to pop.");
    for (int i = 0; i < arr.size(); i++) {
        if (i == top) {
            arr.erase(arr.begin() + i);
        }
    }
    top--;
    return;
}
// Function to return the top element of the stack
Map<String, bool>& Stack::stack::peek() {
    if (top < 0)  throw runtimeerror<Stack::stack>("Stack is empty!", "There is nothing to peek at");
    for (int i = 0; i < arr.size(); i++) {
        if (i == top) {
            return arr.at(i);
        }
    }
    throw runtimeerror<Stack::stack>(String(String("Stack is going out of bounds! top value is: ") + std::to_string(top)).c_str(), " Therefore, Map was not found!");
}

// Function to check if the stack is empty
// If top is less than 0, that means there is something on the stack
bool Stack::stack::isEmpty() { return (top < 0); }

