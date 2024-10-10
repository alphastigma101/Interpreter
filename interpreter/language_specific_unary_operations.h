#ifndef _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_
#define _LANGUAGE_SPECIFIC_UNARY_OPERATIONS_H_ 
#include <language_specific_binary_operations.h> 

namespace UnaryOperations {
    class unaryOperations: public Check<unaryOperations>, public runtimeerror<unaryOperations> {
        public:
            friend class ::Interpreter::interpreter;
            explicit unaryOperations() = default;
            ~unaryOperations() noexcept = default;
            /* -----------------------------------------------------------------------------
             * isNumeric Description:
                Is a helper function for (checkNumberOperands) and (checkNumberOperands)
             * @param Type: Is a generic type that must have a concrete type during run time
             * @return:
                True if the object at runtime is type: int, int64_t, float, double, etc.
                Otherwise, return false
             * ----------------------------------------------------------------------------
            */
            inline static bool isNumeric(const std::any value) {
                return value.type() == typeid(int) ||
                value.type() == typeid(int64_t) ||
                value.type() == typeid(float) ||
                value.type() == typeid(double);
            };
            
            struct staticLanguages {
                friend class unaryOperations;
                auto uC(LanguageTokenTypes& lang, auto& right); // C
                auto uCPP(LanguageTokenTypes& lang, auto& right); // C++
                auto uJava(LanguageTokenTypes& lang, auto& right); // Java
                auto uGo(LanguageTokenTypes& lang, auto& right); // Go
                auto uKotlin(LanguageTokenTypes& lang, auto& right); // Kotlin
                auto uSwift(LanguageTokenTypes& lang, auto& right); // Swift
                auto uRust(LanguageTokenTypes& lang, auto& right); // Rust
                auto uCSharp(LanguageTokenTypes& lang, auto& right); // C#
                auto uFSharp(LanguageTokenTypes& lang, auto& right); // F#
                auto uObjectiveC(LanguageTokenTypes& lang, auto& right); // Objective-C
                auto uScala(LanguageTokenTypes& lang, auto& right); // Scala
                auto uDart(LanguageTokenTypes& lang, auto& right); // Dart
                auto uVHDLVerilog(LanguageTokenTypes& lang, auto& right); // VHDL/Verilog
                auto uFortran(LanguageTokenTypes& lang, auto& right); // Fortran
                auto uCOBOL(LanguageTokenTypes& lang, auto& right); // COBOL
                auto uPascal(LanguageTokenTypes& lang, auto& right); // Pascal
                auto uAda(LanguageTokenTypes& lang, auto& right); // Ada
                auto uEiffel(LanguageTokenTypes& lang, auto& right); // Eiffel
            };
            
            struct dynamicLanguages {
                static Any uPython(LanguageTokenTypes& lang, ExprVariant& right); // Python  
                auto uJavaScript(LanguageTokenTypes& lang, auto& right); // JavaScript
                auto uRuby(LanguageTokenTypes& lang, auto& right); // Ruby
                auto uR(LanguageTokenTypes& lang, auto& right); // R
                auto uPHP(LanguageTokenTypes& lang, auto& right); // PHP
                auto uLua(LanguageTokenTypes& lang, auto& right); // Lua
                auto uMATLAB(LanguageTokenTypes& lang, auto& right); // MATLAB
                auto uVBA(LanguageTokenTypes& lang, auto& right); // VBA
                auto uGroovy(LanguageTokenTypes& lang, auto& right); // Groovy
                auto uJulia(LanguageTokenTypes& lang, auto& right); // Julia
                auto uPowerShell(LanguageTokenTypes& lang, auto& right); // PowerShell
                auto uVisualBasic(LanguageTokenTypes& lang, auto& right); // Visual Basic
                auto uPerl(LanguageTokenTypes& lang, auto& right); // Perl
                auto uAWK(LanguageTokenTypes& lang, auto& right); // AWK
                auto uShell(LanguageTokenTypes& lang, auto& right); // Shell scripting
                auto uLISPScheme(LanguageTokenTypes& lang, auto& right); // Lisp/Scheme
                auto uRacket(LanguageTokenTypes& lang, auto& right); // Racket
                auto uClojure(LanguageTokenTypes& lang, auto& right); // Clojure
                auto uSmallTalk(LanguageTokenTypes& lang, auto& right); // Smalltalk
                auto uHaskell(LanguageTokenTypes& lang, auto& right); // Haskell
                auto uTypeScript(LanguageTokenTypes& lang, auto& right); // TypeScript
            };
            struct otherLanguages {
                auto uHTMLCSS(LanguageTokenTypes& lang, auto& right); // HTML/CSS
                auto uSQL(LanguageTokenTypes& lang, auto& right); // SQL
                auto uLabVIEW(LanguageTokenTypes& lang, auto& right); // LabVIEW (visual programming)
                auto uStandardML(LanguageTokenTypes& lang, auto& right); // Standard ML (Functional)
                auto uElm(LanguageTokenTypes& lang, auto& right); // Elm (Functional)
                auto uCustom(LanguageTokenTypes& lang, auto& right); // Custom language
                auto uDlang(LanguageTokenTypes& lang, auto& right); // D
                auto uProlog(LanguageTokenTypes& lang, auto& right); // Prolog
                auto uTCL(LanguageTokenTypes& lang, auto& right); // TCL
                auto uErlang(LanguageTokenTypes& lang, auto& right); // Elrang
            };
        private:
            static bool checkNumberOperand(ExprVariant& right);
            logTable<std::map<std::string, std::vector<std::string>>> logs_;
        protected:
            inline static bool isString(const std::any value) { return value.type() == typeid(std::string);};
            inline static const char* what(const char* msg = catcher<unaryOperations>::getMsg()) throw() { return msg; };
            inline static const char* what(TokenType&& type = runtimeerror<Interpreter::interpreter>::getType(), const char* msg = runtimeerror<Interpreter::interpreter>::getMsg()) throw() {
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
using namespace UnaryOperations;
#endif
