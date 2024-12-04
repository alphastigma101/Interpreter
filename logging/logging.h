#ifndef _LOGGING_H_
#define _LOGGING_H_
#include <any>
#include <map>
#include <chrono>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <filesystem>
namespace Logging {
    template<class T>
    class logging {
        public:
            logging() = default;
            explicit logging<T>(const std::string& text) {
                this->text = text;
                // Need to check if it is empty
                // if not use getCurrentTime() as the key and see if the value is the same 
                // if not create a new entry
                currentEntries[getCurrentTime()] = {this->text};
            };
            ~logging() noexcept = default;
            inline static std::string getCurrentTime() {
                // Get current time as time_point
                auto now = std::chrono::system_clock::now();

                // Convert time_point to time_t to get a C-style time
                std::time_t now_c = std::chrono::system_clock::to_time_t(now);

                // Convert time_t to tm structure for local time
                std::tm* now_tm = std::localtime(&now_c);

                // Create a string stream to format the time
                std::ostringstream oss;
                oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

                // Return the formatted time as a string
                return oss.str();
            };
            inline static void rotate() {
                std::filesystem::path logDir = "logs";
                // Create logs directory if it doesn't exist
                if (!std::filesystem::exists(logDir)) { std::filesystem::create_directory(logDir); }

                // Iterate through each file in the logs directory
                for (const auto& entry : std::filesystem::directory_iterator(logDir)) {
                    if (entry.is_regular_file() && entry.path().extension() == ".json") {
                        // Process the JSON file, for example, by checking the last modification date
                        auto lastWriteTime = std::filesystem::last_write_time(entry.path());
                        // Convert std::filesystem::file_time_type to std::chrono::system_clock::time_point
                        auto ftime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                                lastWriteTime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now()
                        );
                        auto age = std::chrono::system_clock::now() - ftime;
                        // adjust the chrono corectly by hours, minutes, and or seconds
                        // Tested out rotation by adjusting std::chrono::minutes(30) to std::chrono::seconds(1)
                        if (age > std::chrono::minutes(30)) {
                            std::filesystem::remove(entry.path()); // Remove old logs
                        }
                    }
                }
                return;
            };
            /** -------------------------------------------------
             * @brief Write the logs data to a .json file.
             * 
             * @details This method writes the contents of the logs object to a .json file in the "logs" directory.
             *          The filename is based on the current timestamp.
             * 
             * @return bool Returns true if the write operation is successful, false otherwise.
             * ---------------------------------------------------
            */                      
            inline static bool write() {
                std::filesystem::path logDir = "logs";
                std::string entryName = read();
                if (entryName.empty()) {
                    std::string filename = logDir.string() + "/" + getCurrentTime() + ".json";
                    create(filename);
                }
                else {
                    std::string filename = logDir.string() + "/" + entryName + ".json";
                    create(filename);
                }
                return true;
            };
            void printLogs();
            inline static std::string getText() { return text; };
            inline std::map<std::string, std::vector<std::string>> getLogs() { return currentEntries; };
        private:
            inline static std::map<std::string, std::vector<std::string>> currentEntries{};
            inline static std::string text = "\0";
            /** --------------------------------------------------------
                * @brief write to the file in JSON-like format
                *
                * @return returns the file back 
                * ----------------------------------------------------------
            */
            inline static void create(std::string& filename) {
                // Read the entire content of the input file
                std::ifstream ifs(filename);
                std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
                ifs.close();

                // Open the same file for writing
                std::ofstream ofs(filename, std::ios::out | std::ios::trunc);
                if (!ofs.is_open()) {
                    throw std::runtime_error("Unable to open file for writing: " + filename);
                }

                if (content.empty()) {
                    // If empty, start a new JSON object
                    ofs << "{\n";
                } else {
                    // Remove the closing brace if it exists
                    size_t lastBracePos = content.find_last_of('}');
                    if (lastBracePos != std::string::npos) {
                        content.erase(lastBracePos);
                    }
                    
                    // Write the existing content without the closing brace
                    ofs << content;
                    
                    // Add a comma if there's existing content
                    //if (content.find(':') != std::string::npos) {
                        //ofs << ",\n";
                    //}
                }

                // Write new entries
                bool firstEntry = ofs.tellp() == 1;  // Check if this is the first entry after opening brace
                for (const auto& [timestamp, entries] : currentEntries) {
                    //if (!firstEntry) {
                        //ofs << ",\n";
                    //}
                    ofs << "  \"" << timestamp << "\": [\n";
                    for (size_t i = 0; i < entries.size(); ++i) {
                        ofs << "    \"" << entries[i] << "\"";
                        if (i < entries.size() - 1) {
                            ofs << ",";
                        }
                        ofs << "\n";
                    }
                    ofs << "  ]";
                    ofs << ","; 
                    firstEntry = false;
                }

                // Close the JSON object
                ofs << "\n}\n";
                ofs.close();

                // Verify that content was written
                std::ifstream verifyFile(filename);
                if (verifyFile.peek() == std::ifstream::traits_type::eof()) {
                    throw std::runtime_error("File is empty after writing: " + filename);
                }   
                return;
                /*ofs << "{\n";
                for (const auto& [timestamp, entries] : currentEntries) {
                    ofs << "  \"" << timestamp << "\": [\n";
                    for (const auto& entry : entries) {
                        ofs << "    \"" << entry << "\",\n";
                    }
                    ofs << "  ],\n";
                }
                ofs << "}\n";
                ofs.close();*/
                return;

            };
            /** -------------------------------------------------------------
             * @brief Find the current json file within the hour
             *
             * @return returns a string if there is a .json file within the hour otherwise null
             * ---------------------------------------------------------------
            */
            inline static std::string read() {
                auto now = std::chrono::system_clock::now();
                for (auto const& dir_entry : std::filesystem::directory_iterator{"logs"}) { 
                    std::string temp = dir_entry.path().stem(); // get the file names which represent a time
                    // Convert string back into time_point
                    std::tm tm = {};
                    std::istringstream ss(temp);
                    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
                    auto file_time = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                    // Minus it with a variable that was converted from string to time_point with time now to get the difference
                    auto diff = std::chrono::duration_cast<std::chrono::hours>(now - file_time);
                    // if the difference is 0, then it is within the hour and return the string
                    if (diff.count() == 0) {
                        return temp; 
                    } 
                }
                // No entry name was found
                return "\0";
            };
    };  
};
using namespace Logging;
#endif



