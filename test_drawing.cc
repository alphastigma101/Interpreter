#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
void moveCursor(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void drawStickFigures() {
    cout << "   O   O   \n";
    cout << "   |   |   \n";
    cout << "   |   |   \n";
    cout << "  / \\ / \\  \n";
    cout << "-------------\n";
}

void drawNuke(int height) {
    // Print spaces to position the nuke
    for (int i = 0; i < height; i++) {
        cout << endl;
    }
    cout << "            '--' \n";
    cout << "           /_____\\\n";
    cout << "           |     |\n";
    cout << "           |     |\n";
    cout << "           |_____|\n";
    cout << "           |     |\n";
    cout << "           |     |\n";
    cout << "            \\   /\n";
    cout << "             | |\n";
    cout << "             | |\n";
    cout << "             | |\n";
    cout << "             | |\n";
    cout << "           /     \\\n";
    cout << "          |_______|\n";
    cout << "          |       |\n";
    cout << "           \\_|__/ \n";
    cout << "            \\ | /\n";
    cout << "             \\|/ \n";
}

void drawExplosion() {
    cout << "       . . .      \n";
    cout << "     . . . . .    \n";
    cout << "   . . . . . . .  \n";
    cout << " . . . . . . . . .\n";
    cout << "     . . . . .    \n";
    cout << "       . . .      \n";
}

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the screen
}
void drawMiniatureNuke(int x, int y) {
    moveCursor(x, y);
    cout << "  '--'  \n";
    cout << " /_____\\\n";
    cout << " |     |\n";
    cout << " |     |\n";
    cout << " |_____|\n";
    cout << " |     |\n";
    cout << " |     |\n";
    cout << "  \\   /\n";
    cout << "   | |\n";
    cout << "   | |\n";
    cout << "   | |\n";
    cout << "   | |\n";
    cout << " /     \\\n";
    cout << "|_______|\n";
    cout << "|       |\n";
    cout << " \\_|__/ \n";
    cout << "  \\ | /\n";
    cout << "   \\|/ \n";
}

void drawMiniatureNukeGrid(int numRows, int numCols) {
    int spacing = 6; // Space between each nuke

    for (int y = 0; y < numRows; y++) {
        for (int x = 0; x < numCols; x++) {
            drawMiniatureNuke(x * spacing, y * spacing);
        }
    }
}

int main() {
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
        cout << string(20, ' ') << endl;  // Clear previous position, this is not working!
        
        // Draw falling object at new position
        moveCursor(0, i);
        drawNuke(0);
        //drawMiniatureNukeGrid(i, i);
        
        
        // Redraw stick figures (they stay in place)
        moveCursor(0, groundLevel);
        drawStickFigures();
        if (i == groundLevel) break;
        
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    // Draw explosion where the stick figures were
    clearScreen();
    drawExplosion();

    return 0;
}
