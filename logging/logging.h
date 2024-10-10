#pragma once
#ifndef _LOGGING_H_
#define _LOGGING_H_
#include <interface.h>
#if ENABLE_LOGGING_TEST
    logTable<Map<String, Vector<String>>> logEntries;
#endif
namespace Logging {
    template<class T>
    class logging {
        public:
            logging() = default;
            logging<T>(const logTable<Map<String, Vector<String>>>& old_logs, const String& text): currentEntries(logEntries) {
                this->text = text;
            };
            ~logging() noexcept = default;
            static String getCurrentTimeString();
            static void rotate();             
            static void update();             
            static bool write();
            void printLogs();
            static String getText() {
                return text;
            };
            inline Map<String, Vector<String>> getLogs() { return currentEntries; };
        private:
            logTable<Map<String, Vector<String>>> currentEntries;
            static String text;
            static void create(String& filename);
            static String read();

    };  
};
using namespace Logging;
#include <logging.cc>
#include <run_time_error.h>
#endif



