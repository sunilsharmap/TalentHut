#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL, FATAL };

class Logger {
private:
    /**
     * @brief filename_ is the logger log file name
     */
    string filename_;

    /**
     * @brief logLevel_ is the logger log level
     */
    LogLevel logLevel_;

    /**
     * @brief Logger writer of level `loglevel_` to filename `filename_` with date time and log level indication
     * ex: [2025-02-24 10:46:13] [I] Info level logging at line 6
     *     [timestamp] [Level] <message>
     * @param[IN] level
     * @param[IN] format
     * @param[IN] args
     */
    void log(LogLevel level, const char *format, va_list args) {
        if (logLevel_ > level) {
            return;
        } else {
            FILE *file = fopen(filename_.c_str(), "a");
            if (file) {
                auto now = chrono::system_clock::now();
                auto now_c = chrono::system_clock::to_time_t(now);
                stringstream ss;
                ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
                string timestamp = ss.str();

                fprintf(file, "[%s] ", timestamp.c_str());

                switch (level) {
                case LogLevel::DEBUG:
                    fprintf(file, "%s", "[D] ");
                    break;
                case LogLevel::INFO:
                    fprintf(file, "%s", "[I] ");
                    break;
                case LogLevel::WARNING:
                    fprintf(file, "%s", "[W] ");
                    break;
                case LogLevel::ERROR:
                    fprintf(file, "%s", "[E] ");
                    break;
                case LogLevel::CRITICAL:
                    fprintf(file, "%s", "[C] ");
                    break;
                case LogLevel::FATAL:
                    fprintf(file, "%s", "[F] ");
                    break;
                }

                vfprintf(file, format, args);
                fprintf(file, "%c", '\n');
                fclose(file);
            }
        }
    }

public:
    /**
     * @brief Logger Constructor with default filename and loglevel. You can not
     * change the log file name later, but loglevel can be changed any time using
     * SetLogLevel()
     *
     * @param[IN] filename
     * @param[IN] level
     */
    Logger(string filename = "loggerLog.log",
           LogLevel level = LogLevel::WARNING) {
        filename_ = filename;
        logLevel_ = level;
        FILE *file = fopen(filename_.c_str(), "a");
        if (file) {
            auto now = chrono::system_clock::now();
            auto now_c = chrono::system_clock::to_time_t(now);
            stringstream ss;
            ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
            string timestamp = ss.str();

            fprintf(file, "\n---------- [%s] ----------\n", timestamp.c_str());
            fclose(file);
        } else {
            cerr << "Error: Could not open log file: " << filename_ << endl;
        }
    }

    /**
     * @brief GetLogLevel will return the loglevel string
     * @return loglevel string
     */
    string GetLogLevel(void) {
        switch (logLevel_) {
        case LogLevel::DEBUG:
            return "DEBUG";
            break;
        case LogLevel::INFO:
            return "INFO";
            break;
        case LogLevel::WARNING:
            return "WARNING";
            break;
        case LogLevel::ERROR:
            return "ERROR";
            break;
        case LogLevel::CRITICAL:
            return "CRITICAL";
            break;
        case LogLevel::FATAL:
            return "FATAL";
            break;
        }
    }

    /**
     * @brief SetLogLevel will set the Logger log level
     * @param level of the log from LogLevel enum
     */
    inline void SetLogLevel(LogLevel level) { logLevel_ = level; }

    /**
     * @brief GetLogFileName will return the logfile name set in the constructor
     * @return logfile name set in the constructor
     */
    inline string GetLogFileName(void) { return filename_; }

#define LOG(level)                                                             \
    va_list args;                                                              \
    va_start(args, format);                                                    \
    log(level, format, args);                                                  \
    va_end(args);

    /**
     * @brief debug API to document debug level logging
     * @param format printf() kind of message
     */
    inline void debug(const char *format, ...) { LOG(LogLevel::DEBUG); }

    /**
     * @brief info API to document info level logging
     * @param format printf() kind of message
     */
    inline void info(const char *format, ...) { LOG(LogLevel::INFO); }

    /**
     * @brief warn API to document warning level logging
     * @param format printf() kind of message
     */
    inline void warn(const char *format, ...) { LOG(LogLevel::WARNING); }

    /**
     * @brief error API to document error level logging
     * @param format printf() kind of message
     */
    inline void error(const char *format, ...) { LOG(LogLevel::ERROR); }

    /**
     * @brief crit API to document critical level logging
     * @param format printf() kind of message
     */
    inline void crit(const char *format, ...) { LOG(LogLevel::CRITICAL); }

    /**
     * @brief fatal API to document fatal level logging
     * @param format printf() kind of message
     */
    inline void fatal(const char *format, ...) { LOG(LogLevel::FATAL); }
};
