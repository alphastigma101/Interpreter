#ifndef _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_ 
#include <language_specific_binary_operations.h> 
namespace UnaryOperations {
    class unaryOperations: public Check<unaryOperations>, public Conv<unaryOperations> {
        public:
            friend class Interpreter::interpreter;
            friend class ::Test::OperationsTest;
            explicit unaryOperations() = default;
            ~unaryOperations() noexcept = default;
            static void checkNumberOperand(Token op, const Any object);
        private:
            template<typename T>
            static bool isNumeric(const void* value);
            static bool isString(const void* value);
            /** ---------------------------------------------------------------
             * @brief A complex method that will check the generic type T is a type that Tatical Nuke Suppports
             *
             * @param value Is an Any container that will always hold a stirng
             *
             * @details .....
             * @return Returns true if the generic type T is supported. 
             *         Otherwise, throw an exception and return false. 
             * ----------------------------------------------------------------
            */
            template<typename T>
            inline static bool isOther(const void* value) {
                /*if (auto search = any_visitor.find(value); search != any_visitor.end())
                    return true;
                else
                    return false;*/
                return false;
            };
            template<typename T>
            static bool instanceof(const void* object);
    };
};
using namespace UnaryOperations;
#endif
