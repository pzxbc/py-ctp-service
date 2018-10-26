#include <string>

#include <pybind11/pybind11.h>

#include "const.h"
#include "market_service.h"
#include "py_market_service.h"
#include  "trader_service.h"
#include "py_trader_service.h"

using namespace std;
namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(c_ctp, m) {
    m.doc() = "ctp service, include market-service and trader-service";
    /* py::enum_<ExchangeID>(m, "ExchangeID", py::arithmetic()) */
    /*     .value("SHFE", ExchangeID::SHFE) */
    /*     .value("CZCE", ExchangeID::CZCE) */
    /*     .value("DCE", ExchangeID::DCE) */
    /*     .value("CFFEX", ExchangeID::CFFEX) */
    /*     .value("INE", ExchangeID::INE); */

    py::class_<MarketService, PyMarketService>(m, "MarketService")
        .def(py::init<const string &, const string &>(), "front_addr"_a, "flow_path"_a)
        .def("join", &MarketService::join)
        .def("release", &MarketService::release)
        .def("reqUserLogin", &MarketService::reqUserLogin)
        .def("reqUserLogout", &MarketService::reqUserLogout)
        .def("subscribeMarketData", &MarketService::subscribeMarketData)
        .def("unSubscribeMarketData", &MarketService::unSubscribeMarketData);

    py::class_<TraderService, PyTraderService>(m, "TraderService")
        .def(py::init<const string &, const string &>(), "front_addr"_a, "flow_path"_a)
        .def("join", &TraderService::join)
        .def("release", &TraderService::release)
        .def("reqUserLogin", &TraderService::reqUserLogin)
        .def("reqUserLogout", &TraderService::reqUserLogout)
        .def("reqSettlementInfoConfirm", &TraderService::reqSettlementInfoConfirm)
        .def("reqQryInstrument", &TraderService::reqQryInstrument);
}
