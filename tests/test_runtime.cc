#include <gtest/gtest.h>
#include <run_time_error.h>
#include <token.h>
#include <string>
#include <vector>
#include <memory>
#include <cstring>

class StringPropertyError : protected runtimeerror<StringPropertyError> {
    friend class runtimeerror<StringPropertyError>;
    public:
        explicit StringPropertyError() = default;
        static const char* what() throw();
};

const char *StringPropertyError::what() throw() {
    if (type == nullptr) return message_;
    if (literal == "Token") {
        auto token = dynamic_cast<Token*>(static_cast<Token*>(type));
        String error = token->getLexeme() + " " + message_;
        char* result = new char[error.size() + 1];
        std::strcpy(result, error.c_str());
        return result;
    }
    else if (literal == "TokenType") {
        try {
            auto& value = *reinterpret_cast<TokenType*>(type);
            String error = tokenTypeStrings.at(value) + " " + message_;
            char* result = new char[error.size() + 1];
            std::strcpy(result, error.c_str());
            return result;
        } catch (...) { throw "Invalid type"; }
    }
    return "";
}

class RuntimeErrorTest :  public ::testing::Test {
    friend class StringPropertyError;
    protected:
        void SetUp() override {}
        void TearDown() override {}
};

TEST_F(RuntimeErrorTest, BasicStringError) {
    try {
        throw runtimeerror<StringPropertyError>(nullptr, "Basic error message");
    } catch (runtimeerror<StringPropertyError>& e) {
        EXPECT_STREQ(e.what(), "Basic error message");
    }
    try {
        Token op = Token(TokenType::LEFT_PAREN, "Testing", "Testing", 0);
        runtimeerror<StringPropertyError>::literal = "Token";
        throw runtimeerror<StringPropertyError>(&op, "Basic error message");
    } catch (runtimeerror<StringPropertyError>& e) {
        const char* error = e.what();
        EXPECT_STREQ(e.what(), "Testing Basic error message");
    }
    try {
        auto tmp = TokenType::LEFT_PAREN;
        runtimeerror<StringPropertyError>::literal = "TokenType";
        throw runtimeerror<StringPropertyError>(&tmp, "Basic error message");
    } catch (runtimeerror<StringPropertyError>& e) {
        const char* error = e.what();
        EXPECT_STREQ(e.what(), "LEFT_PAREN Basic error message");
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
