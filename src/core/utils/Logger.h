#pragma once

#include <boost/core/demangle.hpp>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

#include <ctime>

#include <chrono>

enum class LogLevel
{
    DEBUG,
    INFO,
    ERROR
};

struct ScopeInfo
{
    std::string function;
    std::string className;
    LogLevel logLevel;
    bool operator==(const ScopeInfo& other) const;
};

#define LOG_SCOPEUSE_BYCLASS(classname)                                                  \
    ScopeInfo scope = { __FUNCTION__, boost::core::demangle(typeid(classname).name()) }; \
    stringStream << scope.className << "::" << scope.function << ": ";

#define LOG_SCOPEUSE()               \
    std::ostringstream stringStream; \
    LOG_SCOPEUSE_BYCLASS(std::remove_pointer<decltype(this)>::type)

#define LOG_DEBUG(...)                                            \
    stringStream.flags(std::ios::boolalpha | std::ios::showbase); \
    stringStream << __VA_ARGS__;                    \
    Logger::log(LogLevel::DEBUG, stringStream.str())

#define LOG_ERROR(...)                                            \
    stringStream.flags(std::ios::boolalpha | std::ios::showbase); \
    stringStream << __VA_ARGS__;                    \
    Logger::log(LogLevel::ERROR, stringStream.str())

#define LOG_INFO(...)                                             \
    stringStream.flags(std::ios::boolalpha | std::ios::showbase); \
    stringStream << __VA_ARGS__;                    \
    Logger::log(LogLevel::INFO, stringStream.str());

inline std::string getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&timeNow);

    std::ostringstream oss;
    oss << std::put_time(localTime, "%d-%m-%Y %H:%M:%S");
    return oss.str();
}

class Logger
{
public:
    Logger() {}

    static void log(const LogLevel logLevel, const std::string& message)
    {
        switch (logLevel)
        {
            case LogLevel::DEBUG:
                logMessage("DEBUG", message);
                break;
            case LogLevel::INFO:
                logMessage("INFO", message);
                break;
            case LogLevel::ERROR:
                logMessage("ERROR", message);
                break;
        }
    }

private:
    static void logMessage(const std::string& level, const std::string& message)
    {
        std::cout << getCurrentTimestamp() << " [" << level << "] " << message << std::endl;
    }
};
