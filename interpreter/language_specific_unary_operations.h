#ifndef _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_ 
#include <language_specific_binary_operations.h> 
namespace UnaryOperations {
    class unaryOperations: public Check<unaryOperations> {
        public:
            friend class Interpreter::interpreter;
            explicit unaryOperations() = default;
            ~unaryOperations() noexcept = default;
            static void checkNumberOperand(Token op, const Any object);
        private:
            template<typename T>
            static bool isNumeric(const void* value);
            static bool isString(const void* value);
            template<typename T>
            static bool isOther(const void* value);
            template<typename T>
            static bool instanceof(const void* object);
    };
};
using namespace UnaryOperations;
#endif
