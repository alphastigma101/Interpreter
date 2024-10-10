#include <languages.h>
#include <lookup_language.h>

static void other_langs(other_languages& o_t, std::string& choice) {
    if (choice == "HTMLCSS") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "HTML/CSS Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.HTMLCSS() << std::endl;
    }
    else if (choice == "SQL") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "SQL Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.SQL() << std::endl;
    }
    else if (choice == "LabVIEW") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "LabVIEW Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.LabVIEW() << std::endl;
    }
    else if (choice == "VisualBasic") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Visual Basic Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.VisualBasic() << std::endl;
    }
    else if (choice == "Elm") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Elm Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.Elm() << std::endl;
    }
    else if (choice == "Eiffel") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Eiffel Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.Eiffel() << std::endl;
    }
    else if (choice == "StandardML") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Standard ML Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.StandardML() << std::endl;
    }
    else if (choice == "Dlang") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "D Language Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << o_t.Dlang() << std::endl;
    }
    else {
        std::cout << "Invalid choice!" << std::endl;
        exit(0);
    }
}
static void dynamic_langs(dynamic_languages& d_t, std::string& choice) {
    if (choice == "Python") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Python Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Python() << std::endl;
    }
    else if (choice == "JavaScript") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "JavaScript Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.JavaScript() << std::endl;
    }
    else if (choice == "Ruby") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Ruby Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Ruby() << std::endl;
    }
    else if (choice == "PHP") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "PHP Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.PHP() << std::endl;
    }
    else if (choice == "Perl") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Perl Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Perl() << std::endl;
    }
    else if (choice == "R") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "R Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.R() << std::endl;
    }
    else if (choice == "Lua") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Lua Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Lua() << std::endl;
    }
    else if (choice == "Shell") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Shell Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Shell() << std::endl;
    }
    else if (choice == "MATLAB") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "MATLAB Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.MATLAB() << std::endl;
    }
    else if (choice == "VBA") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "VBA Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.VBA() << std::endl;
    }
    else if (choice == "LISPScheme") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "LISP/Scheme Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.LISPScheme() << std::endl;
    }
    else if (choice == "Groovy") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Groovy Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Groovy() << std::endl;
    }
    else if (choice == "Erlang") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Erlang Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Erlang() << std::endl;
    }
    else if (choice == "Clojure") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Clojure Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Clojure() << std::endl;
    }
    else if (choice == "Prolog") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Prolog Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Prolog() << std::endl;
    }
    else if (choice == "AWK") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "AWK Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.AWK() << std::endl;
    }
    else if (choice == "TCL") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "TCL Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.TCL() << std::endl;
    }
    else if (choice == "Julia") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Julia Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Julia() << std::endl;
    }
    else if (choice == "PowerShell") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "PowerShell Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.PowerShell() << std::endl;
    }
    else if (choice == "Racket") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Racket Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Racket() << std::endl;
    }
    else if (choice == "Smalltalk") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Smalltalk Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << d_t.Smalltalk() << std::endl;
    }
    else {
        other_languages o_t;
        other_langs(o_t, choice);
    }
}

static void static_langs(static_languages& s_t, std::string& choice) {
    if (choice == "C") {
    std::cout << "-----------------------" << std::endl;
    std::cout << "C Code!" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::string code = s_t.C();
    std::cout << code << std::endl;
    }
    // -- End of C
    else if (choice == "CPP") {
        std::cout << "-------------------------" << std::endl;
        std::cout << "CPP Code" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << s_t.CPP();
    }
    //-- End of CPP
    else if (choice == "Java") {
        std::cout << "-------------------------" << std::endl;
        std::cout << "Java Code" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << s_t.Java() << std::endl;
    }
    //-- End of Java
    else if (choice == "Go") {
        std::cout << "-------------------------" << std::endl;
        std::cout << "Go Code" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << s_t.Go() << std::endl;
    }
    //-- End of Go
    else if (choice == "Kotlin") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Kotlin Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Kotlin() << std::endl;
    }
    //-- End of Kotlin
    else if (choice == "Swift") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Swift Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Swift() << std::endl;
    }
    //-- End of Swift
    else if (choice == "Rust") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Rust Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Rust() << std::endl;
    }
    else if (choice == "Haskell") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Haskell Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Haskell() << std::endl;
    }
    else if (choice == "CSharp") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "CSharp Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.CSharp() << std::endl;
    }
    else if (choice == "FSharp") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "FSharp Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.FSharp() << std::endl;
    }
    else if (choice == "ObjectiveC") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "ObjectiveC Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.ObjectiveC() << std::endl;
    }
    else if (choice == "VHDLVerilog") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "VHDLVerilog Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout <<  s_t.VHDLVerilog() << std::endl;
    }
    else if (choice == "Fortran") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Fortran Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Fortran() << std::endl;
    }
    else if (choice == "COBOL") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "COBOL Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.COBOL() << std::endl;
    }
    else if (choice == "Pascal") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Pascal Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Pascal() << std::endl;
    }
    else if (choice == "Ada") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Ada Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Ada() << std::endl;
    }
    else if (choice == "Scala") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Scala Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Scala() << std::endl;
    }
    else if (choice == "TypeScript") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "TypeScript Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.TypeScript() << std::endl;
    }
    else if (choice == "Dart") {
        std::cout << "-----------------------" << std::endl;
        std::cout << "Dart Code!" << std::endl;
        std::cout << "-----------------------" << std::endl;
        std::cout << s_t.Dart() << std::endl;
    }
    else {
        dynamic_languages d_t;
        dynamic_langs(d_t, choice);
    }
}

int main(int argc, char** argv) {
    /*Table table = initTable();
    std::cout << "Type help for more details!" << std::endl;
    for (;;) { 
        std::cout << "> ";
        std::string line;
        std::getline(std::cin, line); // get user input
        if (line == "help") {
            // list out the commands
            std::cout << "list"  << std::endl;
            std::cout << "quit" << std::endl;
            std::cout << "print" << std::endl;
            std::cout << "generate" << std::endl;
         }
         else if (line == "list") {
             for (auto &it: table) {
                 std::cout << it->first << std::endl;
             }

         }
         else if (line == "quit") {exit(0);}
         // use regex for pattern matching. So match one part of the stirng literal to see if it is print and the other to see if substring is a key in the map
         else if (line == "print") {
         
         }
    }*/
    static_languages s_t;
    if (argc > 1) {
        std::string to_print = argv[1];
        static_langs(s_t, to_print);
    }
    else {
        /*for (auto &it: Table) {
            std::cout << it->first << std::endl;
        }*/
        std::cerr << "Usage: [Name of language to print]";
        exit(1);
    }
    return 0;
}
