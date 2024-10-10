#ifndef INCLUDED_HTTP_PARSE
#define INCLUDED_HTTP_PARSE

#include "kinds.h"
#include "io/decoder.h"
#include "io/bytes.h"
#include "io/buffer.h"
#include <optional>
#include <cstddef>

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
namespace http{
    namespace parse{
        using io::Decoder, io::BytesIter, io::BytesBuffer; 
        const size_t MAX_BUFFER_SIZE = 1024 * 1024;
        class MaybeUninitHttpHead{
            public:
            MaybeUninitHttpHead(): method(), uri(), version(){

            }
            std::optional<HttpMethod> method;
            std::optional<HttpUri> uri;
            std::optional<HttpVersion> version;
            
        };

        class HttpHeadParser: public io::Decoder<MaybeUninitHttpHead>{
            public:
            std::optional<MaybeUninitHttpHead> decode(BytesIter &b);
            private:
            MaybeUninitHttpHead data;
            BytesBuffer cur;
            
        };


    }
}


#endif