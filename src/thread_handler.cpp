#include "thread_handler.hpp"
#include "logger.hpp"
#include "error_handler.hpp"
#include "request_parser.hpp"
#include "response_builder.hpp"

#include <unistd.h>     // <- Necesario para read() y close()
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <mutex>

// Tamaño del buffer para leer la solicitud
#define BUFFER_SIZE 2048

// Variables globales para las rutas
std::string GLOBAL_DOCUMENT_ROOT;
std::string GLOBAL_LOG_FILE;

// Mutex para evitar condiciones de carrera en el log
std::mutex log_mutex;

void set_globals(const std::string& doc_root, const std::string& log_file) {
    GLOBAL_DOCUMENT_ROOT = doc_root;
    GLOBAL_LOG_FILE = log_file;
}

void handle_client(int client_socket, struct sockaddr_in client_addr) {
    char buffer[BUFFER_SIZE];
    int bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);

    if (bytes_read <= 0) {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_request(client_addr, "-", "-", "-", 400, GLOBAL_LOG_FILE);
        std::string response = build_400_response();
        send(client_socket, response.c_str(), response.size(), 0);
        close(client_socket);
        return;
    }

    buffer[bytes_read] = '\0';
    std::string request_str(buffer);
    HttpRequest request = parse_request(request_str);

    std::string response;
    int status_code;

    if (!request.valid) {
        response = build_400_response();
        status_code = 400;
    } else {
        std::string path = GLOBAL_DOCUMENT_ROOT + request.path;
        response = build_response(request.method, path, status_code);
    }

    send(client_socket, response.c_str(), response.length(), 0);

    {
        std::lock_guard<std::mutex> lock(log_mutex);
        log_request(client_addr, request.method, request.path, "HTTP/1.1", status_code, GLOBAL_LOG_FILE);
    }
    close(client_socket);
}