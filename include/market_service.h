#pragma once

#include <string>
#include <vector>

#include <ThostFtdcMdApi.h> 

#include "data_types.h"

using namespace std;

class MarketService : public CThostFtdcMdSpi
{
private:
    CThostFtdcMdApi* md_api;
    int request_id;

public:
    MarketService(const string &front_addr, const string &flow_path);
    virtual ~MarketService();

    void join();
    void release();
    int reqUserLogin(const string &broker_id, const string &user_id, const string &password);
    int reqUserLogout(const string &broker_id, const string &user_id);
    int subscribeMarketData(const vector<string> &contract_list);
    int unSubscribeMarketData(const vector<string> &contract_list);

public:
    // ctp callback接口
    virtual void OnFrontConnected() override;
    virtual void OnFrontDisconnected(int nReason) override;
    virtual void OnHeartBeatWarning(int nTimeLapse) override;
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    virtual void OnRspUserLogin(CTP_STRUCT &rsp_user_login, CTP_STRUCT &rsp_info); 
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    virtual void OnRspUserLogout(CTP_STRUCT &user_logout, CTP_STRUCT &rsp_info);
    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    virtual void OnRspSubMarketData(const string &contract_id, CTP_STRUCT &rsp_info, bool is_last);
    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    virtual void OnRspUnSubMarketData(const string &contract_id, CTP_STRUCT &rsp_info, bool is_last);
    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;
    virtual void OnRtnDepthMarketData(CTP_STRUCT &market_data);
};
