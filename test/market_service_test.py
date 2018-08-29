# -*- coding: utf-8 -*-

import ctp
import time

class MarketService(ctp.MarketService):

    def __init__(self, front_addr, flow_path):
        ctp.MarketService.__init__(self, front_addr, flow_path)

    def OnFrontConnected(self):
        print("MarketService OnFrontConnected")
        # self.reqUserLogin('9999', '118954', 'mesontrader')
        self.reqUserLogin('9000', '', '')

    def OnRspUserLogin(self, rsp_user_login, rsp_info):
        print(rsp_user_login, rsp_info)
        # self.reqUserLogout('9999', '118954')
        self.subscribeMarketData(('hc1901',))

    def OnRspUserLogout(self, user_logout, rsp_info):
        # 模拟盘没有回调?
        print(user_logout, rsp_info)

    def OnRspSubMarketData(self, contract_id, rsp_info, is_last):
        print(contract_id, rsp_info, is_last)

    def OnRtnDepthMarketData(self, market_data):
        print(market_data)

def main():
    # market_service = MarketService('tcp://180.168.146.187:10011', 'test')
    market_service = MarketService('tcp://180.166.11.33:41213', 'simu')
    # 不使用join
    # market_service.join()
    while True:
        time.sleep(1)

if __name__ == '__main__':
    main()
