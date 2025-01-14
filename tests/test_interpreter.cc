#include <gtest/gtest.h>
#include <scanner.h>
#include <parser.h>
#include <interpreter.h>
#include <resolver.h> 
class InterpreterTest : public ::testing::Test {
    protected:
        void SetUp() override {
            // Setup code if needed
        }   
};
TEST_F(InterpreterTest, Adding) {
    Scanner scanner("int d = (34.000000 + 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("d"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "49.000000");
    
}

TEST_F(InterpreterTest, Substract) {
    Scanner scanner("int b = (34.000000 - 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("b"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "19.000000");
    
}

TEST_F(InterpreterTest, Multiplication) {
    Scanner scanner("int c = (34.000000 * 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("c"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "510.000000");
}

TEST_F(InterpreterTest, ComplexAddAndDivide) {
    Scanner scanner("double z = ((34.000000 + 15.000000) / 3.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("z"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "16.333333");
    
}
TEST_F(InterpreterTest, AddDivideMultiple) {
    Scanner scanner("int a = ((34.000000 + 15.000000) / (12.000000 * 6.000000));");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("a"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "0.680556");
   
}

TEST_F(InterpreterTest, Complex) {
    Scanner scanner("int y = (((34.000000 + 15.000000) * 2.000000) - (12.000000 / (3.000000 + 1.000000))) + ((45.000000 * 2.000000) / 3.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("y"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "125.000000");
     
}

TEST_F(InterpreterTest, Integers) {
    Scanner scanner("int x = (((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("x"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "-65");
     
}
TEST_F(InterpreterTest, Comparison) {
    Scanner scanner("int w = (34 > 15);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("w"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "1");
}

TEST_F(InterpreterTest, BlockScope) {
    Scanner scanner(
        "{\n"
            "string a = \"outer a\";\n"
            "string b = \"outer b\";\n"
        "}"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("a"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"outer a\"");
    if (auto it = env.find("b"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"outer b\"");
} 
TEST_F(InterpreterTest, InterpreterTest_BlockScopePrint) {
    Scanner scanner(
        "string a = \"outer a\";\n"
        "string b = \"outer b\";\n""\
        {\n"
            "string a = \"inner a\";\n"
            "string b = \"inner b\";\n"
        "}\n"
            "radiate a;"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"inner a\"");
    if (auto it = env.find("b"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"inner b\"");
}
TEST_F(InterpreterTest, InterpreterTest_Initializers) {
    Scanner scanner(
        "string a;\n"
        "string b;\n""\
        {\n"
            "a = \"inner a\";\n"
            "b = \"inner b\";\n"
        "}\n"
            "radiate a;"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"inner a\"");
    if (auto it = env.find("b"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"inner b\"");
}
TEST_F(InterpreterTest, InterpreterTest_ShadowedVariableArithmetic) {
    Scanner scanner(
        "int a = 4;\n"
        "string b;\n""\
        {\n"
            "a = a + 5;\n"
            "b = \"inner b\";\n"
        "}\n"
            "radiate a;"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "9");
    if (auto it = env.find("b"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"inner b\"");
}
/*TEST_F(InterpreterTest, NoVariable) {
    Scanner scanner("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "-65");
}*/
TEST_F(InterpreterTest, PrintStmt) {
    Scanner scanner("radiate 24;");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "24");
}
TEST_F(InterpreterTest, LogicalOr) {
    // Single String
    Scanner scanner("radiate 'hi' or 2;");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "'hi'");
}
TEST_F(InterpreterTest, LogicalAnd) {
    // Single String
    Scanner scanner("radiate 'hi' and 2;");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "2");
}
TEST_F(InterpreterTest, IfStatement) {
    Scanner scanner("if (10 > 1) radiate 'hi';");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "'hi'");
}
TEST_F(InterpreterTest, ElseStatement) {
    Scanner scanner("if (false) radiate 'hi'; if (false) radiate 0; if (false) radiate 1; else radiate 'bye';");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "'bye'");
}
TEST_F(InterpreterTest, ForLoop) {
    Scanner scanner("for (int i = 0; i < 10; i = i + 1) { radiate i; }");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("i"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "10");
}
TEST_F(InterpreterTest, WhileLoop) {
    Scanner scanner("{ int i = 0;  while (i < 10) { radiate i; i = i + 1; }}");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("i"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "10");
}
TEST_F(InterpreterTest, InterpreterTest_FunctionInt) {
    // TODO: Make a recrusion test case
    Scanner scanner("int foo(int a, int b, int c) { return a + b + c; } foo(10, 20, 30);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    try {
        Interpreter::interpreter interp(res);
    }
    catch(NuclearLang::NukeReturn& e) {
        EXPECT_EQ(e.value, "60");
    }
}
TEST_F(InterpreterTest, InterpreterTest_FunctionString) {
    Scanner scanner("string bar(string a) { return a; } bar('hello!');");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    try {
        Interpreter::interpreter interp(res);
    }
    catch(NuclearLang::NukeReturn& e) {
        EXPECT_EQ(e.value, "'hello!'");
    }
    
}
TEST_F(InterpreterTest, InterpreterTest_FunctionMultiple) {
    Scanner scanner("string bar(string a) { return a; } bar('hello!'); int foo(int a) {return a;} foo(100);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    try {
        Interpreter::interpreter interp(res);
    }
    catch(NuclearLang::NukeReturn& e) {
        EXPECT_EQ(e.value, "'hello!'");
    }
    
}
TEST_F(InterpreterTest, InterpreterTest_ClassInstances) {
    Scanner scanner(R"(
        containment Bagel {}
        Bagel bagel = Bagel();
        radiate bagel; // Prints "Bagel instance".)"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("bagel"); it != env.end()) {
        auto nuclearInstance = std::any_cast<NuclearLang::NukeInstance*>(it->second);
        auto res = *(String*)nuclearInstance->getKlass()->name;
        conv = res;
    }
    EXPECT_EQ(conv, "Bagel");
}
TEST_F(InterpreterTest, InterpreterTest_ClassFields) {
    Scanner scanner(R"(
        containment Bacon {
            string choice;
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
        Bacon().eat(); // Prints out "Not crunch crunch crunch!".)"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"Not crunch crunch crunch!\"");
}
TEST_F(InterpreterTest, InterpreterTest_ClassGetAndSet) {
    Scanner scanner(R"(
        containment Bacon {
            string choice;
            string eat() {
                if (choice != "Crunch crunch crunch!") {
                    radiate choice;
                }
                else {
                    radiate "Not crunch crunch crunch!";
                }
            }
        }
        Bacon().choice = "Crunch crunch crunch!";
        Bacon().eat(); // Prints out "Not crunch crunch crunch!".)"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"Not crunch crunch crunch!\"");
}

TEST_F(InterpreterTest, InterpreterTest_ClassMultipleFieldProperties) {
    Scanner scanner(R"(
        containment Bot {
            string a;
            string b;
            string talk() {
                if (a) {
                    radiate "Hello!";
                }
                else {
                    radiate "Set the property a to talk to me!";
                }
            }
            string weather() {
                if (b) {
                    radiate "The weather could be nice outside today. If it is not, you should wear a jacket!";
                }
                else {
                    radiate "Set the property b to get advice about handling cold/hot weather in your area!";
                }
            }
            string c;
            string d;
            string bye() {
                if (c) {
                    radiate "Have a good day!";
                }
                else {
                    radiate "Set the property c for me to say goodbye";
                }
            }
            string add() {
                if (d) {
                    radiate 2 + 2 + 4;
                }
                else {
                    radiate "Set the property d to see me do some simple math";
                }
            }
        }
        Bot().a = "Hello bot";
        Bot().b = "It is cold where I live at";
        Bot().c = "Goodbye Bot!";
        Bot().d = "Do some simple math";
        Bot().talk();
        Bot().weather();
        Bot().bye();
        Bot().add();
        )"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    //Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::Interpreter::interpreter());
    //resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
     EXPECT_EQ(conv, "8");
    
}
TEST_F(InterpreterTest, InterpreterTest_ClassCallBackMethod) {
    Scanner scanner(R"(
        containment Thing {
            Thing getCallback() {
                Thing localFunction() {
                    radiate this;
                }
                return localFunction;
            }
        }
        Thing callback = Thing().getCallback();
        callback();
        )"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    try {
        Interpreter::interpreter interp(res);
    }
    catch(NuclearLang::NukeReturn& e) {
        NuclearLang::NukeFunction* conv = reinterpret_cast<NuclearLang::NukeFunction*>(e.value);
        EXPECT_TRUE(conv != nullptr);
        EXPECT_EQ(typeid(conv), typeid(NuclearLang::NukeFunction*));
    }
    
}
TEST_F(InterpreterTest, InterpreterTest_ClassThis) {
    Scanner scanner(R"(
        containment Cake {
            string taste() {
                string adjective = "delicious";
                radiate "The " + this.flavor + " cake is " + adjective + "!";
            }
        }
        Cake cake = Cake();
        cake.flavor = "German chocolate";
        cake.taste(); // Prints "The German chocolate cake is delicious!".
        )"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
     EXPECT_EQ(conv, "\"The \"\"German chocolate\"\" cake is \"\"delicious\"\"!\"");
    
}
TEST_F(InterpreterTest, InterpreterTest_ClassConstructor) {
    Scanner scanner(R"(
        containment Foo {
            Foo init() {
                radiate this; // this used to be a identifier, but now it is not. So there's a bug
            }
        }
        Foo foo = Foo();
        radiate foo.init();
        )"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    NuclearLang::NukeInstance* conv;
    try {
        if (auto it = env.find("radiate"); it != env.end())
            conv = std::any_cast<NuclearLang::NukeInstance*>(it->second);
    }
    catch(...) {}
    EXPECT_TRUE(conv != nullptr);
    EXPECT_EQ(typeid(conv), typeid(NuclearLang::NukeInstance*));
    
}
TEST_F(InterpreterTest, InterpreterTest_ClassMethod) {
    Scanner scanner(R"(
        containment Bacon {
            string eat() {
                radiate "Crunch crunch crunch!";
            }
        }
        Bacon().eat(); // Prints "Crunch crunch crunch!".)"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("Bacon"); it != env.end()) {
        auto nuclear = std::any_cast<NuclearLang::NukeClass*>(it->second);
        auto res = *(String*)nuclear->name;
        auto map = *(Map<String, NuclearLang::NukeFunction>*)nuclear->methods;
        if (auto search = map.find("eat"); search != map.end()) {
          conv = reinterpret_cast<ContextFreeGrammar::Functions*>(search->second.declaration)->statements.at(0)->initializer->op.getLexeme();  
        }
    }
    EXPECT_EQ(conv, "\"Crunch crunch crunch!\"");
}

TEST_F(InterpreterTest, InterpreterTest_MultipleClassMethods) {
   Scanner scanner(R"(
        containment Bacon {
            string eat() {
                radiate "Crunch crunch crunch!";
            }
            string sleep() {
                radiate "Sleep sleep sleep!";
            }
        }
        Bacon().eat(); // Prints "Crunch crunch crunch!".
        Bacon().sleep(); // Prints "Sleep sleep sleep!"
        )"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"Sleep sleep sleep!\"");
}
TEST_F(InterpreterTest, InterpreterTest_SuperClassesAndSubclasses) {
   Scanner scanner(R"(
        containment Doughnut {
            string cook() {
                radiate "Fry until golden brown.";
            }
        }
        containment BostonCream < Doughnut {}
        BostonCream().cook();
        )"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"Fry until golden brown.\"");
}
TEST_F(InterpreterTest, InterpreterTest_Super) {
   Scanner scanner(R"(
        containment A {
            string method() {
                radiate "A method";
            }
        }
        containment B < A {
            string method() {
                radiate "B method";
            }
            B test() {
                super.method();
            }
        }
        containment C < B {}
        C().test();
        )"
    );
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    Resolver::resolver* resolver = new Resolver::resolver(new Interpreter::interpreter());
    resolver->resolve(res);
    Interpreter::interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"Sleep sleep sleep!\"");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
