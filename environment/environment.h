#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include <catch.h>
#include <run_time_error.h>
#include <token.h>
namespace Environment {
    class environment: public catcher<Environment>, public runtimeerror<environment> {
        public:
            friend class catcher<environment>;
            environment() noexcept = default;
            ~environment() noexcept = default;
            String get(Token name);
            inline void define(String name, Any value) {
                values.emplace(name, value);
            };
        private:
            inline static Map<String, Any> values = new Map<String, Any>();


    };

};
#endif