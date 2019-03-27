#include <sstream> //std::stringstream
#include <ctime> //std::time
#include "request.h"
#include "lib/libcurlpp.h"
#include "lib/exceptions.h"

using namespace bittrex;
using namespace bittrex::lib;

std::string Request::get(const std::string &key,
                         const std::string &secret,
                         const std::string &payloads,
                         const std::string &endpoint,
                         ApiType type) {

    std::string res;
    auto uri = BASE_URL + endpoint;

    try {
        Curl curl;
        auto nonce = std::time(nullptr);
        (type != ApiType::PUBLIC) ?
            uri += "apikey=" + key + "&nonce=" + std::to_string(nonce) + "&" + payloads :
            uri += payloads;

        std::string apisign = "apisign:" + hmac_sha512(uri, secret);
        curl.setOpt(new curl::options::HttpHeader(apisign));
        curl.setOpt(new curl::options::WriteData(res));
        curl.setOpt(new curl::options::Url(uri));

        curl.perform();
    }
    catch (fail &e) {
        std::cout << e.what() << std::endl;
    }
    return res;
}


