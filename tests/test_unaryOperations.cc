#include <gtest/gtest.h>
#include <language_specific_truthy_operations.h>
namespace Test {
class OperationsTest : public ::testing::Test, public UnaryOperations::unaryOperations {
    public:
        template<typename T>
        inline static void runUnaryTest(const char* testName, const Any value, bool expectedResult) {
            bool result = isOther<T>(&value);
            EXPECT_EQ(result, expectedResult);
        };
        template<typename T>
        inline static void runNumericTest(const char* testName, const Any value, bool expectedResult) {
            bool result = isOther<T>(&value);
            EXPECT_EQ(result, expectedResult);
        };
        template<typename T>
        inline static void runOtherTest(const char* testName, const Any value, bool expectedResult) {
            bool result = isOther<T>(&value);
            EXPECT_EQ(result, expectedResult);
        };
    protected:
        void SetUp() override {
            // Setup code if needed
        }   
};
};
using namespace Test;

TEST_F(OperationsTest, BinaryIDs) {
    {
        Vector<int> vec;
        Any value(vec);
        runUnaryTest<int>("Vector<int> test", value, true);
    }

    // Test Case 2: Pointer test
    {
        int* ptr = nullptr;
        Any value(ptr);
        runUnaryTest<int>("int* pointer test", value, true);
    }

    // Test Case 3: NukeInstance test
    {
        NuclearLang::NukeInstance* instance = nullptr;
        Any value(instance);
        runUnaryTest<int>("NukeInstance test", value, true);
    }
    
}
TEST_F(OperationsTest, ToNumeric) {
    {
        Vector<int> vec;
        Any value(vec);
        runNumericTest<int>("Vector<int> test", value, true);
    }

    // Test Case 2: Pointer test
    {
        int* ptr = nullptr;
        Any value(ptr);
        runNumericTest<int>("int* pointer test", value, true);
    }

    // Test Case 3: NukeInstance test
    {
        NuclearLang::NukeInstance* instance = nullptr;
        Any value(instance);
        runNumericTest<int>("NukeInstance test", value, true);
    }
    
}
// Must convert a string into a vector 
TEST_F(OperationsTest, ToOther) {
    {
        Vector<int> vec;
        Any value(vec);
        runOtherTest<int>("Vector<int> test", value, true);
    }

    // Test Case 2: Pointer test
    {
        int* ptr = nullptr;
        Any value(ptr);
        runOtherTest<int>("int* pointer test", value, true);
    }

    // Test Case 3: NukeInstance test
    {
        NuclearLang::NukeInstance* instance = nullptr;
        Any value(instance);
        runOtherTest<int>("NukeInstance test", value, true);
    }
    
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}