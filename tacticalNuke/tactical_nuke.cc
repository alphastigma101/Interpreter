#include <interpreter.h>
Any NuclearLang::NukeFunction::call(Interpreter::interpreter* interp, const Vector<Any>& arguments) {
  Environment::environment* environment = new Environment::environment(*closure);
  for (int i = 0; i < declaration->params.size(); i++) {
    environment->define(declaration->params.at(i).getLexeme(), arguments.at(i));
  }
  try {
    interp->executeBlock(declaration->statements, environment);
  } catch (NuclearLang::NukeReturn* returnValue) {
    environment->assign(declaration->op, new NukeFunction(declaration, closure, returnValue));
    closure = std::move(environment);
    return returnValue->value;
  }
  return nullptr;
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