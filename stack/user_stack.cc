#include <user_stack.h>
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
const char* Stack::stack::what() throw() {
    if (runtimeerror<Stack::stack>::type == nullptr) return runtimeerror<Stack::stack>::message_;
    return "";
}
// Function to add an element x to the top of the stack
void Stack::stack::push(Map<String, bool>* lexical_scope) {
    arr.push_back(std::move(*lexical_scope));
    top++;
}

// Function to remove the top element from the stack
void Stack::stack::pop() {
    String error = "Stack is empty! There is nothing to pop!";
    if (top < 0) {
        runtimeerror<Stack::stack>::literal = "String";
        throw runtimeerror<Stack::stack>(nullptr, error.c_str());
    }
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
    String error = "Stack is empty! There is nothing to pop!";
    if (top < 0)  {
        runtimeerror<Stack::stack>::literal = "String";
        throw runtimeerror<Stack::stack>(nullptr, error.c_str());
    }
    for (int i = 0; i < arr.size(); i++) {
        if (i == top) {
            return arr.at(i);
        }
    }
    error = "Stack is going out bounds! top value is:" + std::to_string(top) + " Therefore, Map was not found!";
    runtimeerror<Stack::stack>::literal = "String";
    throw runtimeerror<Stack::stack>(nullptr, error.c_str());
}

// Function to check if the stack is empty
// If top is less than 0, that means there is something on the stack
bool Stack::stack::isEmpty() { return (top < 0); }

