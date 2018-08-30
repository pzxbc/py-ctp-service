#pragma once

#include <pybind11/pybind11.h>
#include "trader_service.h"

namespace py = pybind11;

class PyTraderService : public TraderService
{
    using TraderService::TraderService;

    void OnFrontConnected() override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            TraderService,
            OnFrontConnected,
            );
    }

    void OnFrontDisconnected(int nReason) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            TraderService,
            OnFrontDisconnected,
            nReason
            );
    }

    void OnRspUserLogin(CTP_STRUCT &rsp_user_login, CTP_STRUCT &rsp_info) override 
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            TraderService,
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
            TraderService,
            OnRspUserLogout,
            user_logout,
            rsp_info
            );
    }

    void OnRspSettlementInfoConfirm(CTP_STRUCT &confirm_info, CTP_STRUCT &rsp_info) override
    {
        py::gil_scoped_acquire acquire;
        PYBIND11_OVERLOAD(
            void,
            TraderService,
            OnRspSettlementInfoConfirm,
            confirm_info,
            rsp_info
            );
    }
};
