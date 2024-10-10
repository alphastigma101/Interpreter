#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <logging.h>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <sstream>
#include <fstream>
#include <iomanip>
logTable<std::map<std::string, std::vector<std::string>>> logEntries;
class LoggingTest : public testing::Test {
    protected:
        logging<std::string> logger;
        std::filesystem::path testLogDir = "logs";

        void SetUp() override {
            // Create a test logs directory
            if (!std::filesystem::exists(testLogDir)) {
                std::filesystem::create_directory(testLogDir);
            }
        }

        void TearDown() override {
            // Clean up test logs directory
            if (std::filesystem::exists(testLogDir)) {
                std::filesystem::remove_all(testLogDir);
            }
        }

        // Helper method to create a test log file
        void createTestLogFile(const std::string& filename, std::chrono::system_clock::time_point modTime) {
            std::ofstream file(testLogDir / filename);
            std::ostringstream oss;
            auto now = std::chrono::system_clock::now();
            // Convert time_point to time_t to get a C-style time
            std::time_t now_c = std::chrono::system_clock::to_time_t(now);
            // Convert time_t to tm structure for local time
            std::tm* now_tm = std::localtime(&now_c);
            oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
            file.open(testLogDir / filename);
            file << oss.str();
            file.close();
            //std::filesystem::last_write_time(testLogDir);
        }
};

TEST_F(LoggingTest, RotateRemovesOldLogs) {
    auto now = std::chrono::system_clock::now();
    createTestLogFile("old_log.json", now - std::chrono::hours(24 * 31)); // 31 days old
    createTestLogFile("new_log.json", now - std::chrono::hours(24 * 29)); // 29 days old
    logger.write();
    logger.rotate();

    EXPECT_FALSE(std::filesystem::exists(testLogDir / "old_log.json"));
    EXPECT_TRUE(std::filesystem::exists(testLogDir / "new_log.json"));
}

/*TEST_F(LoggingTest, UpdateAddsNewLogEntry) {
    logger.text = "Test log entry";
    logger.update();

    EXPECT_EQ(logger.currentEntries.size(), 1);
    EXPECT_EQ(logger.currentEntries.begin()->second.size(), 1);
    EXPECT_EQ(logger.currentEntries.begin()->second[0], "Test log entry");
}

TEST_F(LoggingTest, WriteCreatesJsonFile) {
    logger.text = "Test log entry";
    logger.update();

    EXPECT_TRUE(logger.write());

    auto files = std::filesystem::directory_iterator(testLogDir);
    EXPECT_NE(files, std::filesystem::directory_iterator());

    std::string fileContent;
    std::ifstream file(files->path());
    std::getline(file, fileContent, '\0');
    
    EXPECT_THAT(fileContent, testing::HasSubstr("Test log entry"));
}

TEST_F(LoggingTest, GetCurrentTimeStringReturnsFormattedTime) {
    std::string timeString = logger.getCurrentTimeString();

    // Check if the string matches the format "YYYY-MM-DD HH:MM:SS"
    std::regex timeRegex("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}");
    EXPECT_TRUE(std::regex_match(timeString, timeRegex));
}*/
// Driver Code
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
