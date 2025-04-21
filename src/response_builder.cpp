#include "response_builder.hpp"
#include <fstream>
#include <string>

std::string build_response(const std::string& method, const std::string& file_path, int& status_code) {
    std::ifstream file(file_path, std::ios::binary);
    std::string response;

    if (file) {
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        response  = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Content-Length: " + std::to_string(content.size()) + "\r\n";
        response += "\r\n";
        if (method != "HEAD") {
            response += content;
        }
        status_code = 200;
    } else {
        std::string not_found = "<html><body><h1>404 Not Found</h1></body></html>\r\n";
        response  = "HTTP/1.1 404 Not Found\r\n";
        response += "Content-Type: text/html\r\n";
        response += "Content-Length: " + std::to_string(not_found.size()) + "\r\n";
        response += "\r\n";
        if (method != "HEAD") {
            response += not_found;
        }
        status_code = 404;
    }

    return response;
}

std::string build_400_response() {
    std::string body = "<html><body><h1>400 Bad Request</h1></body></html>\r\n";
    std::string response = "HTTP/1.1 400 Bad Request\r\n";
    response += "Content-Type: text/html\r\n";
    response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    response += "\r\n";
    response += body;
    return response;
}
