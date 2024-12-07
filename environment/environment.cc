#include <environment.h>
Environment::environment* Environment::environment::enclosing = nullptr;
Lists::linkedList<Environment::environment>* Environment::environment::newEnv = new Lists::linkedList<Environment::environment>();
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
 * @return Returns the variable's value if found, otherwise returns null if not found. 
 * -------------------------------------
*/
Any Environment::environment::get(Token name) {
    if (auto search = env.find(name.getLexeme()); search != env.end())
        return search->second;
    if (enclosing != nullptr) return enclosing->get(name);
    
    throw runtimeerror<Environment::environment>(name.getType(), String("Undefined variable '" + name.getLexeme() + "'.").c_str());
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
void Environment::environment::define(String name, Any value) {
   env[name] = value;
   //newEnv->insert(name, value);
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
    if (auto search = env.find(name.getLexeme()); search != env.end()) {
        env.insert_or_assign(name.getLexeme(), value);
        return;  
    }
    //if (newEnv->assign(name.getLexeme(), value)) return;
    if (enclosing != nullptr) {
      enclosing->assign(name, value);
      return;
    }
    throw runtimeerror<Environment::environment>(name.getType(),
        String("Undefined variable '" + name.getLexeme() + "'.").c_str());
}