#pragma once

#include <string>

#include <ThostFtdcTraderApi.h>

#include "data_types.h"

using namespace std;


class TraderService : public CThostFtdcTraderSpi
{
private:
    CThostFtdcTraderApi* trader_api;
    int request_id;

public:
    TraderService(const string &front_addr, const string &flow_path);
    virtual ~TraderService();

    void join();
    void release();
    int reqUserLogin(const string &broker_id, const string &user_id, const string &password);
    int reqUserLogout(const string &broker_id, const string &user_id);
    // 投资结算结果确认
    int reqSettlementInfoConfirm(const string &broker_id, const string &user_id, const string &confirm_date, const string &confirm_time);

public:
    // ctp callback接口
    virtual void OnFrontConnected() override;
    virtual void OnFrontDisconnected(int nReason) override;
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    virtual void OnRspUserLogin(CTP_STRUCT &rsp_user_login, CTP_STRUCT &rsp_info); 
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;
    virtual void OnRspUserLogout(CTP_STRUCT &user_logout, CTP_STRUCT &rsp_info);
    // 投资结算结果确认信息
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override; 
    virtual void OnRspSettlementInfoConfirm(CTP_STRUCT &confirm_info, CTP_STRUCT &rsp_info);
};
