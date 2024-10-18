#ifndef _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_ 
#include <language_specific_binary_operations.h> 
namespace UnaryOperations {
    class unaryOperations: public logging<unaryOperations>, protected runtimeerror<unaryOperations>, public catcher<unaryOperations> {
        public:
            friend class catcher<unaryOperations>; // Useful for one error
            friend class runtimeerror<unaryOperations>; 
            explicit unaryOperations() = default;
            ~unaryOperations() noexcept = default;
        private:
            logTable<std::map<std::string, std::vector<std::string>>> logs_{};
            Nuke::core tatical_nuke;
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
                    throw new runtimeerror<unaryOperations>(getType(), "This object was not properly registered!");
                return false;
            };
            template<typename T>
            inline static bool instanceof(const Any& object) {
                try {
                    (void)std::any_cast<T>(object);
                    return true;
                } catch (const std::bad_any_cast&) {
                    return false;
                }
            };
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(runtimeerror<unaryOperations>::type);};
            inline static bool isString(const std::any value) { return value.type() == typeid(std::string);};
            inline static const char* what(const char* msg = catcher<unaryOperations>::getMsg()) throw() { return msg; };
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<unaryOperations>::getMsg()) throw() {
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
        protected:
            static void checkNumberOperand(Token& op, const Any& object);
           

    };
};
using namespace UnaryOperations;
#endif
