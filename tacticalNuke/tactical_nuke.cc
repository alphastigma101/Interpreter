#include <tactical_nuke.h>
#include <scanner.h>
#include <context_free_grammar.h>
#include <parser.h>
#include <interpreter.h>
#include <resolver.h>
#include <filesystem>
#include <system_error>
#include <fstream>
#include <tactical_nuke.h>
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
  parser p(tokens);
  auto stmt = p.parse();
  if (hadError) return;
  /*std::thread build([&stmt]() {
      return ast(stmt);
  });*/
  if (hadError) return;
  Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
  resolver->resolve(stmt);
  interpreter interp(stmt);
  auto env = interp.getEnv()->getMap();
  for (const auto& it: env) {
      std::cout << std::any_cast<String>(it.second) << std::endl;
  } 
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
void NuclearLang::Nuke::runFile(const char* filePath) {
  String source,line;
  if (std::filesystem::exists(filePath)) {
    std::ifstream file (std::filesystem::path(filePath).stem());
    if (file.is_open()) { 
      while (std::getline(file, line)) 
        source.append(line);
      file.close();
      run(source.c_str());
      // Indicate an error in the exit code.
      if (hadError) exit(1);
    }
  }
  else {
    std::cout << "Not a valid file" << std::endl;
    runPrompt();
  }
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
*/
Any NuclearLang::NukeFunction::call(Interpreter::interpreter *interp, const Vector<Any> &arguments) {
  Environment::environment *environment = new Environment::environment(*closure);
  for (int i = 0; i < declaration->params.size(); i++) {
      environment->define(declaration->params.at(i).getLexeme(), arguments.at(i));
  }
  try { interp->executeBlock(declaration->statements, environment); } 
  catch (NuclearLang::NukeReturn* returnValue) {
    if (isInitializer) return closure->getAt(0, "this");
    environment->assign(declaration->op, new NukeFunction(declaration, closure, returnValue));
    closure = std::move(environment);
    return returnValue->value;
  }
  if (isInitializer) return closure->getAt(0, "this");
  return nullptr;
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
  return new NuclearLang::NukeFunction(declaration, environment, isInitializer);
}
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param stmt A raw pointer to an abstract class called Statement
 * 
 * @return returns nullptr 
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
void NuclearLang::NukeInstance::set(Token name, Any value) { fields->insert_or_assign(name.getLexeme(), value); }
/** ---------------------------------------------------------------
 * @brief ... 
 * 
 * @param name An lvalue of the token class 
 * 
 * @return None. It instead throws an exception  
*/
Any NuclearLang::NukeInstance::get(Token name) {
  if (auto search = fields->find(name.getLexeme()); search != fields->end()) {
    return search->second;
  }
  NuclearLang::NukeFunction* method = klass->findMethod(new String(name.getLexeme()));
  if (method != nullptr) return method->bind(this);
  throw runtimeerror<NuclearLang::NukeClass>(name, String("Undefined property '" + name.getLexeme() + "'.").c_str());
}
NuclearLang::NukeFunction* NuclearLang::NukeClass::findMethod(void* name) {
  auto* methodMap = reinterpret_cast<Map<String, NuclearLang::NukeFunction>*>(methods);
  auto* nameStr = reinterpret_cast<String*>(name);
  if (methodMap->find(*nameStr) != methodMap->end()) {
    return &methodMap->at(*nameStr);
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