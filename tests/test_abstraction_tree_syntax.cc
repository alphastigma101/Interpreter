#include <gtest/gtest.h>
#include <scanner.h>
#include <abstraction_tree_syntax.h>
// Test fixture for AbstractionTreeSyntax classes
class AbstractionTreeSyntaxTest : public testing::Test/*, public AbstractionTreeSyntax::ast*/ {
    public:
        AbstractionTreeSyntaxTest();
        ~AbstractionTreeSyntaxTest();
        static std::string demangle(const char* name);
};
AbstractionTreeSyntaxTest::AbstractionTreeSyntaxTest() {}
AbstractionTreeSyntaxTest::~AbstractionTreeSyntaxTest() {}
std::string AbstractionTreeSyntaxTest::demangle(const char* name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
}

// Test construction of Binary node
TEST(CompressedAstTreeTest, ConstructBinaryNode) {
    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}