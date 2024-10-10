#ifndef INCLUDED_IO_BUFFER
#define INCLUDED_IO_BUFFER

#include "io/bytes.h"
#include <cstddef>



namespace io{
    class BytesBuffer{
        public:
        static const size_t INITIAL_SIZE = 1024;
        class iterator: public BytesIter{
            std::optional<char> next();
            bool is_end();
            std::optional<char> peek();
            private:
            iterator(BytesBuffer &b): inner(b){}
            BytesBuffer &inner;
        };
        // TODO: different type overloads
        void append(char c);
        inline size_t size() const;
        inline size_t capacity() const;
        void clear();
        std::string to_string();
        BytesBuffer(size_t inital_size = INITIAL_SIZE);
        // void advance(size_t n);
        // // void shrink_to_fit();
        // void reserve(size_t n);
        // inline size_t capacity(){
        //     return cap;
        // }
        // // size_t append_from_reader(Reader& r, size_t n);
        // // size_t append_from_reader_until(Reader& r, size_t n, char c);
        // explicit BytesBuffer(size_t size);

        // size_t read_n_till(char *dest, size_t n, char c);
        private:
        inline bool check_availblity(size_t size_expected);
        void enlarge_space(size_t size_expected);
        char *begin_pointer;
        char *read_pointer;
        char *write_pointer;
        char *alloc_pointer;
        /*
            +-------------+ begin_pointer
            |read area    |
            +-------------+ read_pointer(unread)
            |unread area  |
            +-------------+ write_pointer(unwritten)
            |writable area|
            +-------------+ alloc_pointer(unalloc)

        */
    };
}

#endif
