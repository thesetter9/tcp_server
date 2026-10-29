#include "CommandProcessor.h"
#include <ranges>
#include <algorithm>
#include <format>
#include <chrono>
#include <iostream>


std::string str_to_lower(const std::string& str) // не копирую чтобы не испортить строку
{
    auto res = str;
    std::ranges::transform(res, res.begin(), [](unsigned char c) { return tolower(c); });
    return res;
}

std::string CommandProcessor::process_command(const std::string& message) const
{

    std::string line = message;
    while (!line.empty() && (line.back() == '\n' || line.back() == '\r'))
        line.pop_back();
    std::string str = str_to_lower(line);
    if (str == "ping")
        return "pong";
    else if (str == "time")
    {
        auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
        return std::format("{:%F %T}", now);
    }
    else if (str.rfind("echo ", 0) == 0)
        return line.substr(5);
    else if (str == "quit")
        return "bye";
    else
        return "unknown command";
}