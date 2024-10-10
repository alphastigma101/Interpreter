#include <scanner.h> 
#include <parser.h>
#include <interpreter.h>
#include <filesystem>
#include <system_error>
#include <fstream>
static bool hadError = false;
// Declare the external types here 
static LanguageTokenTypes interpretLanguage;
String file_name, user_choice;
int settings;
//LanguageType<LanguageTokenTypes> type;
//void setTokenLanguage(const LanguageType<LanguageTokenTypes>& value);
//LanguageType<LanguageTokenTypes> getTokenLanguage();


/* -------------------------------------------------------------------------
 * @brief Is a standalone static void function that runs the user input 
 * 
 * @param source: is a file that contains data of possibly of a language 
 *
 * @return If an error occurred while parsing it will return back void. Otherwise, continue to execute 
*/
static void run(std::string& source) {
    Scanner scanner(source); // Create a new scanner instance
    std::vector<Token> tokens = scanner.ScanTokens();
    setTokenLanguage(interpretLanguage); // set the language
    parser p(tokens);
    p.parse();
    std::thread build_(ast(p.nodes));
    if (settings) {
        auto temp = p.nodes; // Make a copy 
        interpreter interp(std::move(temp), getTokenLanguage());
    }
    else {
        // TODO: This is just an example and it needs to be properly filled out
        //compiler c();
    }
    if (hadError) return;
}

// TODO: Make sure that the maps in language_lookup.h key's match and also here as well 
/** ------------------------------------------------------------------------- 
 * @brief This looks for whatever the user inputed. If not found, it will assume it is running custom and return it 
 *
 * -------------------------------------------------------------------------
*/

static LanguageTokenTypes user_language(const std::string& choice) {
    if (choice == "Python") return LanguageTokenTypes::Python;
    else if (choice == "JavaScript") return LanguageTokenTypes::JavaScript;
    else if (choice == "Ruby") return LanguageTokenTypes::Ruby;
    else if (choice == "C") return LanguageTokenTypes::C;
    else if (choice == "CPP" || choice == "C++") return LanguageTokenTypes::CPP;
    else if (choice == "Java") return LanguageTokenTypes::Java;
    else if (choice == "Go") return LanguageTokenTypes::Go;
    else if (choice == "Kotlin") return LanguageTokenTypes::Kotlin;
    else if (choice == "Swift") return LanguageTokenTypes::Swift;
    else if (choice == "Rust") return LanguageTokenTypes::Rust;
    else if (choice == "Haskell") return LanguageTokenTypes::Haskell;
    else if (choice == "CSharp" || choice == "C#") return LanguageTokenTypes::CSharp;
    else if (choice == "FSharp" || choice == "F#") return LanguageTokenTypes::FSharp;
    else if (choice == "ObjectiveC" || choice == "Objective-C") return LanguageTokenTypes::ObjectiveC;
    else if (choice == "VHDLVerilog" || choice == "VHDL/Verilog") return LanguageTokenTypes::VHDLVerilog;
    else if (choice == "Fortran") return LanguageTokenTypes::Fortran;
    else if (choice == "COBOL") return LanguageTokenTypes::COBOL;
    else if (choice == "Pascal") return LanguageTokenTypes::Pascal;
    else if (choice == "Ada") return LanguageTokenTypes::Ada;
    else if (choice == "Scala") return LanguageTokenTypes::Scala;
    else if (choice == "TypeScript") return LanguageTokenTypes::TypeScript;
    else if (choice == "Dart") return LanguageTokenTypes::Dart;
    else if (choice == "PHP") return LanguageTokenTypes::PHP;
    else if (choice == "Perl") return LanguageTokenTypes::Perl;
    else if (choice == "R") return LanguageTokenTypes::R;
    else if (choice == "Lua") return LanguageTokenTypes::Lua;
    else if (choice == "Shell" || choice == "Bash") return LanguageTokenTypes::Shell;
    else if (choice == "MATLAB") return LanguageTokenTypes::MATLAB;
    else if (choice == "VBA") return LanguageTokenTypes::VBA;
    else if (choice == "LISPScheme" || choice == "LISP" || choice == "Scheme") return LanguageTokenTypes::LISPScheme;
    else if (choice == "Groovy") return LanguageTokenTypes::Groovy;
    else if (choice == "Erlang") return LanguageTokenTypes::Erlang;
    else if (choice == "Clojure") return LanguageTokenTypes::Clojure;
    else if (choice == "Prolog") return LanguageTokenTypes::Prolog;
    else if (choice == "AWK") return LanguageTokenTypes::AWK;
    else if (choice == "TCL") return LanguageTokenTypes::TCL;
    else if (choice == "Julia") return LanguageTokenTypes::Julia;
    else if (choice == "PowerShell") return LanguageTokenTypes::PowerShell;
    else if (choice == "Racket") return LanguageTokenTypes::Racket;
    else if (choice == "Smalltalk") return LanguageTokenTypes::SmallTalk;
    else if (choice == "HTMLCSS" || choice == "HTML/CSS") return LanguageTokenTypes::HTMLCSS;
    else if (choice == "SQL") return LanguageTokenTypes::SQL;
    else if (choice == "LabVIEW") return LanguageTokenTypes::LabVIEW;
    else if (choice == "VisualBasic" || choice == "VB") return LanguageTokenTypes::VisualBasic;
    else if (choice == "Elm") return LanguageTokenTypes::Elm;
    else if (choice == "Eiffel") return LanguageTokenTypes::Eiffel;
    else if (choice == "StandardML" || choice == "SML") return LanguageTokenTypes::StandardML;
    else if (choice == "Dlang" || choice == "D") return LanguageTokenTypes::Dlang;
    else return LanguageTokenTypes::Custom;
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
static void error(int& line, std::string& message) { report(line, "", std::move(message)); }

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
    Table table = initTable(languageExtensions, downloads);
    if (argc > 2) {
        std::cout << "Supported languages" << std::endl;
        for (const std::pair<const std::string, std::pair<std::vector<std::string>, std::vector<std::string>>>& it : table) { std::cout << it.first << std::endl; }
        std::cerr << "Usage: [script] [language]";
        exit(1); 
    }
    else {
        interpretLanguage = user_language((std::string)argv[2]);
        user_choice = (std::string)argv[2]; // user_choice comes from language_types.h
        file_name = (std::string)argv[1];
        runFile((std::string)argv[1]);
    } 
    else { runPrompt(); }
    return 0;
}
