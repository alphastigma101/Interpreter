#include <gtest/gtest.h>
#include <user_stack.h>
using namespace Stack;

class StackTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear the stack before each test
        while (!stack::isEmpty()) {
            stack::pop();
        }
    }
};

TEST_F(StackTest, PushAndPeek) {
    std::map<std::string, bool> item1 = {{"key1", true}};
    std::map<std::string, bool> item2 = {{"key2", false}};
    
    stack::push(&item1);
    stack::push(&item2);
    
    EXPECT_EQ(stack::peek(), item2) << "Peek should return the last pushed item.";
}

TEST_F(StackTest, PushAndPop) {
    std::map<std::string, bool> item = {{"key", true}};
    stack::push(&item);
    ASSERT_FALSE(stack::isEmpty()) << "Stack should not be empty after a push.";
    
    stack::pop();
    EXPECT_TRUE(stack::isEmpty()) << "Stack should be empty after popping the only item.";
}

TEST_F(StackTest, IsEmpty) {
    EXPECT_TRUE(stack::isEmpty()) << "Newly created stack should be empty.";
    
    std::map<std::string, bool> item = {{"key", true}};
    stack::push(&item);
    EXPECT_FALSE(stack::isEmpty()) << "Stack should not be empty after a push.";
}

TEST_F(StackTest, Size) {
    EXPECT_EQ(stack::size(), 0) << "Initial stack size should be 0.";
    
    std::map<std::string, bool> item1 = {{"key1", true}};
    std::map<std::string, bool> item2 = {{"key2", false}};
    stack::push(&item1);
    stack::push(&item2);
    
    EXPECT_EQ(stack::size(), 2) << "Stack size should reflect the number of pushed elements.";
}

TEST_F(StackTest, GetSpecificItem) {
    std::map<std::string, bool> item1 = {{"key1", true}};
    std::map<std::string, bool> item2 = {{"key2", false}};
    stack::push(&item1);
    stack::push(&item2);
    
    EXPECT_EQ(stack::get(0), item1) << "get(0) should return the first pushed item.";
    EXPECT_EQ(stack::get(1), item2) << "get(1) should return the second pushed item.";
}

TEST_F(StackTest, HandlePopOnEmptyStack) {
    EXPECT_TRUE(stack::isEmpty()) << "Stack should initially be empty.";
    
    EXPECT_THROW(stack::pop(), std::runtime_error) << "Popping an empty stack should throw an error.";
}

TEST_F(StackTest, HandlePeekOnEmptyStack) {
    EXPECT_TRUE(stack::isEmpty()) << "Stack should initially be empty.";
    
    EXPECT_THROW(stack::peek(), std::runtime_error) << "Peeking an empty stack should throw an error.";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
