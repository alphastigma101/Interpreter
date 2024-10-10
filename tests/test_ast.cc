#include <abstraction_tree_syntax.h>
#include <gtest/gtest.h>
logTable<std::map<std::string, std::vector<std::string>>> logEntries; // declare variable globally
// Test fixture for AbstractionTreeSyntax classes
class AbstractionTreeSyntaxTest : public testing::Test, public Binary, public Unary, public Grouping, public Literal {
    public:
        AbstractionTreeSyntaxTest();
        ~AbstractionTreeSyntaxTest();
        static std::string demangle(const char* name);
        static Binary B();
        static Unary U();
        static Grouping G();
        static Literal L();
};

Binary AbstractionTreeSyntaxTest::B() { return Binary(); }

Unary AbstractionTreeSyntaxTest::U() {  return Unary(); }

Grouping AbstractionTreeSyntaxTest::G() { return Grouping(); }

Literal AbstractionTreeSyntaxTest::L() { return Literal(); }

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
    auto res =  AbstractionTreeSyntaxTest::B();
    astTree<int, std::string, std::any> result = compressedAstTree(1, "Binary", std::make_any<Binary>(res));
    EXPECT_EQ(std::get<0>(result), 1);
    EXPECT_EQ(std::get<1>(result).first, "Binary");
    std::string temp = AbstractionTreeSyntaxTest::demangle(typeid(std::any_cast<Binary>(std::get<1>(result).second)).name());
    EXPECT_EQ(temp, "ContextFreeGrammar::Binary");
}

// Test construction Unary node
TEST(CompressedAstTreeTest, ConstructUnaryNode) {
    auto res =  AbstractionTreeSyntaxTest::U();
    astTree<int, std::string, std::any> result = compressedAstTree(2, "Unary", std::make_any<Unary>(res));
    EXPECT_EQ(std::get<0>(result), 2);
    EXPECT_EQ(std::get<1>(result).first, "Unary");
    std::string temp = AbstractionTreeSyntaxTest::demangle(typeid(std::any_cast<Unary>(std::get<1>(result).second)).name());
    EXPECT_EQ(temp, "ContextFreeGrammar::Unary");
}

// Test construction of Grouping Node
TEST(CompressedAstTreeTest, ConstructGroupingNode) {
    auto res =  AbstractionTreeSyntaxTest::G();
    astTree<int, std::string, std::any> result = compressedAstTree(3, "Grouping", std::make_any<Grouping>(res));
    EXPECT_EQ(std::get<0>(result), 3);
    EXPECT_EQ(std::get<1>(result).first, "Grouping");
    std::string temp = AbstractionTreeSyntaxTest::demangle(typeid(std::any_cast<Grouping>(std::get<1>(result).second)).name());
    EXPECT_EQ(temp, "ContextFreeGrammar::Grouping");
}

// Test construction of Literal Node
TEST(CompressedAstTreeTest, ConstructLiteralNode) {
    auto res =  AbstractionTreeSyntaxTest::L();
    astTree<int, std::string, std::any> result = compressedAstTree(4, "Literal", std::make_any<Literal>(res));
    EXPECT_EQ(std::get<0>(result), 4);
    EXPECT_EQ(std::get<1>(result).first, "Literal");
    std::string temp = AbstractionTreeSyntaxTest::demangle(typeid(std::any_cast<Literal>(std::get<1>(result).second)).name());
    EXPECT_EQ(temp, "ContextFreeGrammar::Literal");
}
using Catcher = catcher<ast>;
// Test generateAst constructor with invalid path
TEST_F(AbstractionTreeSyntaxTest, GenerateAstConstructorInvalidFileNameAndChoice) {
    auto res =  AbstractionTreeSyntaxTest::G();
    astTree<int, std::string, std::any> result = compressedAstTree(3, "Grouping", std::make_any<Grouping>(res));
    std::vector<astTree<int, std::string, std::any>> v;
    v.push_back(result);
    EXPECT_THROW({
        ast at(v);
        }, Catcher);
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
