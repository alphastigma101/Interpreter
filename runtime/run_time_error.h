#pragma once
#ifndef _RUN_TIME_ERROR_H_
#define _RUN_TIME_ERROR_H_
#include <cstring>
namespace RunTimeError {
    template<class Type>
    class runtimeerror {
        public:
            inline static const char* message_{};
            inline static const char* literal{};
            // Constructor with token and message
            explicit runtimeerror(void* type, const char* message) {
                message_ = message;
                if (type == nullptr) this->type = nullptr;
                else this->type = type;
            };
            // Default destructor
            ~runtimeerror() = default;
            /** -----------------------------------
             * @brief A static polymorphism method that will reseat the object by calling the correct class instance method
             * 
             * @param Sig Is a concrete type that is checked during compilation; preferable TokenType
             * @param mesg the custom message that will be logged 
             * 
             * @details Requires the template parameter syntax <> in order to use it 
             * 
             * @return Returns the derived class instance, 'this' method
            */
            inline const char* what() { return static_cast<Type*>(this)->what(); };
        protected:
            // Default constructor
            explicit runtimeerror() = default;
            inline static void* type = nullptr;
            //inline static char* message_{};
    };
};
using namespace RunTimeError;
#endif

