/*
    Reference: https://github.com/danielblagy/Yelloger/tree/master

    This is a `Singleton` header only, thread safe logger can be used for logging. Go through
    Quick Start to know how to use it

    ********************
    QUICK START
    ********************

    Logger doesn't need to be instantiated, just include the header and use it like this
        Logger::Info("Infotmation %d", int_value);

    No need to put newline character at the end of the message, it will be done automatically

    To enable console output, call below one before using the logger
        Logger::EnableConsoleOutput();

    To enable file output, call below one before using the logger
        Logger::EnableFileOutput("mylogpath/mylog.txt");

    Optionally, you can provide no path like below then, the logs will be saved in './logger.log'
        Logger::EnableFileOutput();

    The default log priority is LogLevel::eInfo

    You can set priority by calling like below with required LogLevel
        Logger::SetPriority(LogLevel::eDebug);

    Possible values:
        LogLevel::eTrace
        LogLevel::eDebug
        LogLevel::eInfo
        LogLevel::eWarn
        LogLevel::eError
        LogLevel::eCritical

    You can get priority by calling
        Logger::GetPriority();

    To log:
        Logger::Trace(const char* message, Args... args)	// [T] log a message with trace priority
        Logger::Debug(const char* message, Args... args)	// [D] log a message with debug priority
        Logger::Info(const char* message, Args... args)		// [I] log a message with info priority
        Logger::Warn(const char* message, Args... args)		// [W] log a message with warn priority
        Logger::Error(const char* message, Args... args)	// [E] log a message with error priority
        Logger::Critical(const char* message, Args... args)	// [C] log a message with critical priority

        As args you can provide primitives and C-strings. Formatting follows printf format.

    ********************
    SIMPLE EXAMPLE
    ********************

    #include <logger.hpp>
    int main()
    {
        const char* name = "User";
        Logger::EnableConsoleOutput();
        Logger::Info("Hello %s", name);

        return 0;
    }

    Output:
    [2025-03-05 18:14:51] [I] Hello User
    [<date> <time>] [LogLevel] <printf type message>
*/

#pragma once

#include <chrono>
#include <cstdarg>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <stdio.h>

using namespace std;

// xx(EnumValue, EnumName)
#define LOGLEVEL(xx)        \
xx(eTrace, "TRACE")         \
xx(eDebug, "DEBUG")         \
xx(eInfo, "INFO")           \
xx(eWarn, "WARNING")        \
xx(eError, "ERROR")         \
xx(eCritical, "CRITICAL")

#define enum_type(value, name) value,
typedef enum { LOGLEVEL(enum_type) } LogLevel;
#undef enum_type

class Logger {
private:
    FILE *file_ = 0;
    std::mutex log_mutex_;
    bool console_ = false;
    const char *filepath_ = 0;
    LogLevel level_ = eInfo;

public:

#define switch_case(value, name)  \
    case value:                  \
        return name;

    static const char* GetLogLevel()
    {
        switch (get_instance().level_) {
            LOGLEVEL(switch_case)
        default:
            return "UNKNOWN";
        }
    }
#undef switch_case

    static void SetLogLevel(LogLevel level) {
        get_instance().level_ = level;
    }

    static void EnableConsoleOutput() {
        Logger &logger_instance = get_instance();
        logger_instance.console_ = true;
    }

    static void EnableFileOutput() {
        Logger &logger_instance = get_instance();
        logger_instance.filepath_ = "logger.log";
        logger_instance.enable_file_output();
    }

    static void EnableFileOutput(const char *new_filepath) {
        Logger &logger_instance = get_instance();
        logger_instance.filepath_ = new_filepath;
        logger_instance.enable_file_output();
    }

    template <typename... Args>
    static void Trace(const char *message, Args... args) {
        get_instance().log("[T] ", eTrace, message, args...);
    }

    template <typename... Args>
    static void Debug(const char *message, Args... args) {
        get_instance().log("[D] ", eDebug, message, args...);
    }

    template <typename... Args>
    static void Info(const char *message, Args... args) {
        get_instance().log("[I] ", eInfo, message, args...);
    }

    template <typename... Args>
    static void Warn(const char *message, Args... args) {
        get_instance().log("[W] ", eWarn, message, args...);
    }

    template <typename... Args>
    static void Error(const char *message, Args... args) {
        get_instance().log("[E] ", eError, message, args...);
    }

    template <typename... Args>
    static void Critical(const char *message, Args... args) {
        get_instance().log("[C] ", eCritical, message, args...);
    }

private:
    Logger() {}
    ~Logger() { free_file(); }
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    static Logger &get_instance() {
        static Logger logger;
        return logger;
    }

    template <typename... Args>
    void log(const char *message_priority_str, LogLevel message_priority,
             const char *message, Args... args) {
        if (level_ <= message_priority) {
            auto now = chrono::system_clock::now();
            auto now_c = chrono::system_clock::to_time_t(now);
            stringstream ss;
            ss << put_time(localtime(&now_c), "%Y-%m-%d %H:%M:%S");
            string timestamp = ss.str();

            std::scoped_lock lock(log_mutex_);
            if (console_) {
                printf("[%s] ", timestamp.c_str());
                printf(message_priority_str);
                printf(message, args...);
                printf("\n");
            }
            if (file_) {
                fprintf(file_, "[%s] ", timestamp.c_str());
                fprintf(file_, message_priority_str);
                fprintf(file_, message, args...);
                fprintf(file_, "\n");
            }
        }
    }

    bool enable_file_output() {
        free_file();
        file_ = fopen(filepath_, "a");
        if (file_ == 0) {
            return false;
        }
        return true;
    }

    void free_file() {
        if (file_) {
            fclose(file_);
            file_ = 0;
        }
    }
};
