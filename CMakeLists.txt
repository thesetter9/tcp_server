cmake_minimum_required(VERSION 3.16)
project(tcp-server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server main.cpp Logger.cpp TcpServer.cpp)
