#include "Logger.h"
#include "TcpServer.h"
#include <memory>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    try
    {
        
        if (argc < 2)
            throw std::runtime_error("Write a port of server");
        else {
            unsigned long value = std::stoul(argv[1]);
            if (value < 1024 || value > 65535)
                throw std::runtime_error("Port must be in 1..65535, got " + std::string(argv[1]));
            unsigned short port = static_cast<unsigned short>(value);
            auto logger = std::make_shared<Logger>();
            auto server = std::make_unique<TcpServer>(port, logger);
            server->run();
        }
        
    }
    catch (const std::exception& exp)
    {
        std::cerr << "fatal: " << exp.what() << std::endl;
        return 1;
    }
}