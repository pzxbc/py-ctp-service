#include "trader_service.h"
#include "data_convertor.h"

#include <pybind11/pybind11.h>
#include <regex>

namespace py = pybind11;

TraderService::TraderService(const string &front_addr, const string &flow_path)
{
    request_id = 0;
    trader_api = nullptr;

    trader_api = CThostFtdcTraderApi::CreateFtdcTraderApi(flow_path.c_str());
    trader_api->RegisterSpi(this);
    trader_api->RegisterFront(const_cast<char*>(front_addr.c_str()));
    trader_api->SubscribePrivateTopic(THOST_TERT_RESUME);
    trader_api->SubscribePublicTopic(THOST_TERT_RESUME);
    trader_api->Init();
}

TraderService::~TraderService()
{
    this->release();
}

void TraderService::join()
{
    py::gil_scoped_release release;
    trader_api->Join();
}

void TraderService::release()
{
    if(trader_api != nullptr)
    {
        trader_api->Release();
        trader_api = nullptr;
    }
}

int TraderService::reqUserLogin(const string &broker_id, const string &user_id, const string &password)
{
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(CThostFtdcReqUserLoginField));
    strcpy(req.BrokerID, broker_id.c_str());
    strcpy(req.UserID, user_id.c_str());
    strcpy(req.Password, password.c_str());

    return trader_api->ReqUserLogin(&req, ++request_id);
}

int TraderService::reqUserLogout(const string &broker_id, const string &user_id)
{
    CThostFtdcUserLogoutField logout_field;
    memset(&logout_field, 0, sizeof(CThostFtdcUserLogoutField));
    strcpy(logout_field.BrokerID, broker_id.c_str());
    strcpy(logout_field.UserID, user_id.c_str());

    return trader_api->ReqUserLogout(&logout_field, ++request_id);
}

int TraderService::reqSettlementInfoConfirm(const string &broker_id, const string &user_id, const string &confirm_date, const string &confirm_time)
{
    CThostFtdcSettlementInfoConfirmField confirm_field;
    memset(&confirm_field, 0, sizeof(CThostFtdcSettlementInfoConfirmField));
    strcpy(confirm_field.BrokerID, broker_id.c_str());
    strcpy(confirm_field.InvestorID, user_id.c_str());
    strcpy(confirm_field.ConfirmDate, confirm_date.c_str());
    strcpy(confirm_field.ConfirmTime, confirm_time.c_str());

    return trader_api->ReqSettlementInfoConfirm(&confirm_field, ++request_id);
}

int TraderService::reqQryInstrument(const string &contract_id, const string &exchange_id)
{
    CThostFtdcQryInstrumentField instrument_field;
    memset(&instrument_field, 0, sizeof(CThostFtdcQryInstrumentField));
    strcpy(instrument_field.InstrumentID, contract_id.c_str());
    strcpy(instrument_field.ExchangeID, exchange_id.c_str());
    strcpy(instrument_field.ExchangeInstID, contract_id.c_str());
    regex pattern("\\d");
    smatch sm;
    regex_search(contract_id, sm, pattern);
    string product_id{""};
    if(!sm.empty())
    {
        product_id = contract_id.substr(0, sm.position());
    }
    strcpy(instrument_field.ProductID, product_id.c_str());
    return trader_api->ReqQryInstrument(&instrument_field, ++request_id);
}


// CTP 回调接口

void TraderService::OnFrontConnected() 
{
    py::gil_scoped_acquire acquire;
    py::print("TraderService::OnFrontConnected From C++");
}

void TraderService::OnFrontDisconnected(int nReason)
{
    py::gil_scoped_acquire acquire;
    py::print("TraderService::OnFrontDisconnected From C++", nReason);
}

void TraderService::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto rsp_user_login = convertCThostFtdcRspUserLoginField(pRspUserLogin);
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    this->OnRspUserLogin(rsp_user_login, rsp_info);
}

void TraderService::OnRspUserLogin(CTP_STRUCT &rsp_user_login, CTP_STRUCT &rsp_info)
{
    CTP_STRUCT d = rsp_user_login;
    py::print("TraderService::OnRspUserLogin not implemented");
    py::print(d["TradingDay"], d["LoginTime"], d["BrokerID"], d["UserID"], d["SystemName"], d["FrontID"], d["SessionID"], d["MaxOrderRef"], d["SHFETime"]);
    /* py::print(rsp_info["ErrorID"], py::bytes(boost::get<string>(rsp_info["ErrorMsg"]))); */
    /* cout << rsp_info["ErrorMsg"] << endl; */
}

void TraderService::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto user_logout = convertCThostFtdcUserLogoutField(pUserLogout);
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    this->OnRspUserLogout(user_logout, rsp_info);
}

void TraderService::OnRspUserLogout(CTP_STRUCT &user_logout, CTP_STRUCT &rsp_info)
{
    py::gil_scoped_acquire acquire;
    py::print("TraderService::OnRspUserLogout not implemented");
}

void TraderService::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto confirm_field = convertCThostFtdcSettlementInfoConfirmField(pSettlementInfoConfirm);
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    this->OnRspSettlementInfoConfirm(confirm_field, rsp_info);
}

void TraderService::OnRspSettlementInfoConfirm(CTP_STRUCT &confirm_field, CTP_STRUCT &rsp_info)
{
    py::gil_scoped_acquire acquire;
    py::print("TraderService::OnRspSettlementInfoConfirm not implemented");
}

void TraderService::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto contract_info = convertCThostFtdcInstrumentField(pInstrument);
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    this->OnRspQryInstrument(contract_info, rsp_info, bIsLast);
}
void TraderService::OnRspQryInstrument(CTP_STRUCT &contract_info, CTP_STRUCT &rsp_info, bool is_last)
{
    py::gil_scoped_acquire acquire;
    py::print("TraderService::OnRspQryInstrument not implemented");
}
