#include <string>

#include <pybind11/pybind11.h>

#include "market_service.h"
#include "py_market_service.h"

using namespace std;
namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(ctp, m) {
    m.doc() = "ctp service, include market-service and trader-service";
    py::class_<MarketService, PyMarketService>(m, "MarketService")
        .def(py::init<const string &, const string &>(), "front_addr"_a, "flow_path"_a)
        .def("join", &MarketService::join)
        .def("release", &MarketService::release)
        .def("reqUserLogin", &MarketService::reqUserLogin)
        .def("reqUserLogout", &MarketService::reqUserLogout)
        .def("subscribeMarketData", &MarketService::subscribeMarketData)
        .def("unSubscribeMarketData", &MarketService::unSubscribeMarketData);
}
