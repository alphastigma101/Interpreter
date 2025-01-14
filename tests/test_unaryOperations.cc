#include <gtest/gtest.h>
#include <scanner.h>
#include <parser.h>
#include <language_specific_truthy_operations.h>
class UnaryOperationsTest : public ::testing::Test {
    protected:
        void SetUp() override {
            // Setup code if needed
        }   
};
TEST_F(UnaryOperationsTest, IDs) {
    Scanner scanner("int d = (34.000000 + 15.000000);");
    Vector<Token> tokens = scanner.ScanTokens();
    Parser::parser p(tokens);
    auto res = p.parse();
    String conv;
    //if (auto it = env.find("d"); it != env.end())
        //conv = std::any_cast<String>(it->second);
    //EXPECT_EQ(conv, "49.000000");
    
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}