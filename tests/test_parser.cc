#include <gtest/gtest.h>
#include <parser.h>
#include <scanner.h>
// TODO optional: Use google test's input parameter generator to test input values
class ParserTest : public testing::Test {
    protected:
        void SetUp() override {
            // Set up any necessary test environment
        }

        void TearDown() override {
            // Clean up after each test
        }

        // Helper function to create a parser with tokens
        parser createParser(std::vector<Token>& tokens) { return parser(tokens);}
};
//--Equality Testing--
TEST_F(ParserTest, EqualityTest_0) {
    Scanner scanner("1 == 1");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest,EqualityTest_1) {
    Scanner scanner("2 != 3");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_2) {
    Scanner scanner("true == true");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_3) {
    Scanner scanner("false != true");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_4) {
    Scanner scanner("'hello' == 'hello'");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_5) {
    Scanner scanner("'world' != 'World'");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_6) {
    Scanner scanner("42 == 42.0");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_7) {
    Scanner scanner("3.14 != 3.14159");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_8) {
    Scanner scanner("1 == 2 == false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_9) {
    Scanner scanner("1 != 2 != false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_10) {
   Scanner scanner("(1 != 1) == false");
   std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_11) {
    Scanner scanner("true == !false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest,EqualityTest_12) {
    Scanner scanner("0 == false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest,EqualityTest_13) {
    Scanner scanner("1 == true");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));

}
TEST_F(ParserTest,EqualityTest_14) {
   Scanner scanner("'' == false");
   std::vector<Token> tokens = scanner.ScanTokens();
   parser p = createParser(tokens);
   auto result = p.equality();
   ASSERT_NE(result, nullptr);
   EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_15) {
    Scanner scanner("'0' != 0");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
/*TEST_F(ParserTest, EqualityTest_8) {
    Scanner scanner("null != undefined");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_9) {
    Scanner scanner("[] == []");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_10) {
    Scanner scanner("{} != {}");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, EqualityTest_11) {
    Scanner scanner("Infinity == Infinity");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_12) {
    Scanner scanner("NaN != NaN");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_13) {
    Scanner scanner("(1 < 2) == (3 > 2)");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, EqualityTest_14) {
    Scanner scanner("(1 <= 1) != (2 >= 3)");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.equality();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}*/
//--Comparison Testing----
TEST_F(ParserTest, ComparisonTest_0) {
    Scanner scanner("1 < 2");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_1) {
    Scanner scanner("3 > 4");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, fComparisonTest_2) {
    Scanner scanner("5 <= 6");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_3) {
    Scanner scanner("7 >= 8");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_4) {
    Scanner scanner("13 < 14 < 15");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_5) {
    Scanner scanner("16 > 17 > 18");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_6) {
    Scanner scanner("19 <= 20 <= 21");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_7) {
    Scanner scanner("22 >= 23 >= 24");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_8) {
    Scanner scanner("31 < 32 > 33 <= 34 >= 35 <= 36 => 37");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_9) {
    Scanner scanner("true < false");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
//TODO: Debug this later on after getting the other test suites to work
/*TEST_F(ParserTest, ComparisonTest_10) {
    std::string temp = "apple"; 
    temp += ">";
    temp += "banana";
    Scanner scanner(temp);
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}*/
TEST_F(ParserTest, ComparisonTest_11) {
    Scanner scanner("null <= 42");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, ComparisonTest_12) {
    Scanner scanner("3.14 >= 2.71");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.comparison();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
//--Term Testing---
TEST_F(ParserTest, TermTest_0) {
    Scanner scanner("10 - 2");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, TermTest_3) {
    Scanner scanner("2 - 3 + 4");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, TermTest_4) {
    Scanner scanner("5 + 6 - 7");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, TermTest_5) {
    Scanner scanner("-3 - 4");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, TermTest_6) {
    Scanner scanner("1 + 0");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}
TEST_F(ParserTest, TermTest_8) {
    Scanner scanner("3.14 + 2.5");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// --- Factor Testing ----
TEST_F(ParserTest, FactorTest_0) {
    Scanner scanner("(3 * 4) / 6");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.factor();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, FactorTest_1) {
    Scanner scanner("7 % 3");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.factor();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

TEST_F(ParserTest, TermTest_2) {
    Scanner scanner("5 % 0");
    std::vector<Token> tokens = scanner.ScanTokens();
    parser p = createParser(tokens);
    auto result = p.term();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test unary method
TEST_F(ParserTest, UnaryTest) {
    std::vector<Token> tokens = {
        Token(TokenType::MINUS, "-", "", 1),
        Token(TokenType::NUMBER, "5", "5.0", 1)
    };
    parser p = createParser(tokens);
    auto result = p.unary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Unary>(*result));
}

// Test primary method with different token types
TEST_F(ParserTest, PrimaryTestNumber) {
    std::vector<Token> tokens = {Token(TokenType::NUMBER, "42", "42.0", 1)};
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestString) {
    std::vector<Token> tokens = {
        Token(TokenType::STRING, "hello", "hello", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", 1)
    };
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestTrue) {
    std::vector<Token> tokens = {
        Token(TokenType::TRUE, "true", "true", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", 1)
    };
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestFalse) {
    std::vector<Token> tokens = {
        Token(TokenType::FALSE, "false", "false", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", 1)
    };
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestNil) {
    std::vector<Token> tokens = {
        Token(TokenType::NIL, "nil", "", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", 1)
    };
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Literal>(*result));
}

TEST_F(ParserTest, PrimaryTestGrouping) {
    std::vector<Token> tokens = {
        Token(TokenType::LEFT_PAREN, "(", "", 1),
        Token(TokenType::NUMBER, "42", "42.0", 1),
        Token(TokenType::RIGHT_PAREN, ")", "", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", 1)
    };
    parser p = createParser(tokens);
    auto result = p.primary();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Grouping>(*result));
}

// Test expression method
TEST_F(ParserTest, ExpressionTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", "1.0", 1),
        Token(TokenType::PLUS, "+", "", 1),
        Token(TokenType::NUMBER, "2", "2.0", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", 1)
    };
    parser p = createParser(tokens);
    auto result = p.expression();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test parse method
TEST_F(ParserTest, ParseTest) {
    std::vector<Token> tokens = {
        Token(TokenType::NUMBER, "1", "1.0", 1),
        Token(TokenType::PLUS, "+", "", 1),
        Token(TokenType::NUMBER, "2", "2.0", 1),
        Token(TokenType::END_OF_FILE, "EOF", "EOF", 1)
    };
    parser p = createParser(tokens);
    auto result = p.parse();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(std::holds_alternative<Binary>(*result));
}

// Test error handling
/*TEST_F(ParserTest, ParseErrorTest) {
    std::vector<Token> tokens = {
        Token(TokenType::LEFT_PAREN, "(", "", 1),
        Token(TokenType::NUMBER, "42", "42.0", 1)
        // Missing RIGHT_PAREN
    };
    parser p = createParser(tokens);
    auto result = p.parse();
    EXPECT_EQ(result, nullptr);
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
