#ifndef _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_TRUTHY_OPERATIONS_H_
#include <language_specific_unary_operations.h>
namespace TruthyOperations {
    class truthyOperations: public logging<truthyOperations>, protected runtimeerror<truthyOperations>, public catcher<truthyOperations> {
        public:
            friend class runtimeerror<truthyOperations>;
            friend class catcher<truthyOperations>;
            truthyOperations() = default;
            ~truthyOperations() noexcept = default;
        private:
            inline static logTable<std::map<std::string, std::vector<std::string>>> logs_{};
            inline static const Token& getType() { return *static_cast<const Token*>(runtimeerror<truthyOperations>::type);};
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
            inline static const char* what(const char* msg = runtimeerror<truthyOperations>::getMsg()) throw() { return msg; };
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
            inline static const char* what(const Token& type = getType(), const char* msg = runtimeerror<truthyOperations>::getMsg()) throw() {
                static String output;
                auto op = std::move(type);
                try {
                    if (auto search = tokenTypeStrings.find(op.getType()); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    throw new catcher<truthyOperations>(
                        String(String("From truthyOperations what() method, TokenType is not supported!")+ String("\n\t") + 
                        String("Could not find targeted type in map: ")  +   String("\n\t") + String(std::move(op.getLexeme()))).c_str()
                    );
                    // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                }
                catch(catcher<truthyOperations>& e) {
                    std::cout << "A new log entry has been added." << std::endl;
                    logging<unaryOperations> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
            };
            template<class T, class F>
            static std::pair<const std::type_index, std::function<void(std::any const&)>> to_any_visitor(F const& f); 
            static std::unordered_map<std::type_index, std::function<void(std::any const&)>> any_visitor;
            template<class T, class F>
            inline void register_any_visitor(F const& f) { any_visitor.insert(to_any_visitor<T>(f)); };
            inline static bool is_registered(const Any& a) {
                if (const auto it = any_visitor.find(std::type_index(a.type())); it != any_visitor.cend())
                    return true;
                else
                    throw new runtimeerror<truthyOperations>(getType(), "This object was not properly registered!");
                return false;
            };
            /*template<typename T>
            static bool instanceof(const Any& object);
            template<typename T>
            static bool isNumeric(const Any value);
            template<typename T>
            static bool isOther(const Any value);*/
        protected:
            static bool isTruthy(Any& object);
    };
};
using namespace TruthyOperations;
#endif
