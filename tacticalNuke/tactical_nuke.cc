#include <interpreter.h>
#include "tactical_nuke.h"
Any NuclearLang::NukeFunction::call(Interpreter::interpreter *interp, const Vector<Any> &arguments) {
    Environment::environment *environment = new Environment::environment(*closure);
    for (int i = 0; i < declaration->params.size(); i++) {
        environment->define(declaration->params.at(i).getLexeme(), arguments.at(i));
    }
    try {
      interp->executeBlock(declaration->statements, environment);
    } 
    catch (NuclearLang::NukeReturn* returnValue) {
      int zero = 0;
      if (isInitializer) return closure->getAt(zero, "this");
      environment->assign(declaration->op, new NukeFunction(declaration, closure, returnValue));
      closure = std::move(environment);
      return returnValue->value;
    }
  int zero = 0;
  if (isInitializer) return closure->getAt(zero, "this");
  return nullptr;
}
NuclearLang::NukeFunction* NuclearLang::NukeFunction::bind(NukeInstance *instance) {
  Environment::environment* environment = new Environment::environment(*closure);
  environment->define("this", instance);
  return new NuclearLang::NukeFunction(declaration, environment, isInitializer);
}
Any NuclearLang::NukeClass::call(Interpreter::interpreter* interp, const Vector<Any>& arguments) {
  NuclearLang::NukeInstance* instance = new NuclearLang::NukeInstance(this);
  NuclearLang::NukeFunction initializer = findMethod(new String("init"));
    if (&initializer != nullptr) {
      initializer.bind(instance)->call(interp, arguments);
    }
  return std::move(instance);
}

int NuclearLang::NukeClass::arity(int argc) {
  NuclearLang::NukeFunction initializer = findMethod(new String("init"));
  if (&initializer == nullptr) return 0;
  return initializer.arity();
}

void NuclearLang::NukeInstance::set(Token name, Any value) {
  fields->insert_or_assign(name.getLexeme(), value);
}

Any NuclearLang::NukeInstance::get(Token name) {
  if (auto search = fields->find(name.getLexeme()); search != fields->end()) {
    return search->second;
  }
  NuclearLang::NukeFunction method = klass->findMethod(new String(name.getLexeme()));
  if (&method != nullptr) return method.bind(this);
  /*throw runtimeerror(name, 
      "Undefined property '" + name.getLexeme() + "'.");*/
}
NuclearLang::NukeFunction NuclearLang::NukeClass::findMethod(void* name) {
  auto* methodMap = reinterpret_cast<Map<String, NuclearLang::NukeFunction>*>(methods);
  auto* nameStr = reinterpret_cast<String*>(name);
  if (methodMap->find(*nameStr) != methodMap->end()) {
    return methodMap->at(*nameStr);
  }
  throw;
  //return nullptr;

}

void NuclearLang::NukeFunction::moveCursor(int x, int y) {
  std::cout << "\033[" << y << ";" << x << "H";
}

void NuclearLang::NukeFunction::drawStickFigures() {
  std::cout << "   O   O   \n";
  std::cout << "   |   |   \n";
  std::cout << "   |   |   \n";
  std::cout << "  / \\ / \\  \n";
  std::cout << "-------------\n";
}

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
