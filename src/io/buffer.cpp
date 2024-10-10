#include "buffer.h"


#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cstddef>


namespace io{
    BytesBuffer::BytesBuffer(size_t initial_size){
        begin_pointer = (char*)malloc(initial_size);
        if(begin_pointer == NULL){
            throw std::bad_alloc();
        }
        write_pointer = read_pointer = begin_pointer;
        alloc_pointer = begin_pointer + initial_size;
    }
    inline bool BytesBuffer::check_availblity(size_t size_expected){
        return size_expected >= alloc_pointer - write_pointer;
    }
    void BytesBuffer::append(char c){
        if(!check_availblity(sizeof(char))) enlarge_space(sizeof(char));

        *write_pointer = c;
        write_pointer ++;
    }
    void BytesBuffer::clear(){
        read_pointer = write_pointer = begin_pointer;
    }
    inline size_t BytesBuffer::size() const {
        return write_pointer - read_pointer;
    }
    inline size_t BytesBuffer::capacity() const {
        return alloc_pointer - write_pointer;
    }
    void BytesBuffer::enlarge_space(size_t size_expected) {
        if(size_expected <= capacity()) return;
        if(size_expected > size() && size_expected > read_pointer - begin_pointer
            && size() <= read_pointer - begin_pointer){
            // then move data forward
            strncpy(begin_pointer, read_pointer, size());
            size_t forward_size = read_pointer - begin_pointer;
            write_pointer -= forward_size;
            size_expected -= forward_size;
            if(size_expected <= capacity()) return;
        }

        
        size_t newsize = alloc_pointer - begin_pointer + ((size() >> 1) >= size_expected ? (size() >> 1) : size_expected);
    
        char *new_pointer = (char*)realloc((void *)begin_pointer, newsize);
        if(new_pointer == NULL){
            throw std::bad_alloc();
        }
        if(new_pointer != begin_pointer){
            strncpy(new_pointer, read_pointer, size());
            write_pointer = write_pointer - read_pointer + new_pointer;
            read_pointer = new_pointer;
            begin_pointer = new_pointer;
        }

        alloc_pointer = new_pointer + newsize;
        

    }
    std::string BytesBuffer::to_string(){
        return std::string(read_pointer, write_pointer - read_pointer);
    } 
    
    bool BytesBuffer::iterator::is_end(){
        return inner.write_pointer <= inner.read_pointer;
    }

    std::optional<char> BytesBuffer::iterator::next(){
        std::optional<char> c = inner.read_pointer < inner.write_pointer ? std::make_optional(*inner.read_pointer) : std::nullopt;
        if(inner.read_pointer < inner.write_pointer) inner.read_pointer ++;
        return c;
    }

    std::optional<char> BytesBuffer::iterator::peek(){
        return inner.read_pointer < inner.write_pointer ? std::make_optional(*inner.read_pointer) : std::nullopt;
    }
}