#include "Logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <format>

void Logger::log(const std::string& level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    std::cout << std::format("[{:%F %T}] [{}] {}", now, level, message) << std::endl; // использую std::format
}

void Logger::info(const std::string& message) {
    log("INFO", message);
}
void Logger::error(const std::string& message) {
    log("ERROR", message);
}