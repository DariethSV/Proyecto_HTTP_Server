#include "request_parser.hpp"
#include <iostream>

HttpRequest parse_request(const std::string& raw_request) {
    HttpRequest request;
    request.valid = false;

    // Mostrar la solicitud completa
    std::cout << "Solicitud recibida: " << raw_request << "\n";

    size_t sp1 = raw_request.find(' ');
    size_t sp2 = raw_request.find(' ', sp1 + 1);

    if (sp1 == std::string::npos || sp2 == std::string::npos) {
        return request; // Petición malformada
    }

    request.method = raw_request.substr(0, sp1);
    request.path = raw_request.substr(sp1 + 1, sp2 - sp1 - 1);
    if (request.path == "/") request.path = "/index.html";

    if (request.method == "GET" || request.method == "HEAD" || request.method == "POST") {
        request.valid = true;
    }

    return request;
}
