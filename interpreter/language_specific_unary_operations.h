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
            inline static Map<String, Vector<String>> logs_{};
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
                    logging<unaryOperations> logs(e.what());
                    logs.rotate();
                    logs_ = logs.getLogs();
                    
                }
            };
        protected:
            static void checkNumberOperand(Token& op, const Any& object);
    };
};
using namespace UnaryOperations;
#endif
