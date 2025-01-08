#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <environment.h>
#include <tactical_nuke.h>
#include <stdexcept>
namespace BinaryOperations {
    class binaryOperations: public catcher<binaryOperations>, protected runtimeerror<binaryOperations>, public logging<binaryOperations> {
        public:
            friend class catcher<binaryOperations>; // Useful for one error
            friend class runtimeerror<binaryOperations>; 
            // Default constructor
            binaryOperations() = default;
            ~binaryOperations() noexcept {};
        private:
            inline static const Token& getType() { return *static_cast<Token*>(runtimeerror<binaryOperations>::type);};
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
            inline static const char* what(const Token& type = getType(), const char* msg = runtimeerror<binaryOperations>::getMsg()) throw() {
                static String output;
                auto op = std::move(type);
                try {
                    if (auto search = tokenTypeStrings.find(op.getType()); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    throw new catcher<binaryOperations>(
                        String(String("From binaryOperations what() method, TokenType is not supported!")+ String("\n\t") + 
                        String("Could not find targeted type in map: ")  +   String("\n\t") + String(std::move(op.getLexeme()))).c_str()
                    );
                    // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                }
                catch(catcher<binaryOperations>& e) {
                    std::cout << "A new log entry has been added." << std::endl;
                    logging<binaryOperations> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
            };
            /** -----------------------------------
             * @brief A Map that holds logging entries.
             * 
             * @param String First parameter the map takes
             * @param Vector The second parameter the map takes. 
             *               The vector takes in a String type
             * ------------------------------------
            */
            inline static Map<String, Vector<String>> logs_{};
            template<typename T>
            static bool instanceof(const Any object);
        protected:
            static void checkNumberOperands(Token op, Any left, Any right);
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
            inline static bool isNumeric(const Any value) {
                size_t processed = 0;
                String str = std::any_cast<String>(value);
                if (str.find(".") == String::npos && typeid(T) == typeid(int)) {
                    str = std::any_cast<String>(value);
                    std::stoi(str, &processed);
                    // If we processed the whole string, it's a valid integer
                    if (processed == str.length()) return true;
                }
                else if (str.find(".") != String::npos && typeid(T) == typeid(double)) {
                    auto result = double();
                    auto i = std::istringstream(str);
                    i >> result;      
                    return !i.fail() && i.eof();
                }
                return false;
            };
            static bool isEqual(Any a, Any b);
            static bool bothEqual(const Any a, const Any b);
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
            inline static bool isOther(const Any value) {
                if (value.type() == typeid(Vector<T>)) {
                    return true;
                }
                if (value.type() == typeid(T*)) {
                    return true;
                }
                if (value.type() == typeid(std::reference_wrapper<T>)) {
                    return true;
                }
                if (value.type() == typeid(NuclearLang::NukeFunction*)) {
                    return true;
                }
                if (value.type() == typeid(NuclearLang::NukeInstance*)) {
                    return true;
                }
                if (value.type() == typeid(NuclearLang::NukeClass*)) {
                    return true;
                }
                
                
                return false;
            };
            /** -------------------------------------------------------------
             * @brief convert an any object into a numeric representation 
             *
             * @param value is a any object type that provides type safe checking
             * --------------------------------------------------------------
            */
            static Any toNumeric(Any value); 
            static Any toOther(Any value);
        private:
            //bool isInt();
    };
};
using namespace BinaryOperations;
#endif 
