#include "Logger.h"
#include "TcpServer.h"
#include <memory>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    try
    {
        auto logger = std::make_unique<Logger>();
        auto server = std::make_unique<TcpServer>();
        if (argc < 2)
            server->run(logger); // берем порт по умолч. = 8080
        else {
            unsigned long value = std::stoul(argv[1]);
            if (value < 1024 || value > 65535)
                throw std::runtime_error("Port must be in 1..65535, got " + std::string(argv[1]));
            unsigned short port = static_cast<unsigned short>(value);
            server->run(logger, port);
        }
    }
    catch (const std::exception& exp)
    {
        std::cerr << "fatal: " << exp.what() << std::endl;
        return 1;
    }
}