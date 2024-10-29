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

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
