#pragma once
#include <string>
#include <chrono>
#include <iomanip>

class CommandProcessor
{
public:
    std::string process_command(const std::string& message) const;
};
