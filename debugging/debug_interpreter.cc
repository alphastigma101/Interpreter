#include <scanner.h>
#include <parser.h>
#include <interpreter.h>
#include <resolver.h>
#include <cassert>
Vector<String> types = {
    "bool y = false;",
    "double a = 90.0000;",
    "int b = 2;",
    "string c = \"hello\";",
    "string d = 'bye!';",
    //"void &c = &funky;",
};
Vector<String> expressions = {
    /*"(1 == 1)",
    "2 != 3",
    "true == true",
    "false != true",
    "null == null",
    "5 % 0",*/
    //"'hello' == 'hello'",
    /*"('world' != 'World')",
    //"1 == 2 == false",
    //"1 != 2 != false",
    "(1 == 1) == true",
    "(1 != 1) == false",
    "true == !false",
    "null != undefined",
    "0 == false",
    "1 == true",
    "'' == false",
    "'0' != 0",
    "[] == []",
    "{} != {}", 
    "(Infinity == Infinity)",
    "NaN != NaN",
    "(1 < 2) == (3 > 2)",
    "(1 <= 1) != (2 >= 3)"*/
};
Vector<String> Exceptions = {
    "var x = 1;"
    //"double z = 90.0000",
    //"print one",
    //"print one;"
    //"foo.bar(1,2,3,4)",
    // "bar(int x, double y, string z)",
};
Vector<String> functions = {
    "radiate one;",
    //"foo.bar(1,2,3,4);",
    // "bar(int x, double y, string z);",
};
const std::string program = 
    "string a = \"global a\";\n"
    "string b = \"global b\";\n"
    "string c = \"global c\";\n"
    "{\n"
    "  string a = \"outer a\";\n"
    "  string b = \"outer b\";\n"
    "  {\n"
    "    string a = \"inner a\";\n"
    "    radiate a;\n"
    "    radiate b;\n"
    "    radiate c;\n"
    "  }\n"
    "  radiate a;\n"
    "  radiate b;\n"
    "  radiate c;\n"
    "}\n"
    "radiate a;\n"
    "radiate b;\n"
    "radiate c;\n";
Vector<String> blocks = {
    //program
    "string a = \"global a\";\n"
};
    //std::cout << "Debugging supported types:" << std::endl;
    //for (const auto& testCase : types) runTest(testCase); // debug the supported types
    //for (const auto& testCase : Exceptions) runTest(testCase); // debug the exceptions
    //for (const auto& testCase : functions) runTest(testCase);
    //for (const auto& testCase : blocks) runTest(testCase); 

static void Adding() {
    Scanner scanner("int x = (((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("x"); it != env.end())
        conv = std::any_cast<String>(it->second);
    assert(conv == "-65");
    std::cout << conv << std::endl;
}

int main(int argc, char **argv) {
    //Scanner scanner("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);"); // how would it handle this?
    //Scanner scanner("string bar(string a) { return a; } bar('hello!'); int foo(int b) {return b;} foo(100);");
    /*Scanner scanner("int a = 4;\n"
        "string b = 'hello';\n""\
        {\n"
            "a = a + 5;\n"
            "b = \"inner b\";\n"
        "}\n"
            "radiate a;"
    );*/
    Scanner scanner(R"(
        containment Bacon {
            string choice = "";
            string eat() {
                if (choice != "Crunch crunch crunch!") {
                    radiate choice;
                }
                else {
                    radiate "Crunch crunch crunch!";
                }
            }
        }
        Bacon().choice = "Not crunch crunch crunch!";
        Bacon().eat(); // Prints out "Not crunch crunch crunch!".)");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("i"); it != env.end())
        conv = std::any_cast<String>(it->second);
    std::cout << conv << std::endl;
    
    //Adding();
    
    return 0;
}
