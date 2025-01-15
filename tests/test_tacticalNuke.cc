#include <gtest/gtest.h>
#include <tactical_nuke.h>
namespace fs = std::filesystem;
class tacticalNukeTest : public ::testing::Test {
    public: 
        inline static bool parseAndValidateFilePath(const std::string& filePath) {
            try {
                fs::path path(filePath);

                // Check if the path exists and is a regular file
                return fs::exists(path) && fs::is_regular_file(path);
            } catch (const fs::filesystem_error& e) {
                return false;
            }
        };
    protected:
        void SetUp() override {
            // Setup code if needed
        }   
};
TEST(tacticalNukeTest, ValidFilePath) {
    const std::string filePath = "../Code-Analysis/TaticalNuke/Classes/class.nuke";
    EXPECT_TRUE(tacticalNukeTest::parseAndValidateFilePath(filePath)) << "File path should be valid and exist.";
}

TEST(tacticalNukeTest, InvalidFilePath) {
    const std::string invalidPath = "../invalid/path/to/file.nuke";
    EXPECT_FALSE(tacticalNukeTest::parseAndValidateFilePath(invalidPath)) << "File path should be invalid or not exist.";
}

TEST(tacticalNukeTest, EmptyFilePath) {
    const std::string emptyPath = "";
    EXPECT_FALSE(tacticalNukeTest::parseAndValidateFilePath(emptyPath)) << "Empty file path should be invalid.";
}

TEST(tacticalNukeTest, RelativeFilePath) {
    const std::string relativePath = "../Code-Analysis/TaticalNuke/Classes/class.nuke";
    EXPECT_TRUE(tacticalNukeTest::parseAndValidateFilePath(relativePath)) << "Relative file path should be valid if it exists.";
}

TEST(tacticalNukeTest, AbsoluteFilePath) {
    const std::string absolutePath = "/absolute/path/to/class.nuke";
    EXPECT_FALSE(tacticalNukeTest::parseAndValidateFilePath(absolutePath)) << "Absolute file path should be tested based on your system.";
}

TEST_F(tacticalNukeTest, TestNuke) {
    // TODO: Need to pass in a dictionary and not a file 
    /*NuclearLang::Nuke nuke;
    nuke.launch();*/
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
