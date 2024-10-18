#ifndef _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_BINARY_OPERATIONS_H_
#include <token.h> // includes declarations.h 
#include <run_time_error.h>
#include <language_core.h> // Include tatical nuke language
#include <logging.h>
#include <stdexcept>
namespace BinaryOperations {
    class binaryOperations: public Check<binaryOperations>, public catcher<binaryOperations>, public NonMemberConv<binaryOperations>, protected runtimeerror<binaryOperations> {
        public:
            friend class catcher<binaryOperations>; // Useful for one error
            friend class runtimeerror<binaryOperations>; 
            // Default constructor
            binaryOperations() = default;
            ~binaryOperations() noexcept {};
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(runtimeerror<binaryOperations>::type);};
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
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<binaryOperations>::getMsg()) throw() {
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
            static bool bothEqual(const Any a, const Any b);
            logTable<Map<String, Vector<String>>> logs_{};
            template<class T, class F>
            static std::pair<const std::type_index, std::function<void(std::any const&)>> to_any_visitor(F const& f); 
            static std::unordered_map<std::type_index, std::function<void(std::any const&)>> any_visitor;
            template<class T, class F>
            inline void register_any_visitor(F const& f) { any_visitor.insert(to_any_visitor<T>(f)); };
            inline static bool is_registered(const Any& a) {
                // cend() points one past the element. Menaing it is checking the bounds of the map
                if (const auto it = any_visitor.find(std::type_index(a.type())); it != any_visitor.cend())
                    return true;
                else
                    throw new runtimeerror<binaryOperations>(getType(), "This object was not properly registered!");
                return false;
            };
            template<typename T>
            inline static bool instanceof(const Any& object) {
                try {
                    if (isNumeric(object)) return true;
                    return true;
                } catch (...) {
                    return false;
                }
            };
        protected:
            static void checkNumberOperands(Token& op, Any& left, Any& right);
            /** -------------------------------------------------------------
             * @brief convert an any object into a numeric representation 
             *
             * @param value is a any object type that provides type safe checking
             * --------------------------------------------------------------
            */
            template<typename T>
            inline static T toNumeric(Any& value) {
                try {
                    String temp = std::any_cast<String>(value);
                    // Check the type T and attempt to convert the string to that type
                    if constexpr (std::is_same<T, int>::value) return std::stoi(temp);
                    else if constexpr (std::is_same<T, double>::value) return std::stod(temp);
                    else if constexpr (std::is_same<T, float>::value) return std::stof(temp); 
                    throw new catcher<binaryOperations>("Failed to convert value into a Numeric Value!");
                } catch (...) { throw new catcher<binaryOperations>("Failed to convert value into a Numeric Value!"); }
                throw new catcher<binaryOperations>("Failed to convert value into a Numeric Value!");
            };
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
                try {
                    std::string temp = std::any_cast<std::string>(value);
                    std::size_t pos;  
                    std::stoi(temp, &pos);
                    if (pos == temp.length()) return true;  
                    std::stod(temp, &pos);
                    if (pos == temp.length()) return true;
                    std::stof(temp, &pos);
                    if (pos == temp.length()) return true;
                    return false;
                } catch (const std::bad_any_cast&) {
                    return false;
                }
            };
            static bool isEqual(Any& a, Any& b);
            
    };
};
using namespace BinaryOperations;
#endif 
