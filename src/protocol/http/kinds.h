#ifndef INCLUDED_HTTP_kinds
#define INCLUDED_HTTP_kinds

#include "status_code.h"
#include <stdexcept>
#include <string>
using std::string_view;
using std::string;
namespace http{
    using _http_status_code::HttpStatusCode;
    class HttpMethod{
        public:
        enum class method{
            CONNECT,
            GET,
            POST,
            PUT,
            DELETE,
            HEAD,
            OPTIONS,
            PATCH,
            TRACE,
            UNKNOWN
        };
        explicit HttpMethod(string_view method_str);
        private:
        method inner;
    };
    
    class HttpVersion{
        public:
        enum class version{
            HTTP1_0,
            HTTP1_1
        };
        explicit HttpVersion(string_view version_str);
        private:
        version inner;
    };

    class HttpUri{
        public:
        const string& get_raw(){
            return inner;
        }
        HttpUri() = delete;
        static HttpUri from_str_unchecked(string_view uri_str);
        static HttpUri from_str(string_view uri_str);
        private:
        HttpUri(string _inner): inner(_inner){}
        // -, ., _, ~, !, $, &, ', (, ), *, +, ,, ;, =, :, @
        inline static bool check_valid_sign(char c){
            switch (c){
            case '-':
            case '.':
            case '_':
            case '~':
            case '!':
            case '$':
            case '&':
            case '\'':
            case '(':
            case ')':
            case '*':
            case '+':
            case ',':
            case ';':
            case '=':
            case ':':
            case '@':
                return true;
            default:
                return false;
            }
        }
        string inner;
    };
    class http_exception: public std::exception{
        public:
        const char* what() const throw() {
            return "My custom exception";
        }
        http_exception(HttpStatusCode _status_code): status_code(_status_code){

        }
        private:
        HttpStatusCode status_code;
        string reason;
    };
    class http_protocol_exception: public std::exception{
        public:
        enum class category{
            HEAD_READ_ERROR,
            INVALID_URI,
            VERSIOH_UNIMPLEMENTED

        };
        category c;
        string reason;
        http_protocol_exception(category _c, string _reason): c(_c), reason(_reason){} 
    };

}
#endif