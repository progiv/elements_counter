add_library(downloader downloader.cpp downloader.h)

## CURL
# Have to install libcurl-dev(libcurl4-openssl-dev) package
include(FindCURL)
include_directories(${CURL_INCLUDE_DIR})

#add_link_options(-ltbb)
target_link_libraries(downloader ${CURL_LIBRARIES} -ltbb)
