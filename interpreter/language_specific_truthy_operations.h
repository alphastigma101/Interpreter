#ifndef _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#include <language_specific_unary_operations.h>
namespace TruthyOperations {
    class truthyOperations: public Check<unaryOperations>, public Conv<truthyOperations> {
        public:
            friend class Interpreter::interpreter;
            truthyOperations() = default;
            ~truthyOperations() noexcept = default;
        private:
            template<typename T>
            static bool isNumeric(const void* value);
            static bool isString(const void* value);
            template<typename T>
            static bool isOther(const void* value);
            template<typename T>
            static bool instanceof(const void* object);
            static bool isTruthy(const Any object);
        protected:
            
    };
};
#endif
