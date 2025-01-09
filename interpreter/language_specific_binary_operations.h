#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <environment.h>
#include <tactical_nuke.h>
#include <stdexcept>
namespace BinaryOperations {
    class binaryOperations: public Check<binaryOperations> {
        public:
            friend class Interpreter::interpreter;
            // Default constructor
            binaryOperations() = default;
            ~binaryOperations() noexcept {};
            static void checkNumberOperands(Token op, Any left, Any right);
        private:
            template<typename T>
            static bool instanceof(const void* object);
        protected:
            /** -------------------------------------------------------------
             * @brief convert an any object into a numeric representation 
             *
             * @param value is a any object type that provides type safe checking
             * --------------------------------------------------------------
            */
            static Any toNumeric(Any value); 
            static bool isEqual(Any a, Any b);
            /** ---------------------------------------------------------------
             * @brief isNumeric Is a helper function for (checkNumberOperands) and (checkNumberOperands)
             * 
             * @param Type: Is a generic type that must have a concrete type during run time
             *
             * @return True if the object at runtime is type: int, int64_t, float, double, etc.
             *         Otherwise, return false
             * ----------------------------------------------------------------
            */
            template<typename T>
            inline static bool isNumeric(const void* value) {
                auto& temp = *reinterpret_cast<const Any*>(value);
                String str = std::any_cast<String>(std::move(temp));
                if (str.find(".") == String::npos && typeid(T) == typeid(int))
                    return isInt(std::move(str));
                else if (str.find(".") != String::npos && typeid(T) == typeid(double))
                    return isDouble(std::move(str));
                return false;
            };
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
                auto& temp = *reinterpret_cast<const Any*>(value);
                if (temp.type() == typeid(Vector<T>)) {
                    return true;
                }
                if (temp.type() == typeid(T*)) {
                    return true;
                }
                if (temp.type() == typeid(std::reference_wrapper<T>)) {
                    return true;
                }
                if (temp.type() == typeid(NuclearLang::NukeFunction*)) {
                    return true;
                }
                if (temp.type() == typeid(NuclearLang::NukeInstance*)) {
                    return true;
                }
                if (temp.type() == typeid(NuclearLang::NukeClass*)) {
                    return true;
                }
                
                
                return false;
            };
            static bool bothEqual(const Any a, const Any b);
            static Any toOther(Any value);
        private:
            static bool isInt(const String value);
            static bool isDouble(const String value);
    };
};
using namespace BinaryOperations;
#endif 
