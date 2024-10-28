#include <gtest/gtest.h>
#include <language_specific_truthy_operations.h>

class TruthyOperationsTest : public ::testing::Test {
    protected:
        truthyOperations to;
};

TEST_F(TruthyOperationsTest, Truthiness) {
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
