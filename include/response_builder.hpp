#pragma once
#include <string>

std::string build_response(const std::string& method, const std::string& file_path, int& status_code);
std::string build_400_response();  // <-- importante
