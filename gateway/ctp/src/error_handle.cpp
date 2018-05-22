
#include"ThostFtdcMdApi.h"
#include"ThostFtdcUserApiStruct.h"
#include<iostream>
#include<string>
using std::cout;
using std::endl;
using std::string;

bool hanle_error(const string & str,CThostFtdcRspInfoField * rsp)
{
    if(rsp) {
        if (rsp->ErrorID == 0) {
#ifdef  DEBUG
            cout << str << " success" << endl;
#endif
        } else {
#ifdef  DEBUG
            cout << str << " error id :" << rsp->ErrorID << " error massage :" << rsp->ErrorMsg << endl;
#endif
        }
        return rsp->ErrorID == 0;
    }
    return true;
}