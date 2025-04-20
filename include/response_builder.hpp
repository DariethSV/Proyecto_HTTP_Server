#ifndef RESPONSE_BUILDER_HPP
#define RESPONSE_BUILDER_HPP

#include <string>

std::string build_response(const std::string& method, const std::string& file_path);
std::string build_400_response();
#endif
