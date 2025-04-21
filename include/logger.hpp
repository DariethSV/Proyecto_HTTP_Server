#pragma once
#include <netinet/in.h>
#include <string>

void log_request(struct sockaddr_in client_addr, const std::string& method,
                 const std::string& resource, const std::string& protocol,
                 int status_code, const std::string& log_file);
