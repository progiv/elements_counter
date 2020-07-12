#include "counter/counter.h"
#include "downloader/downloader.h"

#include <iostream>
#include <vector>

int main(int argc, char** argv)
{
    if (argc<=1) {
        std::cerr << "Usage: Counter <list of URLs leading to xml documents separated with space>"
                  << std::endl;
        return 1;
    }
    std::vector<std::string> urls(argv+1, argv+argc);

    const auto documents = downloadDocuments(urls);

    std::cout << "element_count | url:" << std::endl;
    for (int i = 0; i<urls.size(); ++i) {
        std::cout << countElements(documents[i]) << " " << urls[i] << std::endl;
    }

    return 0;
}
