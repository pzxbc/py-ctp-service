#include "market_service.h"
#include "data_convertor.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

MarketService::MarketService(const string &front_addr, const string &flow_path)
{
    // 初始化
    request_id = 0;
    md_api = nullptr;

    // 创建md_api
    md_api = CThostFtdcMdApi::CreateFtdcMdApi(flow_path.c_str());
    md_api->RegisterSpi(this);
    md_api->RegisterFront(const_cast<char*>(front_addr.c_str()));
    md_api->Init();
}

MarketService::~MarketService()
{
    md_api->Release();
    md_api = nullptr;
}

void MarketService::join()
{
    py::gil_scoped_release release;
    md_api->Join();
}

void MarketService::release()
{
    md_api->Release();
    md_api = nullptr;
}

int MarketService::reqUserLogin(const string &broker_id, const string &user_id, const string &password)
{
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(CThostFtdcReqUserLoginField));
    strcpy(req.BrokerID, broker_id.c_str());
    strcpy(req.UserID, user_id.c_str());
    strcpy(req.Password, password.c_str());

    return md_api->ReqUserLogin(&req, ++request_id);
}

int MarketService::reqUserLogout(const string &broker_id, const string &user_id)
{
    CThostFtdcUserLogoutField logout_field;
    memset(&logout_field, 0, sizeof(CThostFtdcUserLogoutField));
    strcpy(logout_field.BrokerID, broker_id.c_str());
    strcpy(logout_field.UserID, user_id.c_str());

    return md_api->ReqUserLogout(&logout_field, ++request_id);
}

int MarketService::subscribeMarketData(const vector<string> &contract_list)
{
    std::vector<char*> tmp;
    for(auto &contract : contract_list)
    {
        tmp.push_back(const_cast<char*>(contract.c_str()));
    }
    return md_api->SubscribeMarketData(tmp.data(), tmp.size());
}

int MarketService::unSubscribeMarketData(const vector<string> &contract_list)
{
    std::vector<char*> tmp;
    for(auto &contract : contract_list)
    {
        tmp.push_back(const_cast<char*>(contract.c_str()));
    }
    return md_api->UnSubscribeMarketData(tmp.data(), tmp.size());
}


// CTP 回调接口

void MarketService::OnFrontConnected() 
{
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnFrontConnected From C++");
}

void MarketService::OnFrontDisconnected(int nReason)
{
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnFrontDisconnected From C++", nReason);
}

void MarketService::OnHeartBeatWarning(int nTimeLapse)
{
    // CTP文档已说明该接口不再生效
    //
    // iptables过滤front_addr地址的packet会导致CThostFtdcUserApiImplBase::OnSessionDisconnected
    // 以及OnFrontDisconnected调用，但是不会调用该函数，暂时未找到触发回调的方法
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnFrontDisconnected From C++", nTimeLapse);
}

void MarketService::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto rsp_user_login = convertCThostFtdcRspUserLoginField(pRspUserLogin);
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    this->OnRspUserLogin(rsp_user_login, rsp_info);
}

void MarketService::OnRspUserLogin(CTP_STRUCT &rsp_user_login, CTP_STRUCT &rsp_info)
{
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnRspUserLogin not implemented");
}

void MarketService::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto user_logout = convertCThostFtdcUserLogoutField(pUserLogout);
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    this->OnRspUserLogout(user_logout, rsp_info);
}

void MarketService::OnRspUserLogout(CTP_STRUCT &user_logout, CTP_STRUCT &rsp_info)
{
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnRspUserLogout not implemented");
}

void MarketService::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    string contract_id = pSpecificInstrument->InstrumentID;
    this->OnRspSubMarketData(contract_id, rsp_info, bIsLast);
}

void MarketService::OnRspSubMarketData(const string &contract_id, CTP_STRUCT &rsp_info, bool is_last)
{
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnRspSubMarketData not implemented");
}

void MarketService::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    auto rsp_info = convertCThostFtdcRspInfoField(pRspInfo);
    string contract_id = pSpecificInstrument->InstrumentID;
    this->OnRspUnSubMarketData(contract_id, rsp_info, bIsLast);
}

void MarketService::OnRspUnSubMarketData(const string &contract_id, CTP_STRUCT &rsp_info, bool is_last)
{
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnRspUnSubMarketData not implemented");
}

void MarketService::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    auto market_data = convertCThostFtdcDepthMarketDataField(pDepthMarketData);
    this->OnRtnDepthMarketData(market_data);
}

void MarketService::OnRtnDepthMarketData(CTP_STRUCT &market_data)
{
    py::gil_scoped_acquire acquire;
    py::print("MarketService::OnRtnDepthMarketData not implemented");
}

