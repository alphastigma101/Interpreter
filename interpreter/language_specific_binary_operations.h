#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <logging.h> // includes declarations.h 
#include <catch.h> // To output the message of an unexcpected crash
namespace BinaryOperations {
    class binaryOperations: public Check<binaryOperations>, public catcher<binaryOperations>, public NonMemberConv<binaryOperations>, public runtimeerror<binaryOperations> {
        public:
            friend class ::Interpreter::interpreter;
            friend class runtimeerror<binaryOperations>;
            friend class catcher<binaryOperations>;
            // Default constructor
            binaryOperations() = default;
            ~binaryOperations() noexcept {};
            static std::any arithmeticOperations(LanguageTokenTypes& cl, ExprVariant& expr, ExprVariant& left, ExprVariant& right);
            static bool isEqual(ExprVariant& a, ExprVariant& b);
        private:
            static void checkNumberOperands(ExprVariant& expr, ExprVariant& left, ExprVariant& right);
            logTable<Map<String, Vector<String>>> logs_;
        protected:
           /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = runtimeerror<binaryOperations>::getMsg()) throw() { return msg; };
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(TokenType&& type = runtimeerror<binaryOperations>::getType(), const char* msg = runtimeerror<binaryOperations>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                }
                catch(...) {
                    std::cout << "Error! conversion has failed!" << std::endl;
                }
            };
            inline static bool isString(const std::any value) { return value.type() == typeid(std::string);};
            /** ---------------------------------------------------------------
             * @brief isNumeric Is a helper function for (checkNumberOperands) and (checkNumberOperands)
             * 
             * @param Type: Is a generic type that must have a concrete type during run time
             *
             * @return True if the object at runtime is type: int, int64_t, float, double, etc.
                       Otherwise, return false
             * ----------------------------------------------------------------
            */
            inline static bool isNumeric(const std::any value) {
                // TODO: Need to add more supported types here. refer to languages_types.h
                try {
                    auto temp = std::any_cast<int>(value);
                    return value.type() == typeid(int);
                }
                catch(...) {}
                try {
                    auto temp = std::any_cast<int64_t>(value);
                    return value.type() == typeid(int64_t);
                }
                catch(...) {}
                try {
                    auto temp = std::any_cast<float>(value);
                    return value.type() == typeid(float);
                }
                catch(...) {}
                try {
                    auto temp = std::any_cast<double>(value);
                    return value.type() == typeid(double);
                }
                catch(...) {}
                return false;
            };
            /** -------------------------------------------------------------
             * @brief convert an any object into a numeric representation 
             *
             * @param value is a any object type that provides type safe checking
             * --------------------------------------------------------------
            */
            inline static std::any toNumeric(std::any&& value) {
                try {
                    // explicit casting syntax is keywords<objec type>(user defined object)
                    if (value.type() == typeid(int)) return std::any_cast<int>(value);
                    else if (value.type() == typeid(int64_t)) return std::any_cast<int64_t>(value);
                    else if (value.type() == typeid(float)) return std::any_cast<float>(value);
                    else if (value.type() == typeid(double)) return std::any_cast<double>(value);
                    else {
                        catcher<binaryOperations> cbo("Error when converting object into a representable type in c++!");
                        throw cbo;
                    }
                }
                catch(catcher<binaryOperations>& e) {
                    std::cout << e.what() << std::endl;
                }
                return NULL;
            };
    };
};
using namespace BinaryOperations;
#endif 
