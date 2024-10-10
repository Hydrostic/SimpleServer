#ifndef INCLUDED_IO_BYTES
#define INCLUDED_IO_BYTES

#include <iterator>
#include <stdexcept>
#include <cstddef>
#include <optional>

namespace io{
    class bytes_error{
        public:
        class unpeakable_error: public std::exception{
            const char * what(){
                return "object not peakable";
            }
        };
    };
    class BytesIter{
        // using iter_type = std::iterator<std::input_iterator_tag, char, size_t, const size_t *, size_t>;
        public:
        virtual std::optional<char> next() = 0;
        virtual bool is_end() const = 0;         
        virtual std::optional<char> peek() const{
            throw bytes_error::unpeakable_error();
        }
    };
}

#endif