#include "TcpServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

bool TcpServer::send_all(int sock_desc, const std::string &message)
{
    size_t sent = 0;
    while (sent < message.size())
    {
        ssize_t n = send(sock_desc, message.data() + sent, message.size() - sent, MSG_NOSIGNAL); // MSG_NOSIGNAL - не убиваем процесс при SIGPIPE
        if (n < 0 && errno == EINTR)
            continue;
        if (n <= 0)
            return false;
        sent += static_cast<size_t>(sent);
    }
    return true;
}

TcpServer::TcpServer(unsigned short port, std::shared_ptr<Logger> logger) : port_(port), logger_(std::move(logger)) {}

void TcpServer::start_comm_with_client(int sock_desc)
{
    logger_->info("Client connected, fd = " + std::to_string(sock_desc));
    constexpr size_t max_line_size = 4096;
    constexpr size_t buf_size = 1024;
    char buf[buf_size];
    std::string process_res;
    bool flag = true;
    while (flag)
    {
        ssize_t n = recv(sock_desc, buf, buf_size, 0);
        if (n <= 0)
            break;
        process_res.append(buf, static_cast<size_t>(n));
        size_t pos;
        while (flag && (pos = process_res.find('\n')) != std::string::npos)
        {
            std::string cur_line = process_res.substr(0, pos);
            process_res.erase(0, pos + 1);
            std::string reply = cmd_processor.process_command(cur_line) + "\n";
            if (!send_all(sock_desc, reply))
            {
                flag = false;
                break;
            }
            if (reply == "bye")
                break;
        }
        if (process_res.size() > max_line_size)
            break;
    }
    close(sock_desc);
    logger_->info("Client disconnected, fd = " + std::to_string(sock_desc));
}

void TcpServer::run()
{
    int sock, listener;
    sockaddr_in addr;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0)
    {
        throw std::runtime_error("Socket failed: " + std::string(strerror(errno)));
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);             // выбираем порт сервера
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // принимаем любой IP
    int yes = 1;
    setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
    if (bind(listener, (sockaddr *)&addr, sizeof(addr)) < 0)
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