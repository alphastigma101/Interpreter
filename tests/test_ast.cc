#include <abstraction_tree_syntax.h>
#include <gtest/gtest.h>
logTable<std::map<std::string, std::vector<std::string>>> logEntries; // declare variable globally
// Test fixture for AbstractionTreeSyntax classes
class AbstractionTreeSyntaxTest : public testing::Test, public AbstractionTreeSyntax::ast {
    public:
        AbstractionTreeSyntaxTest();
        ~AbstractionTreeSyntaxTest();
        static std::string demangle(const char* name);
};

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

// Test construction Unary node
TEST(CompressedAstTreeTest, ConstructUnaryNode) {
}

// Test construction of Grouping Node
TEST(CompressedAstTreeTest, ConstructGroupingNode) {
}

// Test construction of Literal Node
TEST(CompressedAstTreeTest, ConstructLiteralNode) {
}

// Test generateAst constructor with invalid path
TEST_F(AbstractionTreeSyntaxTest, GenerateAstConstructorInvalidFileNameAndChoice) {

}


// Test ast setTable and getTable methods
/*TEST_F(AbstractionTreeSyntaxTest, AstSetAndGetTable) {
    ExprTypes expr; // You need to define this type and provide a valid instance
    ast tree(expr);
    tree.setTable();
    EXPECT_NO_THROW({
        Table table = tree.getTable();
    });
}*/

/*

// Test analyzeSemantics constructor
TEST_F(AbstractionTreeSyntaxTest, AnalyzeSemanticsConstructor) {
    ExprTypes expr; // You need to define this type and provide a valid instance
    ast tree(expr);
    EXPECT_NO_THROW({
        analyzeSemantics semantics(tree);
    });
}

// Test intermediateRepresentation constructor and generate method
TEST_F(AbstractionTreeSyntaxTest, IntermediateRepresentationConstructorAndGenerate) {
    ExprTypes expr; // You need to define this type and provide a valid instance
    ast tree(expr);
    analyzeSemantics semantics(tree);
    EXPECT_NO_THROW({
        intermediateRepresentation ir(semantics);
        ir.generate();
    });
}*/

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
