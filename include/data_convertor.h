#pragma once

#include <ThostFtdcMdApi.h> 

#include "data_types.h"

CTP_STRUCT convertCThostFtdcRspUserLoginField(CThostFtdcRspUserLoginField *pRspUserLogin);

CTP_STRUCT convertCThostFtdcUserLogoutField(CThostFtdcUserLogoutField *pUserLogout);

CTP_STRUCT convertCThostFtdcRspInfoField(CThostFtdcRspInfoField *pRspInfo);

CTP_STRUCT convertCThostFtdcSpecificInstrumentField(CThostFtdcSpecificInstrumentField *pSpecificInstrument);

CTP_STRUCT convertCThostFtdcDepthMarketDataField(CThostFtdcDepthMarketDataField *pDepthMarketData);
