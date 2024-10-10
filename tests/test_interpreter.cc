#include <gtest/gtest.h>
#include "interpreter.h"

class InterpreterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    // Helper function to create a binary expression
    std::tuple<int, std::pair<std::string, std::any>> createBinaryExpr(const std::string& op, std::any left, std::any right) {
        return std::make_tuple(0, std::make_pair("Binary", std::make_any<BinaryExpr>(op, left, right)));
    }
};

TEST_F(InterpreterTest, ConstructorWithEmptyExpressions) {
    std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::Python));
}

TEST_F(InterpreterTest, ConstructorWithBinaryExpression) {
    std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
    expr.push_back(createBinaryExpr("+", 1, 2));
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::Python));
}

TEST_F(InterpreterTest, ConstructorWithMultipleBinaryExpressions) {
    std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
    expr.push_back(createBinaryExpr("+", 1, 2));
    expr.push_back(createBinaryExpr("*", 3, 4));
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::Python));
}

TEST_F(InterpreterTest, ConstructorWithNonBinaryExpression) {
    std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
    expr.push_back(std::make_tuple(0, std::make_pair("Literal", 5)));
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::Python));
}

TEST_F(InterpreterTest, ConstructorWithMixedExpressions) {
    std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
    expr.push_back(createBinaryExpr("+", 1, 2));
    expr.push_back(std::make_tuple(0, std::make_pair("Literal", 5)));
    expr.push_back(createBinaryExpr("*", 3, 4));
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::Python));
}

TEST_F(InterpreterTest, ConstructorWithDifferentLanguages) {
    std::vector<std::tuple<int, std::pair<std::string, std::any>>> expr;
    expr.push_back(createBinaryExpr("+", 1, 2));

    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::Python));
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::JavaScript));
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::Ruby));
    EXPECT_NO_THROW(interpreter(expr, LanguageTokenTypes::CPP));
}

// Additional tests can be added here for other methods once they are implemented

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
