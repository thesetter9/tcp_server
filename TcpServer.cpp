#include "TcpServer.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

void TcpServer::run(std::unique_ptr<Logger>& logger, unsigned short port) {
    int sock, listener;
    sockaddr_in addr;
    char buf[1024];
    int bytes_read;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        throw std::runtime_error("Socket failed: " + std::string(strerror(errno)));
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port); // выбираем порт сервера
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // принимаем любой IP
    if (bind(listener, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        throw std::runtime_error("Bind failed: " + std::string(strerror(errno)));
    }
    this->port_ = port;
    if (listen(listener, 10) < 0)
    {
        throw std::runtime_error("Listen failed: " + std::string(strerror(errno)));
    }
    logger->info("Server on port " + std::to_string(port_) + " is listening");
    while (1)
    {
        sock = accept(listener, NULL, NULL); // создаем новый сокет для общения с клиентом
        if (sock < 0)
        {
            throw std::runtime_error("Accept failed: " + std::string(strerror(errno)));
        }
        while (1) // пока идет общение с клиентом
        {
            bytes_read = recv(sock, buf, 1024, 0); // записываем сообщение в буффер
            if (bytes_read <= 0)
                break;
            send(sock, buf, bytes_read, 0); // возвращаем его же клиенту
        }
        close(sock);
    }
}