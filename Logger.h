#pragma once

#include <string>
#include <mutex>

class Logger
{
private:
    void log(const std::string& level, const std::string& message);
    std::mutex mutex_;

public:
    void info(const std::string& message);
    void error(const std::string& message);
};