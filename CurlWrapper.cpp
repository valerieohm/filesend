//
// Created by Buck Shlegeris on 12/11/16.
//

#include <curl/curl.h>
#include <iostream>
#include "CurlWrapper.h"

CurlResult CurlWrapper::request(std::string uri) {
    std::string data;
    CURL* curl = curl_easy_init();

    long http_code = 0;

    curl_easy_setopt(curl, CURLOPT_URL, uri.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrapper::handle);

    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

    curl_easy_cleanup(curl);


    return CurlResult(http_code, data);
}

size_t CurlWrapper::handle(char *data, size_t size, size_t nmemb, std::string *output) {
    for (size_t c = 0; c < size * nmemb; c++) {
        output->push_back(data[c]);
    }

    return size * nmemb;
}
