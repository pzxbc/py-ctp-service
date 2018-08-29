#pragma once

#include <pybind11/pybind11.h>
#include "market_service.h"

namespace py = pybind11;

class PyMarketService : public MarketService
{
public:
    using MarketService::MarketService;

    void OnFrontConnected() override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnFrontConnected,
            );
    }

    void OnFrontDisconnected(int nReason) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnFrontDisconnected,
            nReason
            );
    }

    void OnHeartBeatWarning(int nTimeLapse) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnHeartBeatWarning,
            nTimeLapse
            );
    }

    void OnRspUserLogin(CTP_STRUCT &rsp_user_login, CTP_STRUCT &rsp_info) override 
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnRspUserLogin,
            rsp_user_login,
            rsp_info
            );
    }

    void OnRspUserLogout(CTP_STRUCT &user_logout, CTP_STRUCT &rsp_info) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnRspUserLogout,
            user_logout,
            rsp_info
            );
    }

    void OnRspSubMarketData(const string &contract_id, CTP_STRUCT &rsp_info, bool is_last) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnRspSubMarketData,
            contract_id,
            rsp_info,
            is_last
            );
    }
    void OnRspUnSubMarketData(const string &contract_id, CTP_STRUCT &rsp_info, bool is_last) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnRspUnSubMarketData,
            contract_id,
            rsp_info,
            is_last
            );
    }
    void OnRtnDepthMarketData(CTP_STRUCT &market_data) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            MarketService,
            OnRtnDepthMarketData,
            market_data
            );
    }
};
