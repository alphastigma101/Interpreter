#include <scanner.h>
#include <context_free_grammar.h>
#include <parser.h>
#include <interpreter.h>
#include <resolver.h>
#include <filesystem>
#include <system_error>
#include <fstream>
#include "tactical_nuke.h"
void* NuclearLang::NukeFunction::declaration = nullptr;
//void* NuclearLang::NukeClass::methods = nullptr;
//void* NuclearLang::NukeClass::fieldProperties = nullptr;
//void* NuclearLang::NukeClass::superclass = nullptr;

/** -------------------------------------------------------------------------
 * @brief Is a standalone static void function that runs the user input 
 * 
 * @param source: is a file that contains data of possibly of a language 
 *
 * @return If an error occurred while parsing it will return back void. Otherwise, continue to execute 
*/
void NuclearLang::Nuke::run(const char* source) {
  Scanner scanner(source); // Create a new scanner instance
  Vector<Token> tokens = scanner.ScanTokens();
  Parser::parser p(tokens);
  auto stmt = p.parse();
  if (hadError) return;
  /*std::thread build([&stmt]() {
      return ast(stmt);
  });*/
  if (hadError) return;
  Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
  resolver->resolve(stmt);
  Interpreter::interpreter interp(stmt);
  auto env = interp.getEnv()->getMap();
  //for (const auto& it: env) {
    //std::cout << std::any_cast<String>(it.second) << std::endl;
  //} 
  /*if (build.joinable()) {
      build.join();
  }*/
  //cTree.clear();

}
/** ------------------------------------------------------------------------- 
 * @brief This function will implement > at runtime 
 *
 * -------------------------------------------------------------------------
*/
void NuclearLang::Nuke::runPrompt() {
  try {
    for (;;) { 
      std::cout << "> ";
      std::string line;
      std::getline(std::cin, line); // get user input
      if (line[0] == '\0' || line.empty()) break;
      run(line.c_str());
    }
  }
  catch(const std::system_error& e) {
    std::cout << "Caught system_error with code " "[" << e.code() << "] meaning " "[" << e.what() << "]\n";
  }
}
/** -------------------------------------------------------------------------
 * @brief This function will report an error if something crashed
 *
 * @param line The line it occured
 * @param where The string literal
 * @param message The message as to why it crashed
 *
 * @return None
 *
 * -------------------------------------------------------------------------
 */
void NuclearLang::Nuke::report(int line, const char* where, const char* message) {
  std::cout << "[line " <<  line << "] Error" << where << ": " << message;
  hadError = true;
}
/** -------------------------------------------------------------------------
 * @brief A helper function that calls in report and uses the pass by reference
 *
 * @param line the source line
 * @param message the message as to why it crashed
 *
 * -------------------------------------------------------------------------
 */
void NuclearLang::Nuke::error(int line, const char* message) {
  report(line, "", message);
}
//TODO: Update the function below so it takes in more than one file 
/** ------------------------------------------------------------------------- 
 * @brief This function will run the file. 
 *
 * @param filePath The file that was fed into the program
 * -------------------------------------------------------------------------
*/
void NuclearLang::Nuke::runFile(const char* Path) {
  if (std::filesystem::directory_entry(String(Path)).is_directory()) {
    try {
      auto temp = std::filesystem::directory_entry(String(Path));
      multipleFiles(&temp);
      return;
    }
    catch(...) {
      std::cout << "Directory must contain either files or another dictionary that contains files!" << std::endl;
      runPrompt();
    }
  }
  else {
    try {
      singleFiles(Path);
      return;
    }
    catch(...) {
      std::cout << "Must pass in a existing filename." << std::endl;
      runPrompt();
    }
  }
}
void NuclearLang::Nuke::multipleFiles(void *dir) {
  String source,line;
  auto files = reinterpret_cast<std::filesystem::directory_entry*>(dir);
  for (auto const& dir_entry : std::filesystem::directory_iterator{*files}) { 
    if (std::filesystem::is_regular_file(dir_entry))
      std::cout << " is a regular file\n";
    if (std::filesystem::is_directory(dir_entry))
      std::cout << " is a directory\n";
  }
}

void NuclearLang::Nuke::singleFiles(const char* data) {
  String source,line;
  try {
    std::ifstream file(String(data).c_str());
    if (file.is_open()) { 
      while (std::getline(file, line)) 
        source.append(line);
      file.close();
      run(source.c_str());
      // Indicate an error in the exit code.
      if (hadError) exit(1);
    }
  }
  catch(...) {
    std::cout << "Not a real file!" << std::endl;
    throw;
  }
  return;
}

NuclearLang::NukeFunction::NukeFunction(ContextFreeGrammar::Functions* declaration, Environment::environment* closure, NukeReturn* returnValue){
  this->closure = std::move(closure);
  this->declaration = reinterpret_cast<ContextFreeGrammar::Functions*>(std::move(declaration));
  this->value = std::move(returnValue->value);
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
Any NuclearLang::NukeFunction::call(Interpreter::interpreter *interp, const Vector<Any> arguments) {
  Environment::environment *environment = new Environment::environment(*closure);
  for (int i = 0; i < reinterpret_cast<ContextFreeGrammar::Functions*>(declaration)->params.size(); i++) {
    environment->define(reinterpret_cast<ContextFreeGrammar::Functions*>(declaration)->params.at(i).getLexeme(), arguments.at(i));
  }
  try { 
    interp->executeBlock(reinterpret_cast<ContextFreeGrammar::Functions*>(declaration)->statements, environment); 
  } 
  catch (NuclearLang::NukeReturn* returnValue) {
    if (isInitializer) return closure->getAt(0, "this");
    environment->assign(reinterpret_cast<ContextFreeGrammar::Functions*>(declaration)->op, new NukeFunction(reinterpret_cast<ContextFreeGrammar::Functions*>(declaration), closure, returnValue));
    closure = std::move(environment);
    return returnValue->value;
  }
  if (isInitializer) return closure->getAt(0, "this");
  return nullptr;
}
int NuclearLang::NukeFunction::arity(int argc) { 
  return reinterpret_cast<ContextFreeGrammar::Functions*>(declaration)->params.size(); 
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
NuclearLang::NukeFunction* NuclearLang::NukeFunction::bind(NukeInstance *instance) {
  Environment::environment* environment = new Environment::environment(*closure);
  environment->define("this", instance);
  return new NuclearLang::NukeFunction(reinterpret_cast<ContextFreeGrammar::Functions*>(declaration), environment, isInitializer);
}
/** ---------------------------------------------------------------
 * @brief Whenever this method is called, it will create a new instance  
 * 
 * @param interp A raw pointer to a class called Interpreter
 * @param arguments A Vector that holds a list of Any types
 * 
 * @return returns the allocated instance of the user defined class 
*/
Any NuclearLang::NukeClass::call(Interpreter::interpreter* interp, const Vector<Any>& arguments) {
  NuclearLang::NukeInstance* instance = new NuclearLang::NukeInstance(this);
  NuclearLang::NukeFunction* initializer = findMethod(new String("init"));
  if (initializer != nullptr) {
    initializer->bind(instance)->call(interp, arguments);
  }
  return std::move(instance);
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
int NuclearLang::NukeClass::arity(int argc) {
  NuclearLang::NukeFunction* initializer = findMethod(new String("init"));
  if (initializer == nullptr) return 0;
  return initializer->arity();
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
void NuclearLang::NukeInstance::set(Token name, Any value) { fields.insert_or_assign(name.getLexeme(), value); }
/** ---------------------------------------------------------------
 * @brief searches for methods/properties that have been defined with a certain instance 
 * 
 * @param name An lvalue of the token class 
 * 
 * @details Will throw an exception if a property has not been defined globally
 * 
 * @return None. It instead throws an exception  
*/
Any NuclearLang::NukeInstance::get(Token name) {
  if (auto search = fields.find(name.getLexeme()); search != fields.end()) {
    return search->second;
  }
  NuclearLang::NukeFunction* method = klass->findMethod(new String(name.getLexeme()));
  if (method != nullptr) return method->bind(this);
  throw runtimeerror<NuclearLang::NukeClass>(name, String("Undefined property '" + name.getLexeme() + "'.").c_str());
}
/** -------------------------------------
 * @brief search the class instance to aquire the field and properties types 
 * 
 * @param name is a void pointer that points to the identifier to search in the map
 *             It must be an instance of a class called Token
 * 
 * @return None.
 * 
 * --------------------------------------
*/
void* NuclearLang::NukeInstance::getClassFieldProperties(void *name) {
  auto temp = reinterpret_cast<Token*>(name);
  auto properties = reinterpret_cast<Map<String, NuclearLang::NukeProperties>*>(klass->fieldProperties);
  if (auto search = properties->find(temp->getLexeme()); search != properties->end()) {
    return &(reinterpret_cast<NuclearLang::NukeProperties&>(search->second));
  }
  throw runtimeerror<NuclearLang::NukeClass>();
}
NuclearLang::NukeFunction* NuclearLang::NukeClass::findMethod(void* name) {
  auto& methodMap = *reinterpret_cast<Map<String, NuclearLang::NukeFunction>*>(methods);
  auto& nameStr = *reinterpret_cast<String*>(name);
  if (methodMap.find(nameStr) != methodMap.end()) {
    return &methodMap.at(nameStr);
  }
  if (superclass != nullptr) {
    auto& super = *reinterpret_cast<Any*>(superclass);
    if (super.type() == typeid(NuclearLang::NukeClass*)) {
      const auto& method = std::any_cast<NuclearLang::NukeClass*>(std::move(super))->findMethod(name);
      return method;
    }
  }
  return nullptr;
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
void NuclearLang::NukeFunction::moveCursor(int x, int y) { std::cout << "\033[" << y << ";" << x << "H"; }
void NuclearLang::NukeFunction::drawStickFigures() {
  std::cout << "   O   O   \n";
  std::cout << "   |   |   \n";
  std::cout << "   |   |   \n";
  std::cout << "  / \\ / \\  \n";
  std::cout << "-------------\n";
}
/** ---------------------------------------------------------------
 * @brief Draws the nuke that will bomb the family of stick figures 
 * 
 * @param height An integer literal where the nuke will be dropped at
 * 
 * @return Nothing
*/
void NuclearLang::NukeFunction::drawNuke(int height) {
  // Print spaces to position the nuke
  for (int i = 0; i < height; i++) {
    std::cout << std::endl;
  }
  std::cout << "            '--' \n";
  std::cout << "           /_____\\\n";
  std::cout << "           |     |\n";
  std::cout << "           |     |\n";
  std::cout << "           |_____|\n";
  std::cout << "           |     |\n";
  std::cout << "           |     |\n";
  std::cout << "            \\   /\n";
  std::cout << "             | |\n";
  std::cout << "             | |\n";
  std::cout << "             | |\n";
  std::cout << "             | |\n";
  std::cout << "           /     \\\n";
  std::cout << "          |_______|\n";
  std::cout << "          |       |\n";
  std::cout << "           \\_|__/ \n";
  std::cout << "            \\ | /\n";
  std::cout << "             \\|/ \n";
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
void NuclearLang::NukeFunction::drawExplosion() {
  std::cout << "       . . .      \n";
  std::cout << "     . . . . .    \n";
  std::cout << "   . . . . . . .  \n";
  std::cout << " . . . . . . . . .\n";
  std::cout << "     . . . . .    \n";
  std::cout << "       . . .      \n";
}

void NuclearLang::NukeFunction::clearScreen() {
  std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
void NuclearLang::NukeFunction::drawMiniatureNuke(int x, int y) {
  moveCursor(x, y);
  std::cout << "  '--'  \n";
  std::cout << " /_____\\\n";
  std::cout << " |     |\n";
  std::cout << " |     |\n";
  std::cout << " |_____|\n";
  std::cout << " |     |\n";
  std::cout << " |     |\n";
  std::cout << "  \\   /\n";
  std::cout << "   | |\n";
  std::cout << "   | |\n";
  std::cout << "   | |\n";
  std::cout << "   | |\n";
  std::cout << " /     \\\n";
  std::cout << "|_______|\n";
  std::cout << "|       |\n";
  std::cout << " \\_|__/ \n";
  std::cout << "  \\ | /\n";
  std::cout << "   \\|/ \n";
}

void NuclearLang::NukeFunction::drawMiniatureNukeGrid(int numRows, int numCols) {
  int spacing = 6; // Space between each nuke
  for (int y = 0; y < numRows; y++) {
    for (int x = 0; x < numCols; x++) {
      drawMiniatureNuke(x * spacing, y * spacing);
    }
  }
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
void NuclearLang::NukeFunction::launch() {
  int nukeDropHeight = 20;  // Increased height for better visibility
  int groundLevel = 25;     // Position where stick figures will be drawn
  clearScreen();
  // Draw stick figures at fixed position
  moveCursor(0, groundLevel);
  drawStickFigures();

  // Simulate dropping
  for (int i = 0; i < 15; i++) {
    // Clear previous position of falling object
    moveCursor(0, i - 1);
    std::cout << String(20, ' ') << std::endl;  // Clear previous position, this is not working!
    
    // Draw falling object at new position
    moveCursor(0, i);
    drawNuke(0);
    //drawMiniatureNukeGrid(i, i);
    
    
    // Redraw stick figures (they stay in place)
    moveCursor(0, groundLevel);
    drawStickFigures();
    if (i == groundLevel) break;
    
    //this_thread::sleep_for(chrono::milliseconds(500));
  }
  // Draw explosion where the stick figures were
  clearScreen();
  drawExplosion();
  return;
}

const void *NuclearLang::NukeClass::getType() {
  return reinterpret_cast<Token*>(runtimeerror<NuclearLang::NukeClass>::type);
}

const char *NuclearLang::NukeClass::what(const void *type, const char *msg) throw() {
  auto& temp = *reinterpret_cast<const Token*>(type);
  Token op = std::move(temp);
  return String("Error in NukeReturn. Failed to interpret: " + op.getLexeme() + String(msg)).c_str();
}

const void *NuclearLang::NukeReturn::getType() {
  return reinterpret_cast<Token*>(runtimeerror<NuclearLang::NukeReturn>::type);
}
const char *NuclearLang::NukeReturn::what(const void *type, const char *msg) throw() {
  auto& temp = *reinterpret_cast<const Token*>(type);
  Token op = std::move(temp);
  return String("Error in NukeReturn. Failed to interpret: " + op.getLexeme() + String(msg)).c_str();
}
