//
// Created by Buck Shlegeris on 12/11/16.
//

#ifndef WEB_CRAWLER_CURLWRAPPER_H
#define WEB_CRAWLER_CURLWRAPPER_H

#include <string>

class CurlResult {
public:
    long response_code;
    std::string response_body;

    CurlResult(long response_code, std::string response_body):
            response_code(response_code), response_body(response_body) {
    }
};

class CurlWrapper {

public:
    static CurlResult request(std::string uri);
    static size_t handle(char *data, size_t size, size_t nmemb, std::string *output);
};



#endif //WEB_CRAWLER_CURLWRAPPER_H
