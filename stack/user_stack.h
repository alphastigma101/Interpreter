#ifndef _STACK_H_
#define _STACK_H_
#include <declarations.h>
#include <catch.h>
namespace Stack {
    class stack {
        private:
            // Index of the top element in the stack
            inline static int top = -1;
            inline static Vector<Map<String, bool>> arr{};
        public:
            /** --------------------------------------------------
             * @brief A default constructor to initialize the stack
             * ---------------------------------------------------
            */
            explicit stack() noexcept = default;
            ~stack() noexcept = default;
            static void push(Map<String, bool>* lexical_scope);
            static void pop();
            static Map<String, bool>* peek();
            static bool isEmpty();
            inline static Map<String, bool> get(int pos) { return arr.at(pos);};
            inline static int size() { return top; };
    };
};
#endif