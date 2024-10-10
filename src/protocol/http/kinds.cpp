#include "kinds.h"

#include <cstring>
#include <cctype>
#include <fmt/core.h>

using std::string_view;
using std::string;
namespace http{
    HttpMethod::HttpMethod(string_view method_str){
        if(method_str == "GET"){
            inner = method::GET;
        }else if(method_str == "POST"){
            inner = method::POST;
        }else if(method_str == "PUT"){
            inner = method::PUT;
        }else if(method_str == "DELETE"){
            inner = method::DELETE;
        }else if(method_str == "PATCH"){
            inner = method::PATCH;
        }else if(method_str == "HEAD"){
            inner = method::HEAD;
        }else if(method_str == "OPTIONS"){
            inner = method::OPTIONS;
        }else{
            inner = method::UNKNOWN;
        }
    }

    HttpVersion::HttpVersion(string_view version_str){
        if(version_str == "HTTP/1.0"){
            inner = version::HTTP1_0;
        }else if(version_str == "HTTP/1.1"){
            inner = version::HTTP1_1;
        }else{
            throw http_protocol_exception(http_protocol_exception::category::VERSIOH_UNIMPLEMENTED, fmt::format("{} unimplemented", version_str));
        }
    }
    HttpUri HttpUri::from_str_unchecked(string_view uri_str){
        return {string(uri_str)};
    }

    HttpUri HttpUri::from_str(string_view uri_str){
        auto old = uri_str.begin(), p = uri_str.begin();
        HttpUri uri = {string()};
        uri.inner.reserve(uri_str.size());
        while(p != uri_str.begin()){
            char c = *p;
            if(c == '%'){
                auto s1 = p + 1, s2 = p + 2;
                if(s1 != uri_str.end() && s2 != uri_str.end() && isdigit(*s1) && isdigit(*s2)){
                    uri.inner.push_back(((*s1 - '0') << 4) + (*s2 - '0'));
                    p += 2;
                    continue;
                }else{
                    throw http_protocol_exception(http_protocol_exception::category::INVALID_URI, fmt::format("percentage-encoding at index {} invalid", p - old));
                }
            }
            if(!(isalpha(c) || isdigit(c) || check_valid_sign(c))){
                throw http_protocol_exception(http_protocol_exception::category::INVALID_URI, fmt::format("character {} at index {} invalid", c, p - old));
            }
            uri.inner.push_back(c);
            p ++;
        }
        return uri;
    }
}