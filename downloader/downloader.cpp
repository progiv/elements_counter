#include "downloader.h"

#include <algorithm>
#include <execution>
#include <mutex>
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

    std::vector<std::string> result(urls.size());
    std::mutex mutex;
    std::atomic<int> finished = 0;

    std::cerr << "downloading documents (" << urls.size() << ")" << std::endl;

    std::transform(std::execution::par_unseq, urls.begin(), urls.end(), result.begin(),
            [&finished, &urls, &mutex](const std::string& url) {
                std::string document = downloadDocument(url);
                {
                    std::lock_guard<std::mutex> lock(mutex);
                    finished.fetch_add(1);
                    std::cerr << "downloading documents (" << finished.load() << "/" << urls.size() << ")" << std::endl;
                }
                return document;
            });
    return result;
}
