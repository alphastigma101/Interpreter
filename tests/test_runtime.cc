#include <gtest/gtest.h>
#include <run_time_error.h>
#include <string>
#include <vector>
#include <memory>

class StringPropertyError : public runtimeerror<StringPropertyError> {
    public:
        std::string message;
        explicit StringPropertyError(const std::string& msg) : message(msg) {}
        
        static const void* getType(); 
        static const char* what(const void* type = getType(), const char* msg = runtimeerror<StringPropertyError>::getMsg()) throw();
};

const void *StringPropertyError::getType() {
    return nullptr;
}

const char *StringPropertyError::what(const void *type, const char *msg) throw() {
    return nullptr;
}

class ComplexPropertyError : public runtimeerror<ComplexPropertyError> {
    public:
        std::string message;
        int errorCode;
        std::vector<std::string> stackTrace;
        
        ComplexPropertyError(const std::string& msg, int code) 
            : message(msg), errorCode(code) {
            stackTrace.push_back("Frame 1");
            stackTrace.push_back("Frame 2");
        }
        
        static const void* getType(); 
        static const char* what(const void* type = getType(), const char* msg = runtimeerror<ComplexPropertyError>::getMsg()) throw();
};
const void *ComplexPropertyError::getType() {
    return nullptr;
}

const char *ComplexPropertyError::what(const void *type, const char *msg) throw() {
    return nullptr;
}

class NestedPropertyError : public runtimeerror<NestedPropertyError> {
    public:
        struct ErrorDetails {
            std::string context;
            int line;
            int column;
        };
    
        ErrorDetails details;
        std::string message;
    
        NestedPropertyError(const std::string& msg, const std::string& ctx, int line, int col) 
            : message(msg), details{ctx, line, col} {};
    
        static const void* getType(); 
        static const char* what(const void* type = getType(), const char* msg = runtimeerror<NestedPropertyError>::getMsg()) throw();
};

const void *NestedPropertyError::getType() {
    return nullptr;
}

const char *NestedPropertyError::what(const void *type, const char *msg) throw() {
    return nullptr;
}

class PointerPropertyError : public runtimeerror<PointerPropertyError> {
public:
    std::unique_ptr<std::string> dynamicMessage;
    int* rawPointer;
    
    explicit PointerPropertyError(const std::string& msg) {
        dynamicMessage = std::make_unique<std::string>(msg);
        rawPointer = new int(42);
    }
    
    ~PointerPropertyError() {
        delete rawPointer;
    }
    
    static const void* getType(); 
    static const char* what(const void* type = getType(), const char* msg = runtimeerror<PointerPropertyError>::getMsg()) throw();
};
const void *PointerPropertyError::getType() {
    return nullptr;
}

const char *PointerPropertyError::what(const void *type, const char *msg) throw() {
    return nullptr;
}

class RuntimeErrorTest : public ::testing::Test {
    protected:
        void SetUp() override {}
        void TearDown() override {}
};

TEST_F(RuntimeErrorTest, BasicStringError) {
    EXPECT_THROW({
        try {
            throw StringPropertyError("Basic error message");
        } catch (const StringPropertyError& e) {
            EXPECT_STREQ(e.what(), "Basic error message");
            throw;
        }
    }, StringPropertyError);
}

TEST_F(RuntimeErrorTest, ComplexError) {
    EXPECT_THROW({
        try {
            throw ComplexPropertyError("Complex error", 500);
        } catch (const ComplexPropertyError& e) {
            EXPECT_STREQ(e.what(), "Complex error");
            EXPECT_EQ(e.errorCode, 500);
            EXPECT_EQ(e.stackTrace.size(), 2);
            throw;
        }
    }, ComplexPropertyError);
}

TEST_F(RuntimeErrorTest, NestedError) {
    EXPECT_THROW({
        try {
            throw NestedPropertyError("Parser error", "main.cpp", 42, 10);
        } catch (const NestedPropertyError& e) {
            EXPECT_STREQ(e.what(), "Parser error");
            EXPECT_EQ(e.details.line, 42);
            EXPECT_EQ(e.details.column, 10);
            EXPECT_EQ(e.details.context, "main.cpp");
            throw;
        }
    }, NestedPropertyError);
}

TEST_F(RuntimeErrorTest, PointerError) {
    EXPECT_THROW({
        try {
            throw PointerPropertyError("Dynamic error message");
        } catch (const PointerPropertyError& e) {
            EXPECT_STREQ(e.what(), "Dynamic error message");
            EXPECT_NE(e.rawPointer, nullptr);
            EXPECT_EQ(*e.rawPointer, 42);
            throw;
        }
    }, PointerPropertyError);
}

TEST_F(RuntimeErrorTest, ChainedExceptions) {
    EXPECT_THROW({
        try {
            try {
                throw StringPropertyError("Inner error");
            } catch (const StringPropertyError& e) {
                throw ComplexPropertyError(std::string("Outer: ") + e.what(), 500);
            }
        } catch (const ComplexPropertyError& e) {
            EXPECT_STREQ(e.what(), "Outer: Inner error");
            throw;
        }
    }, ComplexPropertyError);
}

TEST_F(RuntimeErrorTest, LongMessageError) {
    std::string longMessage(1000, 'A'); // 1000 'A' characters
    EXPECT_THROW({
        try {
            throw StringPropertyError(longMessage);
        } catch (const StringPropertyError& e) {
            EXPECT_STREQ(e.what(), longMessage.c_str());
            throw;
        }
    }, StringPropertyError);
}

TEST_F(RuntimeErrorTest, EmptyMessageError) {
    EXPECT_THROW({
        try {
            throw StringPropertyError("");
        } catch (const StringPropertyError& e) {
            EXPECT_STREQ(e.what(), "");
            throw;
        }
    }, StringPropertyError);
}

TEST_F(RuntimeErrorTest, UnicodeMessageError) {
    EXPECT_THROW({
        try {
            throw StringPropertyError("Unicode test: 测试 тест テスト");
        } catch (const StringPropertyError& e) {
            EXPECT_STREQ(e.what(), "Unicode test: 测试 тест テスト");
            throw;
        }
    }, StringPropertyError);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
