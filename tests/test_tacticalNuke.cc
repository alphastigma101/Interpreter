#include <gtest/gtest.h>
#include <tactical_nuke.h>
class tacticalNukeTest : public ::testing::Test {
    protected:
        void SetUp() override {
            // Setup code if needed
        }   
};
TEST_F(tacticalNukeTest, RootFiles) {
    NuclearLang::Nuke nuke;
    nuke.runFile("class.nuke");
    if (argc > 2) {
        std::cerr << "Usage: [script]";
        exit(1); 
    }
    else if (argc == 2) nuke.runFile(argv[1]);
    else { nuke.runPrompt(); }
    
}

TEST_F(tacticalNukeTest, OddPath) {
    // TODO: There is an issue going on with the code such that if passing a file like this: ../path/to/file/file.nuke
    // It won't parse it for some reason.
    NuclearLang::Nuke nuke;
    nuke.runFile("../Code-Analysis/TaticalNuke/Classes/class.nuke");
    if (argc > 2) {
        std::cerr << "Usage: [script]";
        exit(1); 
    }
    else if (argc == 2) nuke.runFile(argv[1]);
    else { nuke.runPrompt(); }
    
}

TEST_F(tacticalNukeTest, MultiplePaths) {
    // TODO: Need to pass in a dictionary and not a file 
    NuclearLang::Nuke nuke;
    nuke.runFile("../Code-Analysis/TaticalNuke/Classes/class.nuke");
    if (argc > 2) {
        std::cerr << "Usage: [script]";
        exit(1); 
    }
    else if (argc == 2) nuke.runFile(argv[1]);
    else { nuke.runPrompt(); }
    
}

TEST_F(tacticalNukeTest, TestNuke) {
    // TODO: Need to pass in a dictionary and not a file 
    NuclearLang::Nuke nuke;
    nuke.launch();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
