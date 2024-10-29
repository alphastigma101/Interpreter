#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include <catch.h>
#include <run_time_error.h>
#include <token.h>
namespace Environment {
    class environment: protected catcher<environment>, protected runtimeerror<environment> {
        public:
            friend class catcher<environment>;
            friend class runtimeerror<environment>;
            friend class EnvironmentTest;
            environment() noexcept = default;
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
