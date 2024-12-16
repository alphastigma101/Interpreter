#include <user_stack.h>
// Function to add an element x to the top of the stack
void Stack::stack::push(Map<String, bool>* lexical_scope) {
    arr.push_back(std::move(lexical_scope));
    top++;
}

// Function to remove the top element from the stack
void Stack::stack::pop() {
    if (top < 0) {
        return;
    }
    for (int i = 0; i < arr.size(); i++) {
        if (i == top) {
            arr.erase(arr.begin() + i);
        }
    }
    return;
}
// Function to return the top element of the stack
Map<String, bool>* Stack::stack::peek() {
    // If the stack is empty, print "Stack is empty" and
    if (top < 0) {
        return nullptr;
    }
    for (int i = 0; i < arr.size(); i++) {
        if (i == top) {
            return arr.at(i);
        }
    }
    return arr.at(top);
}

// Function to check if the stack is empty
// If top is less than 0, that means there is something on the stack
bool Stack::stack::isEmpty() { return (top < 0); }