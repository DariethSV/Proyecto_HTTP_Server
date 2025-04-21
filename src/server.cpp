#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <thread>
#include "thread_handler.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Uso: ./server <PUERTO> <LOGFILE> <DOCUMENT_ROOT>\n";
        return 1;
    }

    int port = std::stoi(argv[1]);
    std::string log_file = argv[2];
    std::string document_root = argv[3];

    // Establecer rutas globales para los threads
    set_globals(document_root, log_file);

    // Crear socket del servidor
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Error al crear el socket\n";
        return 1;
    }

    // Reutilizar puerto en caso de reinicio rápido
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Configurar dirección del servidor
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

        // Crear un thread para cada cliente
        std::thread(handle_client, new_socket, client_addr).detach();
    }

    close(server_fd);
    return 0;
}
