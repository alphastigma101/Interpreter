#ifndef _STACK_H_
#define _STACK_H_
#include <declarations.h>
namespace Stack {
    class stack {
        private:
            // Index of the top element in the stack
            inline static int top = 0;
            // Array to store stack elements, with a capacity of 100
            // elements
            inline static Vector<Map<String, bool>*> arr;
            Map<String, bool>* scopes;
        public:
            /** --------------------------------------------------
             * @brief A default constructor to initialize the stack
             * ---------------------------------------------------
            */
            explicit stack() noexcept { top = -1; };
            ~stack() noexcept = default;
            explicit stack(Map<String, bool>* temp): scopes(temp) {};
            inline Map<String, bool>* getScopes() { return scopes; };
            static void push(Map<String, bool>* lexical_scope);
            static void pop();
            static Map<String, bool>* peek();
            static bool isEmpty();
            inline static Map<String, bool>* get(int pos) { return arr.at(pos);};
            inline static int size() { return top; };
    };
};
#endif