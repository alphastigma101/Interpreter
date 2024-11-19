#include <environment.h>
Environment::environment* Environment::environment::enclosing = nullptr;
/** -----------------------------------
 * @brief This is a default constructor for environment
 * 
 * @details This constructor along with environment(Environment::environment& enclosing) support block-scope.
            The idea is to keep the global variables defined in the outer-scope, while clearing out the inner scope variables 
 * -------------------------------------
*/
Environment::environment::environment(Environment::environment& enclosing) {
    this->enclosing = &enclosing;
}
/** -----------------------------------
 * @brief Method that gets the variable name from the map
 *  
 * @param name Is a token class instance which will be used to access the name and type of the variable
 * 
 * @return Returns the name of the variable otherwise returns null if not found. 
 * -------------------------------------
*/
String Environment::environment::get(Token name) {
    for (auto& it : env) {
        if (auto search = it.second.find(name.getLexeme()); search != it.second.end())
            return name.getLexeme();
    }
    if (enclosing != nullptr) return enclosing->get(name);
    throw new runtimeerror<Environment::environment>(name.getType(), String("Undefined variable '" + name.getLexeme() + "'.").c_str());
}
/** -----------------------------------
 * @brief Method that defines/re-defines the variable 
 *  
 * @param type Can be the supported the keyword types 
 * @param name The name of the variable 
 * @param value The value it is bind too. 
 * 
 * @return Returns the name of the variable otherwise returns null if not found. 
 * -------------------------------------
*/
void Environment::environment::define(String type, String name, Any value) {
    if (auto search = env.find(type); search != env.end()) {
        if (search->second.find(name) != search->second.end()) {
            env[type] = {{name, value}};  
            //throw new catcher<environment>(String("Variable '" + name + "' already defined in type '" + type.c_str() + "'").c_str());
        }
    }
    env[type] = {{name, value}};
}


/** -----------------------------------
 * @brief Method that updates the variables' values.
 *  
 * @param name Is a token class instance 
 * @param value The value it is bind too or updated. 
 * 
 * @return Returns the name of the variable otherwise returns null if not found. 
 * -------------------------------------
*/
void Environment::environment::assign(Token name, Any value) {
    for (const auto& it: types) {
        if (auto search = env.find(it); search != env.end()) {
            if (search->second.find(name.getLexeme()) != search->second.end()) {
                search->second.insert_or_assign(name.getLexeme(), value);
                return;  
            }
        }
    }
    if (enclosing != nullptr) {
      enclosing->assign(name, value);
      return;
    }
    throw new runtimeerror<Environment::environment>(name.getType(),
        String("Undefined variable '" + name.getLexeme() + "'.").c_str());
}