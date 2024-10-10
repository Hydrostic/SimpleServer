#include "parse.h"
#include "kinds.h"
#include <optional>
#include <cstddef>

using io::Decoder, io::BytesIter, io::BytesBuffer;
using http_protocol_exception = http::http_protocol_exception;

inline std::optional<size_t> read_to_until(BytesIter &src, BytesBuffer &dest, char target, size_t max_read_size){
    if(dest.size() > http::parse::MAX_BUFFER_SIZE){
        throw http_protocol_exception(http_protocol_exception::category::HEAD_READ_ERROR, "buffer size over restriction");
    }
    size_t readed_size = dest.size();
    while(max_read_size-- && src.is_end()){
        if(src.peek().value() == target){
            return std::optional<size_t>(readed_size);
        }
        dest.append(src.next().value());
    }
    if(max_read_size == 0){
        throw http_protocol_exception(http_protocol_exception::category::HEAD_READ_ERROR, "current buffer size over max read size");
    }
    return std::nullopt;
}
template<typename T, typename F>
inline bool read_if_uninit(BytesIter &src, BytesBuffer &dest, std::optional<T> &source, size_t max_size, F && generator){
    if(!source.has_value()){
        auto readed_size = read_to_until(src, dest, ' ', max_size);
        if(!readed_size.has_value()) return false;
        source = std::make_optional(generator(dest.to_string()));
    }
    return true;
}
namespace http{
    namespace parse{
        // @brief parse http head data from bytes iterator
        // 
        // @param b: 
        // @return 
        std::optional<MaybeUninitHttpHead> HttpHeadParser::decode(BytesIter &b){
            // the bytes iter here is considered as a memory buffer, so there is no need to extract lots of data to improve the performance of decode
            if(!read_if_uninit(b, cur, data.method, 10, 
            [](string_view tmp){ return HttpMethod(tmp); })){
                return std::nullopt;
            }
            cur.clear();b.next();
            if(!read_if_uninit(b, cur, data.uri, 2048, 
            [](string_view tmp){ return HttpUri::from_str(tmp); })){
                return std::nullopt;
            }
            cur.clear();b.next();
            if(!read_if_uninit(b, cur, data.version, 10, 
            [](string_view tmp){ return HttpVersion(tmp); })){
                return std::nullopt;
            }
            cur.clear();
            return std::nullopt;
        }
    }
}