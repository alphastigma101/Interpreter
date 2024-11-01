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
            inline static logTable<std::map<std::string, std::vector<std::string>>> logs_{};
            Nuke::core tatical_nuke;
            template<class T, class F>
            static std::pair<const std::type_index, std::function<void(Any const&)>> to_any_visitor(F const& f); 
            static Unordered<std::type_index, std::function<void(Any const&)>> any_visitor;
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
            inline static const Token& getType() { return *static_cast<const Token*>(runtimeerror<unaryOperations>::type);};
            inline static bool isString(const Any value) { return value.type() == typeid(String);};
            inline static const char* what(const char* msg = catcher<unaryOperations>::getMsg()) throw() { return msg; };
            inline static const char* what(const Token& type = getType(), const char* msg = runtimeerror<unaryOperations>::getMsg()) throw() {
                static String output;
                auto op = std::move(type);
                try {
                    if (auto search = tokenTypeStrings.find(op.getType()); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    throw new catcher<unaryOperations>(
                        String(String("From binaryOperations what() method, TokenType is not supported!")+ String("\n\t") + 
                        String("Could not find targeted type in map: ")  +   String("\n\t") + String(std::move(op.getLexeme()))).c_str()
                    );
                    // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                }
                catch(catcher<unaryOperations>& e) {
                    std::cout << "A new log entry has been added." << std::endl;
                    logging<unaryOperations> logs(logs_, e.what());
                    logs.update();
                    logs.rotate();
                }
            };
        protected:
            static void checkNumberOperand(Token& op, const Any& object);
    };
};
using namespace UnaryOperations;
#endif
