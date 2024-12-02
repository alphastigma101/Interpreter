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


TEST_F(InterpreterTest, Adding) {
    Scanner scanner("(34.000000 + 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(0), "49.000000");
    cTree.clear();
}


TEST_F(InterpreterTest, Substract) {
    Scanner scanner("(34.000000 - 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(1), "19.000000");
    cTree.clear();
}

TEST_F(InterpreterTest, Multiplication) {
    Scanner scanner("(34.000000 * 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(2), "510.000000");
    cTree.clear();
}

TEST_F(InterpreterTest, ComplexAddAndDivide) {
    Scanner scanner("((34.000000 + 15.000000) / 3.000000));");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(4), "16.333333");
    cTree.clear();   
}
TEST_F(InterpreterTest, AddDivideMultiple) {
    Scanner scanner("((34.000000 + 15.000000) / (12.000000 * 6.000000));");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(7), "0.680556");
    cTree.clear();   
}

TEST_F(InterpreterTest, Complex) {
    Scanner scanner("(((34.000000 + 15.000000) * 2.000000) - (12.000000 / (3.000000 + 1.000000))) + ((45.000000 * 2.000000) / 3.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(15), "125.000000");
    cTree.clear();   
}

TEST_F(InterpreterTest, Integers) {
    Scanner scanner("(((34 + 15) * -2) - (-12 / (3 + 1))) + ((45 * 2) / 3);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(evaluatedExpressions.size() - 1), "-65");
    cTree.clear();   
}
TEST_F(InterpreterTest, Comparison) {
    Scanner scanner("(34 > 15);");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    auto res = p.parse();
    interpreter interp(res);
    EXPECT_EQ(evaluatedExpressions.at(evaluatedExpressions.size() - 1), "1");
    cTree.clear();   
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
