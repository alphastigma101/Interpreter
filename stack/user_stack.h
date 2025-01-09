#ifndef _STACK_H_
#define _STACK_H_
#include <declarations.h>
#include <catch.h>
#include <run_time_error.h>
namespace Stack {
    class stack: protected catcher<stack>, protected runtimeerror<stack> {
        private:
            // Index of the top element in the stack
            inline static int top = -1;
            inline static Vector<Map<String, bool>> arr{};
            static const void* getType();
           /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = runtimeerror<stack>::getMsg()) throw() { return msg; }; 
            static const char* what(const void* type = getType(), const char* msg = runtimeerror<stack>::getMsg()) throw();
        public:
            /** --------------------------------------------------
             * @brief A default constructor to initialize the stack
             * ---------------------------------------------------
            */
            explicit stack() noexcept = default;
            ~stack() noexcept = default;
            static void push(Map<String, bool>* lexical_scope);
            static void pop();
            static Map<String, bool>& peek();
            static bool isEmpty();
            inline static Map<String, bool>& get(int pos) { return arr.at(pos);};
            inline static int size() { return top; };
    };
};
#endif