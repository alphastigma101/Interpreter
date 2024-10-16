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
    Scanner scanner("(34 + 15)");
    //Scanner scanner("((34 + 15) / 3))");
    //Scanner scanner("(((34 + 15) * 2) - (12 / (3 + 1))) + ((45 * 2) / 3)");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.beginParse();
    interpreter interp(cTree);
    EXPECT_EQ(evaluatedExpressions.at(0), "49");
    cTree.clear();
}


TEST_F(InterpreterTest, Substract) {
    Scanner scanner("(34 - 15)");
    //Scanner scanner("((34 + 15) / 3))");
    //Scanner scanner("(((34 + 15) * 2) - (12 / (3 + 1))) + ((45 * 2) / 3)");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.beginParse();
    interpreter interp(cTree);
    EXPECT_EQ(evaluatedExpressions.at(1), "19");
    cTree.clear();
}

TEST_F(InterpreterTest, Multiplication) {
    Scanner scanner("(34 * 15)");
    //Scanner scanner("((34 + 15) / 3))");
    //Scanner scanner("(((34 + 15) * 2) - (12 / (3 + 1))) + ((45 * 2) / 3)");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.beginParse();
    interpreter interp(cTree);
    EXPECT_EQ(evaluatedExpressions.at(2), "510");
    cTree.clear();
}

/*TEST_F(Interpreter, ComplexAddAndDivide) {
    Scanner scanner("((34 + 15) / 3))");
    Vector<Token> tokens = scanner.ScanTokens();
    parser p(tokens);
    p.beginParse();
    interpreter interp(cTree);
    EXPECT_EQ(evaluatedExpressions.at(0), "49");
    cTree.clear();   
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
