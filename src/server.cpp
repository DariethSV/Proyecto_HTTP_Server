#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <string>
#include "request_parser.hpp"
#include "response_builder.hpp"

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: ./server <PUERTO> <LOGFILE> <DOCUMENT_ROOT>\n";
        return 1;
    }

    int port = std::stoi(argv[1]);
    std::string document_root = argv[3];

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error al crear el socket\n";
        return 1;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr << "Error al hacer bind\n";
        return 1;
    }

    if (listen(server_fd, 10) == -1) {
        std::cerr << "Error al escuchar conexiones\n";
        return 1;
    }

    std::cout << "Servidor escuchando en puerto " << port << "...\n";

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        int new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (new_socket == -1) {
            std::cerr << "Error al aceptar la conexión\n";
            continue;
        }

        char buffer[BUFFER_SIZE] = {0};
        read(new_socket, buffer, sizeof(buffer));

        std::string buffer_str(buffer);
        
        // Analizar la solicitud HTTP
        HttpRequest request = parse_request(buffer_str);
        
        // Verificar que la solicitud es válida
        if (!request.valid) {
            std::string response = build_400_response();
            send(new_socket, response.c_str(), response.size(), 0);
            close(new_socket);
            continue;
        }

        // Construir la respuesta según el archivo solicitado
        std::string file_path = document_root + (request.path == "/" ? "/index.html" : request.path);
        std::string response = build_response(request.method, file_path);

        send(new_socket, response.c_str(), response.size(), 0);
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
