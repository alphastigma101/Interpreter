#include <gtest/gtest.h>
#include "languages.h"

class LanguagesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }

    void TearDown() override {
        // Teardown code if needed
    }
};

// Test the replace function
TEST_F(LanguagesTest, ReplaceFunction) {
    std::string code = "FUNCTION FOR WHILE IF";
    std::string for_loop = "for_test";
    std::string while_loop = "while_test";
    std::string if_block = "if_test";
    std::string function = "function_test";
    std::unordered_map<std::string, std::pair<int,int>> values = {
        {"FUNCTION", {0, 8}},
        {"FOR", {0, 3}},
        {"WHILE", {0, 5}},
        {"IF", {0, 2}}
    };

    std::string result = operations::replace(code, for_loop, while_loop, if_block, function, values);
    EXPECT_EQ(result, "function_test for_test while_test if_test");
}

// Test C language function
TEST_F(LanguagesTest, CLangFunction) {
    std::string result = static_languages::C();
    EXPECT_TRUE(result.find("for (int i = 0; i < 10; i++)") != std::string::npos);
    EXPECT_TRUE(result.find("while (true)") != std::string::npos);
    EXPECT_TRUE(result.find("if (true)") != std::string::npos);
}

// Test C++ language function
TEST_F(LanguagesTest, CPPLangFunction) {
    std::string result = static_languages::CPP();
    EXPECT_TRUE(result.find("for (int i = 0; i < 10; i++)") != std::string::npos);
    EXPECT_TRUE(result.find("while (true)") != std::string::npos);
    EXPECT_TRUE(result.find("if (true)") != std::string::npos);
}

// Test Java language function
TEST_F(LanguagesTest, JavaLangFunction) {
    std::string result = static_languages::Java();
    EXPECT_TRUE(result.find("for (int i = 0; i < 10; i++)") != std::string::npos);
    EXPECT_TRUE(result.find("while (true)") != std::string::npos);
    EXPECT_TRUE(result.find("if (true)") != std::string::npos);
}

// Test Python language function
TEST_F(LanguagesTest, PythonLangFunction) {
    std::string result = dynamic_languages::Python();
    EXPECT_TRUE(result.find("for i in range(0, 10):") != std::string::npos);
    EXPECT_TRUE(result.find("while (True):") != std::string::npos);
    EXPECT_TRUE(result.find("if (true):") != std::string::npos);
}

// Test JavaScript language function
TEST_F(LanguagesTest, JavaScriptLangFunction) {
    std::string result = dynamic_languages::JavaScript();
    EXPECT_TRUE(result.find("for (var i in arr)") != std::string::npos);
    EXPECT_TRUE(result.find("while (true)") != std::string::npos);
    EXPECT_TRUE(result.find("if (true)") != std::string::npos);
}

// Test Ruby language function
TEST_F(LanguagesTest, RubyLangFunction) {
    std::string result = dynamic_languages::Ruby();
    EXPECT_TRUE(result.find("for i in 0...size") != std::string::npos);
    EXPECT_TRUE(result.find("while i1 <= max") != std::string::npos);
    EXPECT_TRUE(result.find("if block_given?") != std::string::npos);
}

// Add more tests for other language functions as needed

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
