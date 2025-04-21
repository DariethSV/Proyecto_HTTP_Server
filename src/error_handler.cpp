#include "error_handler.hpp"
#include <string>
#include <unistd.h>

void send_error_response(int client_socket, int error_code) {
    std::string response;

    if (error_code == 400) {
        response = "HTTP/1.1 400 Bad Request\r\n\r\nSolicitud inválida";
    } else if (error_code == 404) {
        response = "HTTP/1.1 404 Not Found\r\n\r\nRecurso no encontrado";
    }

    send(client_socket, response.c_str(), response.length(), 0);
}
