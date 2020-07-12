#include "downloader.h"

#include <curl/curl.h>
#include <iostream>

namespace {

size_t writeBufferCallback(void* ptr, size_t size, size_t nmemb, void* data)
{
    if (!data) {
        std::cerr << "writeBufferCallback: null pointer destination";
        exit(1);
    }
    auto buf = static_cast<std::string*>(data);

    const size_t bytes = size*nmemb;

    buf->append((char*) ptr, bytes);

    return bytes;
}

std::string downloadDocument(const std::string& url)
{
    CURL* curl;
    CURLcode res;
    std::string data;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        /* tell libcurl to follow redirection if present */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, CURLOPT_MAXREDIRS_VALUE);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeBufferCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res!=CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return data;
}

} // namespace

std::vector<std::string> downloadDocuments(const std::vector<std::string>& urls)
{
    std::vector<std::string> result;
    result.reserve(urls.size());
    for (int i = 0; i<urls.size(); ++i) { // TODO make the loop parallel
        std::cerr << "downloading documents (" << i+1 << "/" << urls.size() << ")" << std::endl;
        result.emplace_back(downloadDocument(urls[i]));
    }
    return result;
}
