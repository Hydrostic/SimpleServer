#ifndef INCLUDED_HTTP_MESSAGE
#define INCLUDED_HTTP_MESSAGE 

#include "kinds.h"

using http::HttpMethod, http::HttpVersion;
class HttpHead{
    HttpVersion version;
    HttpMethod method;
    
};

#endif