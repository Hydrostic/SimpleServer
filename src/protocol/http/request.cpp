#include "request.h"
#include "spdlog/spdlog.h"

#include <stdexcept>


namespace http{

    // void HttpRequest::get_head_from(Reader &r){
    //     auto meta = HttpRequestMeta();
    //     // buf.append_from_reader_until(r, 2066);
    //     // parse request line
    //     // method(<=7) + space + path(<=2048) + space + http_version(8)
    //     char method[8];
    //     buf.read_n_till(method, 7, ' ');
    //     meta.method = get_method_from_str(method);
    //     if(meta.method == HttpMethod::UNKNOWN){
    //         throw http_exception(HttpStatusCode::BAD_REQUEST);
    //     }
    //     char path[2048] = {0};
    //     buf.advance(1);
    //     // buf.read_n_till(path, 2048, ' ');
    //     spdlog::debug("{} {}", method, path);
    //     // 
    // }
}
