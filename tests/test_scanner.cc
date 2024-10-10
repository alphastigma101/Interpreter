#include <scanner.h>
#include <gtest/gtest.h>

class ScannerTest : public testing::Test {
    protected:
        //ScannerTest st(std::string source): Scanner(source) {};

        /*------------------------------------------------------------------------
         * @brief SetUp allows you to test individual test cases instead of testing them all 
         * @param None
         * @return void
         * -----------------------------------------------------------------------
         */
        void SetUp() override {
            // Setup code if needed
        }

        void TearDown() override {
            // Teardown code if needed
        }
};

// Test the constructor
TEST_F(ScannerTest, ConstructorTest) {
    std::string source_ = "var x = 5;";
    Scanner scanner(source_);
    EXPECT_EQ(scanner.getSource(), source_);
}

// Test scanning of single-character tokens
TEST_F(ScannerTest, SingleCharacterTokens) {
    std::string source_ = "(){},.-+;*";
    Scanner scanner(source_);
    std::vector<Token> tokens = scanner.ScanTokens();
        
    ASSERT_EQ(tokens.size(), 11);
    EXPECT_EQ(tokens[0].getTypeStr(), "LEFT_PAREN");
    EXPECT_EQ(tokens[1].getTypeStr(), "RIGHT_PAREN");
    EXPECT_EQ(tokens[2].getTypeStr(), "LEFT_BRACE");
    EXPECT_EQ(tokens[3].getTypeStr(), "RIGHT_BRACE");
    EXPECT_EQ(tokens[4].getTypeStr(), "COMMA");
    EXPECT_EQ(tokens[5].getTypeStr(), "DOT");
    EXPECT_EQ(tokens[6].getTypeStr(), "MINUS");
    EXPECT_EQ(tokens[7].getTypeStr(), "PLUS");
    EXPECT_EQ(tokens[8].getTypeStr(), "SEMICOLON");
    EXPECT_EQ(tokens[9].getTypeStr(), "STAR");
    EXPECT_EQ(tokens[10].getTypeStr(), "EOF");
    EXPECT_EQ(tokens[10].getType(), TokenType::END_OF_FILE);

}

// Test scanning of double-character tokens
/*TEST_F(ScannerTest, DoubleCharacterTokens) {
    std::string source = "!= == <= >=";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 5);
    EXPECT_EQ(tokens[0].getType(), TokenType::BANG_EQUAL);
    EXPECT_EQ(tokens[1].getType(), TokenType::EQUAL_EQUAL);
    EXPECT_EQ(tokens[2].getType(), TokenType::LESS_EQUAL);
    EXPECT_EQ(tokens[3].getType(), TokenType::GREATER_EQUAL);
}

// Test scanning of keywords
TEST_F(ScannerTest, Keywords) {
    std::string source_ = "and class else if while var";
    Scanner scanner(source_);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 7);
    EXPECT_EQ(tokens[0].getType(), TokenType::AND);
    EXPECT_EQ(tokens[1].getType(), TokenType::CLASS);
    EXPECT_EQ(tokens[2].getType(), TokenType::ELSE);
    EXPECT_EQ(tokens[3].getType(), TokenType::IF);
    EXPECT_EQ(tokens[4].getType(), TokenType::WHILE);
    EXPECT_EQ(tokens[5].getType(), TokenType::VAR);
}

// Test scanning of identifiers
TEST_F(ScannerTest, Identifiers) {
    std::string source = "variable_name anotherVar _underscoreVar";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 4);
    EXPECT_EQ(tokens[0].getType(), TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[1].getType(), TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].getType(), TokenType::IDENTIFIER);
}

// Test scanning of numbers
TEST_F(ScannerTest, Numbers) {
    std::string source = "123 45.67";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].getType(), TokenType::NUMBER);
    EXPECT_EQ(tokens[0].getLiteral(), "123");
    EXPECT_EQ(tokens[1].getType(), TokenType::NUMBER);
    EXPECT_EQ(tokens[1].getLiteral(), "45.67");
}

// Test scanning of strings
TEST_F(ScannerTest, Strings) {
    std::string source_ = "\"Hello, World!\" \"Another string\"";
    Scanner scanner(source_);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].getType(), TokenType::STRING);
    //ASSERT_EQ(tokens[0].getLexeme(), "Hello, World!") << "Execpted:" << std::endl << "Hello, World!" << std::endl << "Got:" << std::endl << tokens[0].getLexeme();
    EXPECT_EQ(tokens[1].getType(), TokenType::STRING);
    //ASSERT_EQ(tokens[1].getLexeme(), "Another string") << "Execpted:" << std::endl << "Another string" << std::endl << "Got:" << std::endl << tokens[1].getLexeme();
}

// Test scanning of comments
TEST_F(ScannerTest, Comments) {
    std::string source = "// This is a comment\nvar x = 5;";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 6);
    EXPECT_EQ(tokens[0].getType(), TokenType::VAR);
    EXPECT_EQ(tokens[1].getType(), TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[2].getType(), TokenType::EQUAL);
    EXPECT_EQ(tokens[3].getType(), TokenType::NUMBER);
}

// Test error handling (e.g., unterminated string)
TEST_F(ScannerTest, UnterminatedString) {
    std::string source_ = "\"This string never ends";
    Scanner scanner(source_);
    
    testing::internal::CaptureStdout();
    std::vector<Token> tokens = scanner.ScanTokens();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Unterminated string") != std::string::npos);
}

// Test a complex case combining multiple elements
TEST_F(ScannerTest, ComplexCase) {
    std::string source = "if (x == 10) { print \"Hello\"; } // End of line";
    Scanner scanner(source);
    std::vector<Token> tokens = scanner.ScanTokens();
    
    ASSERT_EQ(tokens.size(), 11);
    EXPECT_EQ(tokens[0].getType(), TokenType::IF);
    EXPECT_EQ(tokens[1].getType(), TokenType::LEFT_PAREN);
    EXPECT_EQ(tokens[2].getType(), TokenType::IDENTIFIER);
    EXPECT_EQ(tokens[3].getType(), TokenType::EQUAL_EQUAL);
    EXPECT_EQ(tokens[4].getType(), TokenType::NUMBER);
    EXPECT_EQ(tokens[5].getType(), TokenType::RIGHT_PAREN);
    EXPECT_EQ(tokens[6].getType(), TokenType::LEFT_BRACE);
    EXPECT_EQ(tokens[7].getType(), TokenType::PRINT);
    EXPECT_EQ(tokens[8].getType(), TokenType::STRING);
    EXPECT_EQ(tokens[9].getType(), TokenType::RIGHT_BRACE);
}*/

// Driver Code
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
