#include "logging.h" // Assuming the logging class is in this header
#include <filesystem>
#include <fstream>
#include <chrono>
#include <any>
#include <sstream>
#include <fstream>
using Any = std::any;
logTable<std::map<std::string, std::vector<std::string>>> logEntries;

void createTestLogFile(const std::string& filename, std::chrono::system_clock::time_point modTime) {
    auto now = std::chrono::system_clock::now();

    // Convert time_point to time_t to get a C-style time
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // Convert time_t to tm structure for local time
    std::tm* now_tm = std::localtime(&now_c);

    // Create a string stream to format the time
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");


    std::filesystem::path filePath(filename);

    // Create an empty file
    std::ofstream file(filePath);
    if (!file) {
        throw std::runtime_error("Failed to create file: " + filename);
    }
    else {
        file.open(filePath);
        file << oss.str();
    }
    file.close();

    // Set the modification time
    std::filesystem::last_write_time(filePath);
}

void debugRotate() {
    // Manually debug the rotate method
    logging<Any> log(logEntries, "Testing");
    auto now = std::chrono::system_clock::now();
    //createTestLogFile("old_log.json", now - std::chrono::hours(24 * 31)); // 31 days old
    createTestLogFile("new_log.json", now - std::chrono::hours(24 * 29)); // 29 days old
    log.update();
    log.write();
    log.rotate();
    return;
}


void debugUpdate() {
    std::string test = "Test log entry";
    logging<Any> log(logEntries, test);
    log.update;
    return;
}

void debugWrite() {
     // Manually debug write method
    std::string text = "Test log entry";
    logging<Any> log(logEntries, text);
    log.update;
    log.write;
    return;
}

void debugGetterMethods() {
    // Manually debug the getTimeString
    //logging<Any> log(logEntries, "Testing");
    //std::string timeString = log.getCurrentTimeString();
    // Check if the string matches the format "YYYY-MM-DD HH:MM:SS"
    std::regex timeRegex("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}");
    return;
}


int main(void) {
   debugRotate();
   debugUpdate();
   debugWrite();
   debugGetterMethods();
   return 0;
}
