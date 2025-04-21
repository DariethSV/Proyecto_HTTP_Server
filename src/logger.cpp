#include "logger.hpp"
#include <fstream>
#include <ctime>
#include <arpa/inet.h>
#include <cstring>

void log_request(struct sockaddr_in client_addr, const std::string& method,
                 const std::string& resource, const std::string& protocol,
                 int status_code, const std::string& log_file) {
    
    std::ofstream log(log_file, std::ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    dt[strlen(dt) - 1] = '\0'; // Quitar salto de línea

    std::string ip = inet_ntoa(client_addr.sin_addr);

    log << "[" << dt << "] "
        << ip << " - " << method << " " << resource << " - "
        << status_code << std::endl;
}
