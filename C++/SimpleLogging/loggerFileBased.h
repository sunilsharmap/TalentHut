#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>

#ifdef _WIN32
#define pathsep = '\\';
#elif
#define pathsep = '/'
#endif

using namespace std;

class LoggerFileBased {
private:
    /**
     * @brief filename_ is the logger log file name
     */
    string filename_;

    /**
     * @brief Logger writer of level `loglevel_` to filename `filename_` with date time and log level indication
     * ex: [2025-02-24 10:46:13] [I] Info level logging at line 6
     *     [timestamp] [Level] <message>
     * @param[IN] level
     * @param[IN] format
     * @param[IN] args
     */
    void log(string level, const char *format, va_list args) {
        // Check level file exist, then only log the level logs to the logger
        filesystem::path path(filename_);
        string _dirName = path.parent_path().string();
        filesystem::path _levelfile(level);
        _levelfile = _dirName / _levelfile;
        if (!filesystem::exists(_levelfile)) {
            // level file not exist, dont log
            return;
        }

        FILE *file = fopen(filename_.c_str(), "a");
        if (file) {
            auto now = chrono::system_clock::now();
            auto now_c = chrono::system_clock::to_time_t(now);
            stringstream ss;
            ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
            string timestamp = ss.str();

            fprintf(file, "[%s] ", timestamp.c_str());
            string level_str = "";
            if (level.compare("DEBUG") == 0)
                level_str = "[D] ";
            else if (level.compare("INFO") == 0)
                level_str = "[I] ";
            else if (level.compare("WARN") == 0)
                level_str = "[W] ";
            else if (level.compare("ERROR") == 0)
                level_str = "[E] ";
            else if (level.compare("CRITICAL") == 0)
                level_str = "[C] ";
            else if (level.compare("FATAL") == 0)
                level_str = "[F] ";
            fprintf(file, "%s", level_str.c_str());

            vfprintf(file, format, args);
            fprintf(file, "%c", '\n');
            fclose(file);
        }
    }

public:
    LoggerFileBased(){}
    ~LoggerFileBased(){}

    /**
     * @brief Logger Constructor with default filename and loglevel. You can not
     * change the log file name later, but loglevel can be changed any time using
     * SetLogLevel()
     *
     * @param[IN] filename
     * @param[IN] level
     */
    void LoggerInit(string filename="loggerLog.log") {
        filesystem::path path(filename);
        string _dirName = path.parent_path().string();
        string _filename = "";
        if (_dirName.empty()) {
            _dirName = filesystem::current_path().string();
            _filename = (_dirName / path).string();
        }
        if (_filename.empty()) {
            filename_ = (_dirName / path).string();
        } else {
            filename_ = _filename;
        }

        FILE *file = fopen(filename_.c_str(), "a");
        if (file) {
            auto now = chrono::system_clock::now();
            auto now_c = chrono::system_clock::to_time_t(now);
            stringstream ss;
            ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
            string timestamp = ss.str();
            fprintf(file, "---------- [%s] ----------\n", timestamp.c_str());
            fclose(file);
        } else {
            cerr << "Error: Could not open log file: " << filename_ << endl;
        }
    }

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
    inline void debug(const char *format, ...) { LOG("DEBUG"); }

    /**
     * @brief info API to document info level logging
     * @param format printf() kind of message
     */
    inline void info(const char *format, ...) { LOG("INFO"); }

    /**
     * @brief warn API to document warning level logging
     * @param format printf() kind of message
     */
    inline void warn(const char *format, ...) { LOG("WARN"); }

    /**
     * @brief error API to document error level logging
     * @param format printf() kind of message
     */
    inline void error(const char *format, ...) { LOG("ERROR"); }

    /**
     * @brief crit API to document critical level logging
     * @param format printf() kind of message
     */
    inline void crit(const char *format, ...) { LOG("CRITICAL"); }

    /**
     * @brief fatal API to document fatal level logging
     * @param format printf() kind of message
     */
    inline void fatal(const char *format, ...) { LOG("FATAL"); }
};
