#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <environment.h>
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
            template<class T, class F>
            static std::pair<const std::type_index, std::function<void(Any const&)>> to_any_visitor(F const& f); 
            static Unordered<std::type_index, std::function<void(Any const&)>>any_visitor;
            template<class T, class F>
            inline void register_any_visitor(F const& f) { any_visitor.insert(to_any_visitor<T>(f)); };
            inline static bool is_registered(const Any& a);
            template<typename T>
            static bool instanceof(const Any& object);
        protected:
            static void checkNumberOperands(Token& op, Any& left, Any& right);
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
                try {
                    String temp = std::move(std::any_cast<String>(value));
                    for (int i = 0; i < temp.length() - 1; i++) {
                        if (temp[i] == '.') {
                            try {
                                if (typeid(std::stod(temp)) == typeid(T)) return true;
                                return false;
                            }
                            catch(...) { return false; }
                        }
                    }
                    try {
                        if (typeid(std::stoi(temp)) == typeid(T)) return true;
                        return false;
                    }
                    catch(...) { return false; }
                } catch (...) { throw new catcher<binaryOperations>("Failed to convert value into a Numeric Value!"); }
                throw new catcher<binaryOperations>("Failed to convert value into a Numeric Value!");    
            };
            static bool isEqual(Any& a, Any& b);
            inline static bool isString(const Any value) { return value.type() == typeid(String);};
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
                /*if (auto search = any_visitor.find(value); search != any_visitor.end())
                    return true;
                else
                    return false;*/
                return false;
            };
            /** -------------------------------------------------------------
             * @brief convert an any object into a numeric representation 
             *
             * @param value is a any object type that provides type safe checking
             * --------------------------------------------------------------
            */
            static Any toNumeric(Any& value); 
            static Any toOther(Any& value);
    };
};
using namespace BinaryOperations;
#endif 
