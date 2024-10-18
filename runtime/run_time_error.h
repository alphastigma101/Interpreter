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

            inline static const char* getMsg() { return message_; };

            // Default destructor
            ~runtimeerror() = default;

            // Get the error message
            template<typename Sig>
            inline const char* what(const Sig& type, const char* msg) {
                return static_cast<Type*>(this)->what(type, msg);
            };
        
            template<typename Sig>
            inline void setType(const Sig& value) { type = const_cast<void*>(static_cast<const void*>(&value)); };

            // Get the token associated with the error
            template<typename Sig>
            inline const Sig& getType() { return static_cast<Type*>(this)->getType(); };

        protected:
            inline static void* type = nullptr;
            inline static const char* message_{};
    };
};
using namespace RunTimeError;
#endif

