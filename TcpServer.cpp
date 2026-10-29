#include "TcpServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

TcpServer::TcpServer(unsigned short port, std::shared_ptr<Logger> logger) : 
    port_(port), logger_(std::move(logger)) {}

void TcpServer::start_comm_with_client(int sock_desc) {
    logger_->info("Client connected, fd = " + std::to_string(sock_desc));
    char buf[1024];
    int bytes_read;
    std::string process_res;
    while (process_res != "bye") // пока идет общение с клиентом
    {
        bytes_read = recv(sock_desc, buf, 1024, 0); // записываем сообщение в буффер
        if (bytes_read <= 0)
            break;
        process_res = cmd_processor.process_command(std::string(buf, bytes_read));
        send(sock_desc, process_res.data(), process_res.size(), 0);
        send(sock_desc, "\n", 1, 0);
    }
    close(sock_desc);
    logger_->info("Client disconnected, fd = " + std::to_string(sock_desc));
}

void TcpServer::run() {
    int sock, listener;
    sockaddr_in addr;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        throw std::runtime_error("Socket failed: " + std::string(strerror(errno)));
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_); // выбираем порт сервера
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // принимаем любой IP
    if (bind(listener, (sockaddr*)&addr, sizeof(addr)) < 0)
    {
        throw std::runtime_error("Bind failed: " + std::string(strerror(errno)));
    }
    if (listen(listener, 10) < 0)
    {
        throw std::runtime_error("Listen failed: " + std::string(strerror(errno)));
    }
    logger_->info("Server on port " + std::to_string(port_) + " is listening");
    while (1)
    {
        sock = accept(listener, NULL, NULL); // `создаем новый сокет для общения с клиентом
        if (sock < 0)
        {
            throw std::runtime_error("Accept failed: " + std::string(strerror(errno)));
        }
        std::thread t(&TcpServer::start_comm_with_client, this, sock);
        t.detach();
    }

}