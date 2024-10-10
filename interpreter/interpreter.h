#ifndef _INTERPRETER_H_
#define _INTERPRETER_H_
#include <language_specific_truthy_operations.h> 
/* ----------------------------------------------------------------------
 * This is how the headers are formatted:
 * expression     → literal
               | unary
               | binary
               | grouping ;
 * So that means binary will have to include the grouping header file 
*/

namespace Interpreter {
    class interpreter: public unaryOperations, public binaryOperations, public truthyOperations, public runtimeerror<interpreter>, public catcher<interpreter> {
        // A class object that visits Binary, Unary, Grouping, or Literal.
        public:
            friend class catcher<interpreter>; // Useful for one error 
            friend class runtimeerror<interpreter>; // Useful for displaying the token type and a string literal

            /** -----------------------------------------------
             * 
             * @brief A constructor that handles the traversing of the ast
             * 
             * ------------------------------------------------
             */
            explicit interpreter(Vector<treeStructure>&& expr, const LanguageTokenTypes lang);
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
            inline static std::any visitLiteralExpr(auto& expr) {
                auto literal = std::get_if<ContextFreeGrammar::Literal>(&expr); 
                return literal->getValue(); 
            };
            static std::any visitUnaryExpr(auto& expr);
            static std::any visitBinaryExpr(auto& expr);
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
            inline static std::any visitGroupingExpr(auto& expr) {  return evaluate(expr); };
            inline static char* toString(std::any& left, std::any& right) {
                return NULL;
            };
            static void setExpr(const std::any& visitor);
        private:
            inline static LanguageTokenTypes currentLanguage;
            inline static logTable<std::map<std::string, std::vector<std::string>>> logs_;
        protected:
            // temp is a representation of the class node ie Binary, Unary, Grouping, and literal
            // Cast temp the correct abstract type 
            // expr is a global variable: ExprTypes<Binary, Unary, Grouping, Literal>
            static String evaluate(ExprVariant& temp);
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
            inline static const char* what(const char* msg = runtimeerror<interpreter>::getMsg()) throw() { return msg; };
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
            inline static const char* what(TokenType&& type = runtimeerror<interpreter>::getType(), const char* msg = runtimeerror<interpreter>::getMsg()) throw() {
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
    };
};
using namespace Interpreter;
#endif
