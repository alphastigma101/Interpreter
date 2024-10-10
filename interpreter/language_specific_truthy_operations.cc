#include <language_specific_truthy_operations.h>
#include <languages_types.h>
#include <context_free_grammar.h>
/* ---------------------------------------------------------------------------------------------------------
 * isTruthy Description:
    Is a method that will return an concrete type if the language the user specifies supports truthy/falsy
    Depending on the language, truthy can be an int, string, bool or NULL
 * Arguments:
    * Type: Is a generic type that must have a concrete type during run time
 * Returns:
    True if the object was successfully casted into a c++ supported type
    Otherwise, return false
 * ---------------------------------------------------------------------------------------------------------
*/
bool truthyOperations::isTruthy(ExprVariant& object, LanguageTokenTypes& lang) {
    String temp = std::get<Unary>(object).getToken().getLexeme();
    switch(lang) {
        case LanguageTokenTypes::Python:
            if (std::any_cast<LanguageTypes::Python::None>(temp) != nullptr) return false;
            else if (auto b = std::any_cast<LanguageTypes::Python::Bool>(temp)) return b;
            else if (auto i = std::any_cast<LanguageTypes::Python::Int>(temp)) return i != 0;
            else if (auto f = std::any_cast<LanguageTypes::Python::Float>(temp)) return f != 0.0;
            //else if (auto s = std::any_cast<LanguageTypes::Python::String>(temp)) return !s->empty();
            //else if (auto l = std::any_cast<LanguageTypes::Python::List>(temp)) return !l->empty();
            //else if (auto d = std::any_cast<LanguageTypes::Python::Dict>(temp)) return !d->empty();
            return true;
        /*case LanguageTokenTypes::JavaScript:
            if (std::any_cast<LanguageTypes::JavaScript::Null>(object.getValue()) != nullptr) return false;
            else if (std::any_cast<LanguageTypes::JavaScript::Undefined>(object.getValue()) != nullptr) return false;
            else if (auto b = std::any_cast<LanguageTypes::JavaScript::Bool>(object.getValue())) return *b;
            else if (auto n = std::any_cast<LanguageTypes::JavaScript::Float>(object.getValue())) return *n != 0 && !std::isnan(*n);
            else if (auto s = std::any_cast<LanguageTypes::JavaScript::String>(object.getValue())) return !s->empty();
            return true;
        case LanguageTokenTypes::Ruby:
            if (std::any_cast<LanguageTypes::Ruby::Nil>(&object) != nullptr) return false;
            else if (auto b = std::any_cast<LanguageTypes::Ruby::TrueClass>(object.getValue())) return true;
            else if (auto b = std::any_cast<LanguageTypes::Ruby::FalseClass>(object.getValue())) return false;
            return true;
        case LanguageTokenTypes::C:
        case LanguageTokenTypes::CPP:
            if (auto b = std::any_cast<LanguageTypes::CPP::Bool>(object.getValue())) return *b;
            else if (auto i = std::any_cast<LanguageTypes::CPP::Int>(object.getValue())) return *i != 0;
            else if (auto d = std::any_cast<LanguageTypes::CPP::Double>(object.getValue())) return *d != 0.0;
            else if (auto p = std::any_cast<LanguageTypes::CPP::Nullptr>(object.getValue())) return false;
            return true;
        case LanguageTokenTypes::Java:
            if (std::any_cast<LanguageTypes::Java::Null>(object.getValue()) != nullptr) return false;
            else if (auto b = std::any_cast<LanguageTypes::Java::Bool>(object.getValue())) return *b;
            return true;
        case LanguageTokenTypes::Go:
            if (auto b = std::any_cast<LanguageTypes::Go::Bool>(object.getValue())) return *b;
            return true;
        case LanguageTokenTypes::Kotlin:
        case LanguageTokenTypes::Swift:
        case LanguageTokenTypes::Rust:
        case LanguageTokenTypes::CSharp:
        case LanguageTokenTypes::FSharp:
        case LanguageTokenTypes::ObjectiveC:
        case LanguageTokenTypes::Scala:
        case LanguageTokenTypes::TypeScript:
        case LanguageTokenTypes::Dart:
            if (std::any_cast<std::nullptr_t>(object.getValue()) != nullptr) return false;
            else if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            return true;
        case LanguageTokenTypes::PHP:
            if (std::any_cast<nullptr_t>(object.getValue()) != nullptr) return false;
            else if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            else if (auto i = std::any_cast<int>(object.getValue())) return *i != 0;
            else if (auto f = std::any_cast<float>(object.getValue())) return *f != 0.0f;
            else if (auto s = std::any_cast<std::string>(object.getValue())) return !s->empty();
            return true;
        case LanguageTokenTypes::Perl:
        case LanguageTokenTypes::R:
        case LanguageTokenTypes::Lua:
        case LanguageTokenTypes::MATLAB:
        case LanguageTokenTypes::VBA:
        case LanguageTokenTypes::Groovy:
        case LanguageTokenTypes::Julia:
        case LanguageTokenTypes::PowerShell:
        case LanguageTokenTypes::VisualBasic:
            if (std::any_cast<nullptr_t>(object.getValue()) != nullptr) return false;
            else if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            else if (auto n = std::any_cast<double>(object.getValue())) return *n != 0.0;
            else if (auto s = std::any_cast<std::string>(object.getValue())) return !s->empty();
            return true;
        case LanguageTokenTypes::Haskell:
        case LanguageTokenTypes::Erlang:
        case LanguageTokenTypes::Clojure:
        case LanguageTokenTypes::StandardML:
        case LanguageTokenTypes::Elm:
            if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            return true;
        case LanguageTokenTypes::VHDLVerilog:
        case LanguageTokenTypes::Fortran:
        case LanguageTokenTypes::COBOL:
        case LanguageTokenTypes::Pascal:
        case LanguageTokenTypes::Ada:
        case LanguageTokenTypes::Eiffel:
            if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            return true;
        case LanguageTokenTypes::AWK:
        case LanguageTokenTypes::TCL:
            if (auto s = std::any_cast<std::string>(object.getValue())) return !s->empty() && *s != "0";
            else if (auto n = std::any_cast<double>(object.getValue())) return *n != 0.0;
            return true;
        case LanguageTokenTypes::Shell:
            if (auto s = std::any_cast<std::string>(object.getValue())) return !s->empty();
            else if (auto n = std::any_cast<int>(object.getValue())) return *n != 0;
            return true;
        case LanguageTokenTypes::LISPScheme:
        case LanguageTokenTypes::Racket:
            if (std::any_cast<nullptr_t>(object.getValue()) != nullptr) return false;
            return true;
        case LanguageTokenTypes::Prolog:
            if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            return true;
        case LanguageTokenTypes::SmallTalk:
            if (std::any_cast<nullptr_t>(object.getValue()) != nullptr) return false;
            if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            return true;
        case LanguageTokenTypes::HTMLCSS:
        case LanguageTokenTypes::SQL:
        case LanguageTokenTypes::LabVIEW:
            return NULL;
        case LanguageTokenTypes::Dlang:
            if (std::any_cast<nullptr_t>(object.getValue()) != nullptr) return false;
            else if (auto b = std::any_cast<bool>(object.getValue())) return *b;
            else if (auto i = std::any_cast<int>(object.getValue())) return *i != 0;
            else if (auto f = std::any_cast<float>(object.getValue())) return *f != 0.0f;
            else if (auto s = std::any_cast<std::string>(object.getValue())) return !s->empty();
            return true;
        */
        default:
            //TODO: Implement Custom language here
            return NULL;
    }
}
