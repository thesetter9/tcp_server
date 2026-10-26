#pragma once
#include "Logger.h"
#include <memory>

class TcpServer
{
private:
    unsigned short port_;
public:
    void run(std::unique_ptr<Logger>& logger, unsigned short port = 8080);
};