#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include <interpreter.h>
namespace Environment {
    class environment: protected catcher<environment>, protected runtimeerror<environment>, public Interpreter::interpreter {
        public:
            friend class catcher<environment>;
            friend class runtimeerror<environment>;
            friend class EnvironmentTest;
            explicit environment();
            ~environment() noexcept = default;
            static String get(Token name);
            inline void define(String name, Any value) {
                //value.emplace(name, value);
            };
        private:
            //inline static Map<String, Any> values = new Map<String, Any>();


    };

};
#endif
