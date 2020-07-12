#pragma once

#include <vector>
#include <string>


namespace downloader {

constexpr int CURLOPT_MAXREDIRS_VALUE = 5;

std::vector<std::string> downloadDocuments(const std::vector<std::string>& urls);

}
