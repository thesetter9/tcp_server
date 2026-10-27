#pragma once
#include "Logger.h"
#include <memory>
#include <thread>

class TcpServer
{
private:
    unsigned short port_;
    static void start_comm_with_client(int sock_desc, std::unique_ptr<Logger>& logger);

public:
    void run(std::unique_ptr<Logger>& logger, unsigned short port = 8080);
};