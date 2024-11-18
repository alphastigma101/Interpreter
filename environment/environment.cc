#include <environment.h>
/** -----------------------------------
 * @brief This is a default constructor for environment 
 * 
 * -------------------------------------
*/
Environment::environment::environment(): Interpreter::interpreter(cTree) {

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
    return "\0";
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


