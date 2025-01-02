#include <gtest/gtest.h>
#include <scanner.h>
#include <parser.h>

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
    EXPECT_EQ("[line 1] Error at end: Expect ';' after variable declaration. Got '90.0000' instead.", p.getMessage());
}
TEST_F(ParserTest, ParserTest_ClosePara_Test) {
    Scanner scan("(");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at end: Expect expression. Got '(' instead.", p.getMessage());
}
TEST_F(ParserTest, ParserTest_CloseParaAroundLiteral_Test) {
    Scanner scan("(56;");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at ';': Expect ')' after expression. Got ';' instead.", p.getMessage());
}
TEST_F(ParserTest, ParserTest_ExtraPara_Test) {
    Scanner scan("double z = ((34.000000 + 15.000000) / 3.000000))");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at ')': Expect ';' after variable declaration. Got ')' instead.", p.getMessage());
}

TEST_F(ParserTest, ParserTest_Semicolon_Test) {
    Scanner scan(";");
    Vector<Token> tokens = scan.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    EXPECT_EQ("[line 1] Error at ';': Expect expression. Got ';' instead.", p.getMessage());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
