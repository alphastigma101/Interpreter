#include <interpreter.h>
#include <resolver.h>


// This is the driver code
int main(int argc, char **argv) {
    NuclearLang::Nuke nuke;
    if (argc > 2) {
        std::cerr << "Usage: [script]";
        exit(1); 
    }
    else if (argc == 2) nuke.runFile(argv[1]);
    else { nuke.runPrompt(); }
    return 0;
}
