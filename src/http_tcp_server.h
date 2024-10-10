#ifndef INCLUDED_HTTP_TCP_SERVER
#define INCLUDED_HTTP_TCP_SERVER

#include <netinet/in.h>
#include <string>
#include <cstddef>

#include "utils/io_wrapper.h"

using utils::Reader;
using std::string;

namespace http{
    const int DEFAULT_MAX_CAPACITY = 100;
    const int BUFFER_SIZE = 65535;
    class TcpServer{
        public:
        TcpServer(string ip_address, int port);
        ~TcpServer();
        int start();
        void set_max_capacity(int capacity){
            max_capacity = capacity;
        }
        int listen_on();
        void read_request(int sock);
        private:
        int m_socket;
        string m_ip_address;
        int mPort;
        sockaddr_in mAddress;
        unsigned int m_address_len;
        int max_capacity;
    };

    class HttpReader: public Reader{
        public:
        size_t read_n_bytes(char *dest, size_t n);
        HttpReader(int _fd): fd(_fd){}
        private:
        int fd;
    };
}
#endif