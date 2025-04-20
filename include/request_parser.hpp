#ifndef REQUEST_PARSER_HPP
#define REQUEST_PARSER_HPP

#include <string>

struct HttpRequest {
    std::string method;
    std::string path;
    bool valid;
};

HttpRequest parse_request(const std::string& raw_request);

#endif
