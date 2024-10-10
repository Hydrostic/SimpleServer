#ifndef INCLUDED_HTTP_RESPONSE
#define INCLUDED_HTTP_RESPONSE

#include "utils/io_wrapper.h"
namespace http{
    class HttpResponse{
        public:
        HttpResponse(){

        }
        void send_by_writer();
        // private:
        
    };
}
#endif