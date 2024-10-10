#include <language_specific_unary_operations.h>
#include <languages_types.h>
#include <context_free_grammar.h>
/* ----------------------------------------------------------------------------------------------------------------------------------------------------
 * checkNumberOperand Description: 
    Is a method that calls in isNumeric, the helper function
 * Arguments:
    * auto right: Is a generic type that must have a concrete type during run time, and will visit the unary abstract syntax tree right side (rh)
 * Returns:
    True if a and b are equal
    Otherwise, return false 
 * ----------------------------------------------------------------------------------------------------------------------------------------------------
*/
bool unaryOperations::checkNumberOperand(ExprVariant& right) {
    try {
        if (isNumeric(std::get<Unary>(right).getToken().getLexeme()) == true) { return true; }
        return false;
    }
    catch(...) {
        throw runtimeerror(std::get<Unary>(right).getToken().getType(), "Failed to check the number operands!");
    }
    return false;
}

/* ----------------------------------------------------------------------------
 *
 *
*/
Any unaryOperations::dynamicLanguages::uPython(LanguageTokenTypes& lang, ExprVariant& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<LanguageTypes::Python::Int>(std::get<Unary>(right).getToken().getLexeme())) {  return -(val); }
            if (auto val = std::any_cast<LanguageTypes::Python::Float>(std::get<Unary>(right).getToken().getLexeme())) { return -(val); }
            else { throw runtimeerror(std::get<Unary>(right).getToken().getType(), "Unknown Type! in uPython"); }
        }
    }
    catch(runtimeerror& e) { 
        //TODO: Logging needs to go here
        //std::cout << e.what() << std::endl;
    }
    return NULL;
}

/* ----------------------------------------------------------------------------
 * JavaScript Description:
    This method will convert a JavaScript type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uJavaScript(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<LanguageTypes::JavaScript::Float>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uJavaScript"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Ruby Description:
    This method will convert a Ruby type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uRuby(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<LanguageTypes::Ruby::Int>(&right)) { return -(*val); }
            if (auto val = std::any_cast<LanguageTypes::Ruby::Float>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uRuby");
            }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * C Description:
    This method will convert a C type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uC(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            // if statements go here
            if (true) {}
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uC");
            }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * CPP Description:
    This method will convert a C++ type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uCPP(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<LanguageTypes::CPP::Int>(&right)) { return -(*val); }
            if (auto val = std::any_cast<LanguageTypes::CPP::Double>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uCPP"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Java Description:
    This method will convert a Java type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uJava(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<LanguageTypes::Java::Int>(&right)) { return -(*val); }
            if (auto val = std::any_cast<LanguageTypes::Java::Double>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uJava"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Go Description:
    This method will convert a Go type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uGo(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Go::Int>(&right)) { return -(*val); }
            if (auto val = std::any_cast<Go::Float>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uGo"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Kotlin Description:
    This method will convert a Kotlin type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uKotlin(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Kotlin::Int>(&right)) { return -(*val); }
            if (auto val = std::any_cast<Kotlin::Float>(&right)) { return -(*val); }
            if (auto val = std::any_cast<Kotlin::Double>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uKotlin"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Swift Description:
    This method will convert a Swift type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uSwift(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Swift::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Kotlin::Double>(&right)) { return -(*val);  }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uSwift"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Rust Description:
    This method will convert a Rust type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uRust(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Rust::i8>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::i16>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::i32>(&right)) { return -(*val); } 
            else if (auto val = std::any_cast<Rust::i64>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::u8>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::u16>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::u32>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::u64>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::Float>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Rust::Double>(&right)) {  return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uRust"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * CSharp Description:
    This method will convert a CSharp type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uCSharp(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<CSharp::byte>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::sbyte>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::short_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::ushort>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::int_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::uint>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::long_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::ulong>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::float_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::double_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<CSharp::decimal>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uCSharp"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * FSharp Description:
    This method will convert a FSharp type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uFSharp(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<FSharp::int_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<FSharp::float_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<FSharp::double_>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uFSharp"); }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Logging needs to go here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * ObjectiveC Description:
    This method will convert a ObjectiveC type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uObjectiveC(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<ObjectiveC::NSInteger>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<ObjectiveC::NSUInteger>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<ObjectiveC::CGFloat>(&right)) { return -(*val); }
            else { throw runtimeerror(right.getType(), "Unknown Type! in uObjectiveC"); }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Scala Description:
    This method will convert a Scala type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uScala(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Scala::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Scala::Long>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Scala::Float>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Scala::Double>(&right)) { return -(*val); }
            else {throw runtimeerror(right.getType(), "Unknown Type! in uScala");}
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * TypeScript Description:
    This method will convert a TypeScript type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uTypeScript(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            // TODO: Need to add more support for typescript
            if (auto val = std::any_cast<TypeScript::number>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uTypeScript");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Dart Description:
    This method will convert a Dart type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::staticLanguages::uDart(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Dart::int_>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Dart::double_>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uDart");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * PHP Description:
    This method will convert a PHP type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uPHP(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<PHP::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<PHP::Float>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uPHP");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * R Description:
    This method will convert a R type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uR(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<R::Integer>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<R::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uR");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Lua Description:
    This method will convert a Lua type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uLua(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = std::any_cast<Lua::Number>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uLua");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * MATLAB Description:
    This method will convert a MATLAB  type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uMATLAB(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            // TODO: Add more support  
            if (auto val = std::any_cast<MATLAB::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uMATLAB");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * VBA Description:
    This method will convert a VBA type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uVBA(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<LanguageTypes::VBA::Byte>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LanguageTypes::VBA::Integer>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LanguageTypes::VBA::Long>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LanguageTypes::VBA::Single>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LanguageTypes::VBA::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uVBA");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Groovy Description:
    This method will convert a Groovy type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uGroovy(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Groovy::Integer>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Groovy::Long>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Groovy::Double>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Groovy::Float>(&right)) { return -(*val); }
            else {
                throw runtimeerror("Unknown Type! in uGroovy");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Julia Description:
    This method will convert a Julia type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uJulia(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Julia::Int64>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Julia::Float64>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uJulia");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * PowerShell Description:
    This method will convert a PowerShell type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uPowerShell(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<PowerShell::Int>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uPowerShell");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * VisualBasics Description:
    This method will convert a VisualBasics type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::dynamicLanguages::uVisualBasic(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<VisualBasic::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<VisualBasic::Long>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<VisualBasic::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uVisualBasic");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/* ----------------------------------------------------------------------------
 * Dlang Description:
    This method will convert a Dlang type into a C++ representation type
 * Arguments:
 * LanguageTokenTypes& lang: and alias a enumerator
 * auto& right: Representing the right side of a ast
 * Returns:
    NULL if an error occured.
    Otherwise return the explicited converted object 
 * ----------------------------------------------------------------------------
*/
/*auto unaryOperations::otherLanguages::uDlang(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uDlang");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*
auto unaryOperations::dynamicLanguages::uHaskell(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Haskell::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Haskell::Float>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uHaskell");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uErlang(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Erlang::Number>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uErlang");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::dynamicLanguages::uClojure(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else if (auto val = std::any_cast<LanguageTypes::Clojure::Number>(&right)) { return -(*val); }
        else {
            throw runtimeerror("Unknown Type! in uClojure");
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uStandardML(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<StandardML::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<StandardML::Long>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<StandardML::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uStandardML");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uElm(LanguageTokenTypes& lang, auto& right) {
    // TODO: needs to be redone
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uElm");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::staticLanguages::uVHDLVerilog(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            // TODO: This needs to be redone
            if (auto val = std::any_cast<VHDLVerilog::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<VHDLVerilog::Long>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<VHDLVerilog::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uVHDLVerilog");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::staticLanguages::uFortran(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Fortran::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Fortran::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uFortran");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::staticLanguages::uCOBOL(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<COBOL::numeric>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uCOBOL");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::staticLanguages::uPascal(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = std::any_cast<Pascal::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Pascal::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uPascal");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::staticLanguages::uAda(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Ada::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Ada::Float>(&right)) { return -(*val); }
            else {
                throw runtimeerror("Unknown Type! in uAda");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::dynamicLanguages::uPerl(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Perl::Int>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Perl::Long>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Perl::Double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uPerl");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::dynamicLanguages::uAWK(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (true) {}
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uAWK");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uTCL(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uTCL");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::dynamicLanguages::uShell(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uShell");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;

}*/
/*
 *
*/
/*auto unaryOperations::dynamicLanguages::uLISPScheme(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {    
            if (auto val = std::any_cast<LISPScheme::Number>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uLISPScheme");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::dynamicLanguages::uRacket(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) {return NULL;}
        else {
            if (auto val = std::any_cast<double>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uRacket");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uProlog(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (true) {}
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uProlog");
            }
        }

    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::dynamicLanguages::uSmallTalk(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<SmallTalk::Integer>(&right)) { return -(*val); } 
            else if (auto val = std::any_cast<SmallTalk::Float>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uSmallTalk");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uHTMLCSS(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<HTMLCSS::Number>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uHTMLCSS");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uSQL(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<SQL::Integer>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<SQL::Decimal>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<SQL::Float>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uSQL");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::otherLanguages::uLabVIEW(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<LabVIEW::I8>(&right)) { return -(*val); } 
            else if (auto val = std::any_cast<LabVIEW::I16>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LabVIEW::I32>(&right)) { return -(*val);  }
            else if (auto val = std::any_cast<LabVIEW::I64>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LabVIEW::U8>(&right)) { return -(*val);  }
            else if (auto val = std::any_cast<LabVIEW::U16>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LabVIEW::U32>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LabVIEW::U64>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LabVIEW::SGL>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LabVIEW::DBL>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<LabVIEW::EXT>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uLabView");
            }
        }
    }
    catch(runtimeerror& e) {
        std::cout << e.what() << std::endl; 
    }
    return NULL;
}*/
/*
 *
*/
/*auto unaryOperations::staticLanguages::uEiffel(LanguageTokenTypes& lang, auto& right) {
    try {
        if (checkNumberOperand(right) == false) { return NULL; }
        else {
            if (auto val = std::any_cast<Eiffel::REAL>(&right)) { return -(*val); }
            else if (auto val = std::any_cast<Eiffel::INTEGER>(&right)) { return -(*val); }
            else {
                throw runtimeerror(right.getType(), "Unknown Type! in uEiffel");
            }
        }
    }
    catch(runtimeerror& e) {
        //TODO: Add Logging here
        std::cout << e.what() << std::endl;
    }
    return NULL;
}*/
/*
 *
*/
//auto unaryOperations::otherLanguages::uCustom(LanguageTokenTypes& lang, auto& right) {
    /*try {
        if (auto val = std::any_cast<Custom::numeric>(&right)) { return -(*val); }
        else {
            throw std::runtime_error(right.getType(), "Unsupported type for unary operation");
        *///}
        /*else if (right.isType<Custom::tokens>()) {
            // Handle token types (char, std::string)
            auto token = right.getValue<Custom::tokens>();
            // Perform unary operation on token
            // For example, convert to uppercase if it's a string
        }
        else if (right.isType<Custom::list>()) {
            // Handle list type (std::vector<std::any>)
            auto list = right.getValue<Custom::list>();
            // Perform unary operation on list
            // For example, reverse the list or apply operation to each element
        }
        else if (right.isType<Custom::dict>()) {
            // Handle dictionary type (std::map<std::any, std::any>)
            auto dict = right.getValue<Custom::dict>();
            // Perform unary operation on dictionary
            // For example, invert key-value pairs or apply operation to values
        }
        else if (right.isType<Custom::ptr>()) {
            // Handle pointer types
            auto ptr = right.getValue<Custom::ptr>();
            // Perform unary operation on pointer
            // For example, dereference and apply operation to pointed value
        }
        else if (right.isType<Custom::ref>()) {
            // Handle reference types
            auto ref = right.getValue<Custom::ref>();
            // Perform unary operation on reference
            // For example, modify the referred value
        }
        else {
            // Handle unsupported types
            throw std::runtime_error(right.getType(), "Unsupported type for unary operation");
        }

        // 2. Apply language-specific rules (if any)
        if (lang.hasSpecialRules()) {
            // Apply special rules based on the language
            // This could modify the result of the operation
        }*/
    //}
    //catch(runtimeerror& e) {
        //std::cout << e.what() << std::endl;
    //}
    //return NULL;
//}
