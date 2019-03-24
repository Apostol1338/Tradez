#include <sstream>
#include "market.h"

using namespace bittrex::api;
using json = nlohmann::json;


std::string Market::buy_limit(const string &market, float quantity, float rate) {
    auto res = dispatch("market/buylimit?", ApiType::MARKET, "market=", market, "quantity=", quantity, "rate=", rate);
    return res["result"];
}


std::string Market::sell_limit(const string &market, float quantity, float rate) {
    auto res = dispatch("market/selllimit?", ApiType::MARKET, "market=", market, "quantity=", quantity, "rate=", rate);
    return res["result"];

}


std::string Market::cancel(const string &uuid) {
    auto res = dispatch("market/cancel?", ApiType::MARKET, "uuid=", uuid);
    return res["result"];
}


List<response::OpenOrder> Market::get_open_orders(const string &market) {
    List<response::OpenOrder> open_orders;

    auto res = dispatch("market/getopenorders?", ApiType::MARKET, "market=", market);

    auto j_o_orders = res["result"];
    for (auto const &order:j_o_orders) {
        open_orders.emplace_back(response::OpenOrder(order));
    }
    return open_orders;
}



