#include <abstraction_tree_syntax.h>
#include <scanner.h>
#include <parser.h>
#include <interpreter.h>
#include <filesystem>
#include <system_error>
#include <fstream>
static bool hadError = false;
/** -------------------------------------------------------------------------
 * @brief Is a standalone static void function that runs the user input 
 * 
 * @param source: is a file that contains data of possibly of a language 
 *
 * @return If an error occurred while parsing it will return back void. Otherwise, continue to execute 
*/
static void run(std::string& source) {
    Scanner scanner(source); // Create a new scanner instance
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto stmt = p.parse();
    if (hadError) return;
    std::thread build([&stmt]() {
        return ast(stmt);
    });
    if (hadError) return;
    interpreter interp(stmt);
    auto env = interp.getEnv()->getMap();
    for (const auto& it: env) {
        std::cout << std::any_cast<String>(it.second) << std::endl;
    } 
    if (build.joinable()) {
        build.join();
    }
   //cTree.clear();

}
/** ------------------------------------------------------------------------- 
 * @brief This function will implement > at runtime 
 *
 * -------------------------------------------------------------------------
*/
static void runPrompt() {
     try {
        for (;;) { 
            std::cout << "> ";
            std::string line;
            std::getline(std::cin, line); // get user input
            if (line[0] == '\0' || line.empty()) break;
            run(line);
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
static void report(int &line, std::string where, std::string& message) {
    std::cout << "[line " <<  line << "] Error" << where << ": " + message;
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
static void error(int& line, std::string& message) { report(line, "", message); }

//TODO: Update the function below so it takes in more than one file 
/** ------------------------------------------------------------------------- 
 * @brief This function will run the file. 
 *
 * @param filePath The file that was fed into the program
 * -------------------------------------------------------------------------
*/
static void runFile(const std::string& filePath) {
    std::string source,line;
    if (std::filesystem::exists(filePath)) {
        std::ifstream file (std::filesystem::path(filePath).stem());
        if (file.is_open()) { 
            while (std::getline(file, line)) {
                source.append(line);
            }
            file.close();
            run(source);
            // Indicate an error in the exit code.
            if (hadError) exit(1);
        }
    }
    else {
        std::cout << "Not a valid file" << std::endl;
        runPrompt();
    }
}


// This is the driver code
int main(int argc, char **argv) {
    if (argc > 2) {
        std::cerr << "Usage: [script]";
        exit(1); 
    }
    else if (argc == 2) runFile(argv[1]);
    else { runPrompt(); }
    return 0;
}
