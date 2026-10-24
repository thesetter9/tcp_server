#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>

void Logger::log(const std::string& level, const std::string& message) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[" << std::put_time(std::localtime(&now_c), "%F %T") << "] [" << level << "] " << message << std::endl;
}
void Logger::info(const std::string& message) {
    log("INFO", message);
}
void Logger::error(const std::string& message) {
    log("ERROR", message);
}