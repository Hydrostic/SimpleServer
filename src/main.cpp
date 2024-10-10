#include "http_tcp_server.h"
#include "spdlog/spdlog.h"
#include <stdexcept>
#include <string>
#include <iostream>


int main(){
    try{
        auto server = http::TcpServer(std::string("127.0.0.1"), 7001);
        server.start();
        server.listen_on();
    }catch(std::exception &e){
        spdlog::critical("{}", e.what());
    }
}