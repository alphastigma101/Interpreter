#include <gtest/gtest.h>
#include <scanner.h>
#include <parser.h>
#include <environment.h>

class EnvironmentTest : public ::testing::Test {
    protected:
        void SetUp() override {
            // Setup code if needed
        }   
};


TEST_F(EnvironmentTest, Adding) {

}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
