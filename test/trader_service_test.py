# -*- coding: utf-8 -*-

import ctp
import time
import datetime

class TraderService(ctp.TraderService):

    def __init__(self, front_addr, flow_path):
        ctp.TraderService.__init__(self, front_addr, flow_path)

    def OnFrontConnected(self):
        print("TraderService OnFrontConnected")
        self.reqUserLogin('9999', '118954', 'mesontrader')

    def OnRspUserLogin(self, rsp_user_login, rsp_info):
        print(rsp_user_login, rsp_info)
        
        now = datetime.datetime.now()
        self.reqSettlementInfoConfirm('9999', '118954', now.strftime('%Y%m%d'), now.strftime('%H:%M:%S'))

        # self.reqUserLogout('4200', '15500028')

    def OnRspUserLogout(self, user_logout, rsp_info):
        print(user_logout, rsp_info)

    def OnRspSettlementInfoConfirm(self, confirm_info, rsp_info):
        print(confirm_info, rsp_info)
        self.reqQryInstrument('SM905', 'CZCE')

    def OnRspQryInstrument(self, contract_info, rsp_info, is_last):
        print(contract_info, rsp_info, is_last)


def main():
    trader_service = TraderService('tcp://180.168.146.187:10000', '155')
    while True:
        time.sleep(1)

if __name__ == '__main__':
    main()
