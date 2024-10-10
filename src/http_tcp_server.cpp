#include "http_tcp_server.h"
#include "utils/io_wrapper.h"
#include "protocol/http/http.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <spdlog/spdlog.h>
#include <errno.h>

using std::string;


namespace http{
    
    TcpServer::TcpServer(string ip_address, int port): 
        m_ip_address(ip_address), m_socket(), mPort(port), mAddress(), m_address_len(sizeof(mAddress)), max_capacity(DEFAULT_MAX_CAPACITY){
        spdlog::set_level(spdlog::level::debug);
        mAddress.sin_family = AF_INET, mAddress.sin_port = htons(mPort);
        mAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
    }
    int TcpServer::start(){
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(m_socket < 0){
            throw std::system_error(errno, std::system_category(), "unable to create socket");
        }
        // std::memset(&mAddress, 0, sizeof(mAddress));
        
        int mBind = bind(m_socket, (sockaddr*)&mAddress, m_address_len);
        if(mBind < 0){
            throw std::system_error(errno, std::system_category(), "unable to bind");
        }
        return 0;
    }
    int TcpServer::listen_on(){
        if(listen(m_socket, max_capacity) < 0){
            throw std::system_error(errno, std::system_category(), "unable to listen");
        }
        spdlog::info("listening on {}:{}", m_ip_address, mPort);
        
        sockaddr_in clientAddress{};
        unsigned len = sizeof(clientAddress);
        while(true){

            int acceptFd = accept(m_socket, (sockaddr *)&clientAddress, &len);
            spdlog::debug("new conn from {}:{}", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
            if(acceptFd < 0){
                spdlog::error("accept error: {}", std::system_error(errno, std::system_category()).what());
                continue;
            }
            try{
                
                TcpServer::read_request(acceptFd);
            }catch(http_exception &e){
                
            }

            close(acceptFd);
        }

    }
    void TcpServer::read_request(int sockfd){
        // auto req = http::HttpRequest();
        // auto r = HttpReader(sockfd);
        // try{

        //     req.get_header_from_reader(r);
        // }catch(http_exception &e){
        //     throw e;
        // }catch(std::system_error &e){
        //     spdlog::error("failed to obtain header\nCause: {}", e.what());
        //     throw http_exception(HttpStatusCode::INTERNAL_SERVER_ERROR);
        // }
    }
    TcpServer::~TcpServer(){
        // TODO: close all connection
        close(m_socket);
    }
    
    size_t HttpReader::read_n_bytes(char *dest, size_t n){
        ssize_t bytes_read = read(fd, dest, n);
        if(bytes_read < 0){
            throw std::system_error(errno, std::system_category());
        }
        return bytes_read;

    }
}