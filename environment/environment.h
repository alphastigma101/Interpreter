#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_
#include <token.h> // includes declarations.h
#include <run_time_error.h>
namespace Environment {
    /** --------------------------------------
        * @brief A class that implements the environment data structure.
        *        It will map the identifier to its values.
        * ---------------------------------------- 
    */
    class environment: protected runtimeerror<environment> {
        public:
            friend class runtimeerror<environment>;
            friend class EnvironmentTest;
            explicit environment() = default;
            explicit environment(environment* env);
            ~environment() noexcept = default;
            static environment* enclosing;
            static Any get(Token name);
            static void define(const String name, const Any value);
            environment* ancestor(int distance);
            Any getAt(const int distance, String name);
            void assignAt(const int distance, Token name, Any value);
            static void assign(Token name, const Any value);
            inline static Map<String, Any>& getMap() { return env; };
            inline static int count(String key) { return env.count(key); };
        protected:
            static const void* getType();
            static const char* what(const void* type = getType(), const char* msg = runtimeerror<environment>::getMsg()) throw();
        private:
            /** --------------------------------------------------------------------------
                * @brief A map that holds a map and a vector 
                *
                * @details The following parameters are for the nested map, which is the key for the 'outer map':
                * @param Any: is a any type but functions as the key. It is considered to be the 'state' of the object, such that the identifer must always have some kind of state.
                * @param String: is the indentifer, but represented as a string type.
                *
                * @details The following parameters describe the value in great detail: 
                * @param Vector: It is a container that holds a string that represents an evaluated expression, which are pulled from 'evaluatedExpressions'.
                *                Or it can hold a specific node from 'context_free_grammar.h' that can be visited and/or converted into a string later on.
            */
            inline static Map<String, Any> env{};
    };

};
#endif
