#include <gtest/gtest.h>
#include <scanner.h>
#include <parser.h>
#include <interpreter.h> 

class InterpreterTest : public ::testing::Test {
    protected:
        void SetUp() override {
            // Setup code if needed
        }   
};
/*TEST_F(InterpreterTest, Adding) {
    Scanner scanner("int d = (34.000000 + 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("d"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "49.000000");
    
}

TEST_F(InterpreterTest, Substract) {
    Scanner scanner("int b = (34.000000 - 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("b"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "19.000000");
    
}

TEST_F(InterpreterTest, Multiplication) {
    Scanner scanner("int c = (34.000000 * 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("c"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "510.000000");
}

TEST_F(InterpreterTest, ComplexAddAndDivide) {
    Scanner scanner("double z = ((34.000000 + 15.000000) / 3.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("z"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "16.333333");
    
}
TEST_F(InterpreterTest, AddDivideMultiple) {
    Scanner scanner("int a = ((34.000000 + 15.000000) / (12.000000 * 6.000000));");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("a"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "0.680556");
   
}

TEST_F(InterpreterTest, Complex) {
    Scanner scanner("int y = (((34.000000 + 15.000000) * 2.000000) - (12.000000 / (3.000000 + 1.000000))) + ((45.000000 * 2.000000) / 3.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("y"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "125.000000");
     
}

TEST_F(InterpreterTest, Integers) {
    Scanner scanner("int x = (((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("x"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "-65");
     
}
TEST_F(InterpreterTest, Comparison) {
    Scanner scanner("int w = (34 > 15);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
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
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("a"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"outer a\"");
    if (auto it = env.find("b"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "\"outer b\"");
}*/
/*TEST_F(InterpreterTest, NoVariable) {
    Scanner scanner("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "-65");
}*/
/*TEST_F(InterpreterTest, PrintStmt) {
    Scanner scanner("radiate 24;");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "24");
}*/
/*TEST_F(InterpreterTest, LogicalOr) {
    // Single String
    Scanner scanner("radiate 'hi' or 2;");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "'hi'");
}*/
TEST_F(InterpreterTest, IfStatement) {
    Scanner scanner("if (10 > 1) radiate 'hi';");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "'hi'");
}
TEST_F(InterpreterTest, ElseStatement) {
    Scanner scanner("if (10 < 1) radiate 'hi'; else radiate 'bye';");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("radiate"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "'bye'");
}
TEST_F(InterpreterTest, ForLoop) {
    Scanner scanner("for (int i = 0; i < 10; i = i + 1) radiate i;");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("i"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "10");
}

TEST_F(InterpreterTest, WhileLoop) {
    Scanner scanner("{ int i = 0;  while (i < 10) { radiate i; i = i + 1; }}");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    auto env = interp.getEnv()->getMap();
    String conv;
    if (auto it = env.find("i"); it != env.end())
        conv = std::any_cast<String>(it->second);
    EXPECT_EQ(conv, "10");
}

// TODO optional: Use google test's input parameter generator to test input values
class ParserTest : public testing::Test {
    protected:
        void SetUp() override {
            // Set up any necessary test environment
        }

        void TearDown() override {
            // Clean up after each test
        }
};
TEST_F(ParserTest,  ParserTest_MissingSemiColon) {
    Scanner scan("double z = 90.0000");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at end: Expect ';' after variable declaration. Got '90.0000' instead.", p.getText());
}
TEST_F(ParserTest, ParserTest_ClosePara_Test) {
    Scanner scan("(");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at end: Expect expression. Got '(' instead.", p.getText());
}
TEST_F(ParserTest, ParserTest_CloseParaAroundLiteral_Test) {
    Scanner scan("(56;");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at ';': Expect ')' after expression. Got ';' instead.", p.getText());
}
TEST_F(ParserTest, ParserTest_ExtraPara_Test) {
    Scanner scan("double z = ((34.000000 + 15.000000) / 3.000000))");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at ')': Expect ';' after variable declaration. Got ')' instead.", p.getText());
}

TEST_F(ParserTest, ParserTest_Semicolon_Test) {
    Scanner scan(";");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at ';': Expect expression. Got ';' instead.", p.getText());
}

// Test fixture for AbstractionTreeSyntax classes
class AbstractionTreeSyntaxTest : public testing::Test/*, public AbstractionTreeSyntax::ast*/ {
    public:
        AbstractionTreeSyntaxTest();
        ~AbstractionTreeSyntaxTest();
        static std::string demangle(const char* name);
};
AbstractionTreeSyntaxTest::AbstractionTreeSyntaxTest() {}
AbstractionTreeSyntaxTest::~AbstractionTreeSyntaxTest() {}
std::string AbstractionTreeSyntaxTest::demangle(const char* name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}

// Test construction of Binary node
TEST(CompressedAstTreeTest, ConstructBinaryNode) {
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
