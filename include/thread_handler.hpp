#pragma once
#include <netinet/in.h>
#include <string>
// En thread_handler.hpp (si quieres usarlas desde otros .cpp)
extern std::string GLOBAL_DOCUMENT_ROOT;
extern std::string GLOBAL_LOG_FILE;

void handle_client(int client_socket, struct sockaddr_in client_addr);
void set_globals(const std::string& doc_root, const std::string& log_file);
