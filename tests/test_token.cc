#include <gtest/gtest.h>
#include "token.h" 
class TokenTest : public testing::Test {};

// Test the default constructor
TEST_F(TokenTest, DefaultConstructor) {
    try {
        Token token(TokenType::STRING, "", "", 0);
        EXPECT_EQ(token.getLexeme(), "") << "Expected empty string, got: " + token.getLexeme();
        EXPECT_EQ(token.getLiteral(), "") << "Expected string literal empty, got: " + token.getLiteral();
        EXPECT_EQ(token.getLine(), 0);
    } catch (const std::bad_alloc& e) {
        FAIL() << "Memory allocation failed: " << e.what();
    } catch (const std::exception& e) {
        FAIL() << "Exception occurred: " << e.what();
    }
}


// Test toString method
TEST_F(TokenTest, ToString) {
    Token token(TokenType::EQUAL, "=", "=", 1);
    std::any result = token.toString();
    ASSERT_TRUE(result.type() == typeid(std::string));
    std::string str_result = std::any_cast<std::string>(result);
    EXPECT_TRUE(str_result.find("EQUAL") != std::string::npos);
    EXPECT_TRUE(str_result.find("=") != std::string::npos);
}

// Driver Code
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
