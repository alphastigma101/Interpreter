#include <gtest/gtest.h>
#include "truthyOperations.h"  // Assuming this is where the class is defined

class TruthyOperationsTest : public ::testing::Test {
protected:
    truthyOperations to;
};

TEST_F(TruthyOperationsTest, PythonTruthiness) {
    ct.setTokenLanguage(LanguageTokenTypes::Python);

    // Test None (false)
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Python::None()));

    // Test Bool
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Python::Bool(true)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Python::Bool(false)));

    // Test Int
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Python::Int(1)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Python::Int(0)));

    // Test Float
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Python::Float(0.1)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Python::Float(0.0)));

    // Test Str
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Python::Str("Hello")));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Python::Str("")));

    // Test List
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Python::List({1, 2, 3})));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Python::List()));

    // Test Dict
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Python::Dict({{1, "one"}})));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Python::Dict()));
}

TEST_F(TruthyOperationsTest, JavaScriptTruthiness) {
    ct.setTokenLanguage(LanguageTokenTypes::JavaScript);

    // Test Null (false)
    EXPECT_FALSE(to.isTruthy(LanguageTypes::JavaScript::Null()));

    // Test Undefined (false)
    EXPECT_FALSE(to.isTruthy(LanguageTypes::JavaScript::Undefined()));

    // Test Boolean
    EXPECT_TRUE(to.isTruthy(LanguageTypes::JavaScript::Boolean(true)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::JavaScript::Boolean(false)));

    // Test Number
    EXPECT_TRUE(to.isTruthy(LanguageTypes::JavaScript::Number(1)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::JavaScript::Number(0)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::JavaScript::Number(NAN)));

    // Test String
    EXPECT_TRUE(to.isTruthy(LanguageTypes::JavaScript::String("Hello")));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::JavaScript::String("")));
}

TEST_F(TruthyOperationsTest, RubyTruthiness) {
    ct.setTokenLanguage(LanguageTokenTypes::Ruby);

    // Test Nil (false)
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Ruby::Nil()));

    // Test TrueClass (true)
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Ruby::TrueClass()));

    // Test FalseClass (false)
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Ruby::FalseClass()));

    // Test other types (should all be true)
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Ruby::Integer(0)));
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Ruby::String("")));
}

TEST_F(TruthyOperationsTest, CPPTruthiness) {
    ct.setTokenLanguage(LanguageTokenTypes::CPP);

    // Test Bool
    EXPECT_TRUE(to.isTruthy(LanguageTypes::CPP::Bool(true)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::CPP::Bool(false)));

    // Test Int
    EXPECT_TRUE(to.isTruthy(LanguageTypes::CPP::Int(1)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::CPP::Int(0)));

    // Test Double
    EXPECT_TRUE(to.isTruthy(LanguageTypes::CPP::Double(0.1)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::CPP::Double(0.0)));

    // Test Nullptr (false)
    EXPECT_FALSE(to.isTruthy(LanguageTypes::CPP::Nullptr()));
}

// Additional tests for other languages
TEST_F(TruthyOperationsTest, JavaTruthiness) {
    ct.setTokenLanguage(LanguageTokenTypes::Java);

    EXPECT_FALSE(to.isTruthy(LanguageTypes::Java::Null()));
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Java::Boolean(true)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Java::Boolean(false)));
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Java::Integer(1)));  // Assuming non-null objects are truthy
}

TEST_F(TruthyOperationsTest, GoTruthiness) {
    ct.setTokenLanguage(LanguageTokenTypes::Go);

    EXPECT_TRUE(to.isTruthy(LanguageTypes::Go::Bool(true)));
    EXPECT_FALSE(to.isTruthy(LanguageTypes::Go::Bool(false)));
    EXPECT_TRUE(to.isTruthy(LanguageTypes::Go::Int(1)));  // Assuming non-bool types are always truthy
}

TEST_F(TruthyOperationsTest, PHPTruthiness) {
    ct.setTokenLanguage(LanguageTokenTypes::PHP);

    EXPECT_FALSE(to.isTruthy(nullptr));
    EXPECT_TRUE(to.isTruthy(true));
    EXPECT_FALSE(to.isTruthy(false));
    EXPECT_TRUE(to.isTruthy(1));
    EXPECT_FALSE(to.isTruthy(0));
    EXPECT_TRUE(to.isTruthy(0.1f));
    EXPECT_FALSE(to.isTruthy(0.0f));
    EXPECT_TRUE(to.isTruthy(std::string("Hello")));
    EXPECT_FALSE(to.isTruthy(std::string("")));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
