#ifndef INCLUDED_IO_WRAPPER
#define INCLUDED_IO_WRAPPER

#include<cstddef>

namespace utils{
    class Reader{
        public:
        virtual size_t read_n_bytes(char *dest, size_t n) = 0;
    };

    class Writer{
        public:
        virtual size_t write_n_bytes(char *src, size_t n) = 0;
    };
}

#endif