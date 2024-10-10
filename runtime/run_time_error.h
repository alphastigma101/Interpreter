#pragma once
#ifndef _RUN_TIME_ERROR_H_
#define _RUN_TIME_ERROR_H_
//#include <enum_types.h>
namespace RunTimeError {
    template<class Type>
    class runtimeerror {
        public:
            // Constructor with token and message
            explicit runtimeerror(const TokenType& type, const char* message) {
                message_ = message;
                type_ = std::move(type);
            };
            // Default constructor
            explicit runtimeerror() {
                //message_ = "Unspecified runtime error"; 
            };

            inline static const char* getMsg() { return message_; };
            // Default deconstructor
            ~runtimeerror() = default;

            // Get the error message
            inline const char* what(TokenType&& type = getType(), const char* msg = getMsg()) throw() { return static_cast<Type*>(this)->what(type, msg); };
            
            // Get the token associated with the error
            inline static const TokenType getType() { return type_; };
        private:
            inline static TokenType type_;
            inline static const char* message_;
    };
};
using namespace RunTimeError;
#endif

