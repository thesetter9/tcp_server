#pragma once

#include <string>

class Logger
{
private:
    void log(const std::string& level, const std::string& message);
public:
    void info(const std::string& message);
    void error(const std::string& message);
};