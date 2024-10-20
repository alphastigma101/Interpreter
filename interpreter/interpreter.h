#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <language_specific_truthy_operations.h>
namespace Interpreter {
    class interpreter: protected truthyOperations, protected binaryOperations, protected unaryOperations, public logging<interpreter>, protected runtimeerror<interpreter>, public catcher<interpreter> {
        public:
            friend class catcher<interpreter>; // Useful for one error
            friend class runtimeerror<interpreter>; 
            /** -----------------------------------------------
             * @brief A constructor that handles the traversing of the ast
             * ------------------------------------------------
            */
            explicit interpreter(Set<astTree<int, String, ExprVariant>>& expr);
            ~interpreter() noexcept = default;
            /** --------------------------------------
             * @brief A method that wraps around another method called evaluate
             * 
             * @details By making this the caller of evaluate, this will prevent infinity loop
             * 
             * @param expr Is a varaint type that has been passed by referenced
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static Any visitLiteralExpr(auto expr) { return expr->getLexeme(); };
            static Any visitBinaryExpr(auto& expr);
            /** --------------------------------------
             * @brief A method that wraps around another method called evaluate
             * 
             * @details By making this the caller of evaluate, this will prevent infinity loop
             * @details This is the visitor method that will visit the grouping expression
             * 
             * @param expr Is a varaint type that has been passed by referenced
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static String visitGroupingExpr(auto& expr) { return evaluate(expr); };
        private:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            template<typename T>
            static bool instanceof(const Any& object);
        protected:
            static String evaluate(auto conv);
            static String stringify(Any object);
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<interpreter>::type));};
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
            inline static const char* what(const char* msg = catcher<interpreter>::getMsg()) throw() { return msg; };
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
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<interpreter>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else 
                        throw new catcher<interpreter>("In interpreter class: Error! conversion has failed!");
                }
                catch(catcher<interpreter>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<interpreter> logs(logs_, e.what());
                    logs.update();
                    logs.rotate();
                }
                return output.c_str();
            };
    };
};
using namespace Interpreter;
#endif
