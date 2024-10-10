#ifndef INCLUDED_IO_DECODER
#define INCLUDED_IO_DECODER

#include <optional>

namespace io{
    template<typename T>
    class Decoder{
        virtual std::optional<T> decode() = 0;
    };
}
#endif
