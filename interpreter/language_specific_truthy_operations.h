#ifndef _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#include <language_specific_unary_operations.h>
namespace TruthyOperations {
    class truthyOperations: public Check<unaryOperations>, public Conv<truthyOperations> {
        public:
            friend class Interpreter::interpreter;
            friend class ::Test::OperationsTest;
            truthyOperations() = default;
            ~truthyOperations() noexcept = default;
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
            static bool isTruthy(const Any object);
        protected:
            
    };
};
#endif
