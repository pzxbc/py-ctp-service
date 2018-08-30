#pragma once

#include <ThostFtdcMdApi.h> 

#include "data_types.h"

#include <string>
#include <boost/locale/encoding.hpp>
inline std::string trGBK(const std::string & str)
{
    return boost::locale::conv::between(str, "UTF-8", "GBK");
}

CTP_STRUCT convertCThostFtdcRspUserLoginField(CThostFtdcRspUserLoginField *pRspUserLogin);

CTP_STRUCT convertCThostFtdcUserLogoutField(CThostFtdcUserLogoutField *pUserLogout);

CTP_STRUCT convertCThostFtdcRspInfoField(CThostFtdcRspInfoField *pRspInfo);

CTP_STRUCT convertCThostFtdcSpecificInstrumentField(CThostFtdcSpecificInstrumentField *pSpecificInstrument);

CTP_STRUCT convertCThostFtdcDepthMarketDataField(CThostFtdcDepthMarketDataField *pDepthMarketData);

CTP_STRUCT convertCThostFtdcSettlementInfoConfirmField(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm);
