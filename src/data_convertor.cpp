#include "data_convertor.h"

CTP_STRUCT convertCThostFtdcRspUserLoginField(CThostFtdcRspUserLoginField *pRspUserLogin)
{
    CTP_STRUCT d;
    d["TradingDay"] = pRspUserLogin->TradingDay;
    d["LoginTime"] = pRspUserLogin->LoginTime;
    d["BrokerID"] = pRspUserLogin->BrokerID;
    d["UserID"] = pRspUserLogin->UserID;
    d["SystemName"] = pRspUserLogin->SystemName;
    d["FrontID"] = pRspUserLogin->FrontID;
    d["SessionID"] = pRspUserLogin->SessionID;
    d["MaxOrderRef"] = pRspUserLogin->MaxOrderRef;
    d["SHFETime"] = pRspUserLogin->SHFETime;
    d["DCETime"] = pRspUserLogin->DCETime;
    d["CZCETime"] = pRspUserLogin->CZCETime;
    d["FFEXTime"] = pRspUserLogin->FFEXTime;
    d["INETime"] = pRspUserLogin->INETime;

    return d;
}

CTP_STRUCT convertCThostFtdcUserLogoutField(CThostFtdcUserLogoutField *pUserLogout)
{
    CTP_STRUCT d;
    d["BrokerID"] = pUserLogout->BrokerID;
    d["UserID"] = pUserLogout->UserID;
    return d;
}

CTP_STRUCT convertCThostFtdcRspInfoField(CThostFtdcRspInfoField *pRspInfo)
{
    CTP_STRUCT d;
    if(pRspInfo)
    {
        d["ErrorID"] = pRspInfo->ErrorID;
        d["ErrorMsg"] = trGBK(pRspInfo->ErrorMsg);
    }
    return d;
}

CTP_STRUCT convertCThostFtdcSpecificInstrumentField(CThostFtdcSpecificInstrumentField *pSpecificInstrument)
{
    CTP_STRUCT d;
    d["InstrumentID"] = pSpecificInstrument->InstrumentID;
    return d;
}


CTP_STRUCT convertCThostFtdcDepthMarketDataField(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    CTP_STRUCT d;
    d["TradingDay"] = pDepthMarketData->TradingDay;
    d["InstrumentID"] = pDepthMarketData->InstrumentID;
    d["ExchangeID"] = pDepthMarketData->ExchangeID;
    d["ExchangeInstID"] = pDepthMarketData->ExchangeInstID;
    d["LastPrice"] = pDepthMarketData->LastPrice;
    d["PreSettlementPrice"] = pDepthMarketData->PreSettlementPrice;
    d["PreClosePrice"] = pDepthMarketData->PreClosePrice;
    d["PreOpenInterest"] = pDepthMarketData->PreOpenInterest;
    d["OpenPrice"] = pDepthMarketData->OpenPrice;
    d["HighestPrice"] = pDepthMarketData->HighestPrice;
    d["LowestPrice"] = pDepthMarketData->LowestPrice;
    d["Volume"] = pDepthMarketData->Volume;
    d["Turnover"] = pDepthMarketData->Turnover;
    d["OpenInterest"] = pDepthMarketData->OpenInterest;
    d["ClosePrice"] = pDepthMarketData->ClosePrice;
    d["SettlementPrice"] = pDepthMarketData->SettlementPrice;
    d["UpperLimitPrice"] = pDepthMarketData->UpperLimitPrice;
    d["LowerLimitPrice"] = pDepthMarketData->LowerLimitPrice;
    d["PreDelta"] = pDepthMarketData->PreDelta;
    d["CurrDelta"] = pDepthMarketData->CurrDelta;
    d["UpdateTime"] = pDepthMarketData->UpdateTime;
    d["UpdateMillisec"] = pDepthMarketData->UpdateMillisec;
    d["BidPrice1"] = pDepthMarketData->BidPrice1;
    d["BidVolume1"] = pDepthMarketData->BidVolume1;
    d["AskPrice1"] = pDepthMarketData->AskPrice1;
    d["AskVolume1"] = pDepthMarketData->AskVolume1;
    d["BidPrice2"] = pDepthMarketData->BidPrice2;
    d["BidVolume2"] = pDepthMarketData->BidVolume2;
    d["AskPrice2"] = pDepthMarketData->AskPrice2;
    d["AskVolume2"] = pDepthMarketData->AskVolume2;
    d["BidPrice3"] = pDepthMarketData->BidPrice3;
    d["BidVolume3"] = pDepthMarketData->BidVolume3;
    d["AskPrice3"] = pDepthMarketData->AskPrice3;
    d["AskVolume3"] = pDepthMarketData->AskVolume3;
    d["BidPrice4"] = pDepthMarketData->BidPrice4;
    d["BidVolume4"] = pDepthMarketData->BidVolume4;
    d["AskPrice4"] = pDepthMarketData->AskPrice4;
    d["AskVolume4"] = pDepthMarketData->AskVolume4;
    d["BidPrice5"] = pDepthMarketData->BidPrice5;
    d["BidVolume5"] = pDepthMarketData->BidVolume5;
    d["AskPrice5"] = pDepthMarketData->AskPrice5;
    d["AskVolume5"] = pDepthMarketData->AskVolume5;
    d["AveragePrice"] = pDepthMarketData->AveragePrice;
    d["ActionDay"] = pDepthMarketData->ActionDay;
    return d;
}

CTP_STRUCT convertCThostFtdcSettlementInfoConfirmField(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm)
{
    CTP_STRUCT d;
    d["BrokerID"] = pSettlementInfoConfirm->BrokerID;
    d["InvestorID"] = pSettlementInfoConfirm->InvestorID;
    d["ConfirmDate"] = pSettlementInfoConfirm->ConfirmDate;
    d["ConfirmTime"] = pSettlementInfoConfirm->ConfirmTime;
    return d;
}

CTP_STRUCT convertCThostFtdcInstrumentField(CThostFtdcInstrumentField *pInstrument)
{
    CTP_STRUCT d;
    auto s = pInstrument;
    d["InstrumentID"] = s->InstrumentID;
    d["ExchangeID"] = s->ExchangeID;
    d["InstrumentName"] = trGBK(s->InstrumentName);
    d["ExchangeInstID"] = s->ExchangeInstID;
    d["ProductID"] = s->ProductID;
    d["ProductClass"] = s->ProductClass;
    d["DeliveryYear"] = s->DeliveryYear;
    d["DeliveryMonth"] = s->DeliveryMonth;
    d["MaxMarketOrderVolume"] = s->MaxMarketOrderVolume;
    d["MinMarketOrderVolume"] = s->MinMarketOrderVolume;
    d["MaxLimitOrderVolume"] = s->MaxLimitOrderVolume;
    d["MinLimitOrderVolume"] = s->MinLimitOrderVolume;
    d["VolumeMultiple"] = s->VolumeMultiple;
    d["PriceTick"] = s->PriceTick;
    d["CreateDate"] = s->CreateDate;
    d["OpenDate"] = s->OpenDate;
    d["ExpireDate"] = s->ExpireDate;
    d["StartDelivDate"] = s->StartDelivDate;
    d["EndDelivDate"] = s->EndDelivDate;
    d["InstLifePhase"] = s->InstLifePhase;
    d["IsTrading"] = s->IsTrading;
    d["PositionType"] = s->PositionType;
    d["PositionDateType"] = s->PositionDateType;
    d["LongMarginRatio"] = s->LongMarginRatio;
    d["ShortMarginRatio"] = s->ShortMarginRatio;
    d["MaxMarginSideAlgorithm"] = s->MaxMarginSideAlgorithm;
    d["UnderlyingInstrID"] = s->UnderlyingInstrID;
    d["StrikePrice"] = s->StrikePrice;
    d["OptionsType"] = s->OptionsType;
    d["UnderlyingMultiple"] = s->UnderlyingMultiple;
    d["CombinationType"] = s->CombinationType;
    return d;
}

