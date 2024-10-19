#pragma once
#ifndef _RUN_TIME_ERROR_H_
#define _RUN_TIME_ERROR_H_
namespace RunTimeError {
    template<class Type>
    class runtimeerror {
        public:
            // Constructor with token and message
            template<typename Sig>
            explicit runtimeerror(const Sig& type, const char* message) {
                message_ = message;
                setType(type);
            };
            // Default constructor
            explicit runtimeerror() { message_ = "Unspecified runtime error"; };
            /** -----------------------------------------------------------------
             * @brief Simple getter method
             *
             * @returns a string literal which is associated with the generic type 'Sig'
             * ------------------------------------------------------------------
            */
            inline static const char* getMsg() { return message_; };
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
            template<typename Sig>
            inline const char* what(const Sig& type, const char* msg) { return static_cast<Type*>(this)->what(type, msg); };
            /** -----------------------------------
             * @brief Get the token associated with the error
             * 
             * @details Requires the template parameter syntax <> in order to use it 
             * 
             * @return Returns the derived class instance, 'this' method
            */
            template<typename Sig>
            inline const Sig& getType() { return static_cast<Type*>(this)->getType(); };
        protected:
            inline static void* type = nullptr;
        private:
            inline static const char* message_{};
            /** -----------------------------------
             * @brief A static polymorphism method that will reseat the object by calling the correct class instance method
             * 
             * @param Sig Is a concrete type that is checked during compilation; preferable TokenType
             * 
             * @details Requires the template parameter syntax <> in order to use it 
             * 
             * @return Returns nothing
            */
            template<typename Sig>
            inline void setType(const Sig& value) { type = const_cast<void*>(static_cast<const void*>(&value)); };

    };
};
using namespace RunTimeError;
#endif

