#include "downloader/downloader.h"

#include <iostream>
#include <vector>

std::vector<int> countElements(const std::vector<std::string>& documents)
{
    return {};
}

void printCounts(const std::vector<int>& counts, const std::vector<std::string>& urls)
{
}

int main(int argc, char** argv)
{
    if (argc<=1) {
        std::cerr << "Usage: elements_counter <list of URLs leading to xml documents separated with space>"
                  << std::endl;
        return 1;
    }
    std::vector<std::string> urls(argv+1, argv+argc);

    const auto documents = downloader::downloadDocuments(urls);

    const auto element_counts = countElements(documents);

    printCounts(element_counts, urls);

    return 0;
}
