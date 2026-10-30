#pragma once
#include "Logger.h"
#include <memory>
#include <thread>
#include "CommandProcessor.h"

class TcpServer
{
private:
    unsigned short port_;
    void start_comm_with_client(int sock_desc);
    std::shared_ptr<Logger> logger_;
    CommandProcessor cmd_processor;
    static bool send_all(int sock_desc, const std::string& message);
    

public:
    TcpServer(unsigned short port, std::shared_ptr<Logger> logger);
    void run();
};