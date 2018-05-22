//
// Created by root on 4/26/18.
//

#ifndef BT_FILEGATEWAY_H
#define BT_FILEGATEWAY_H
#include "FakeGateWay.h"
#include <string>
#include <chrono>
#include<time.h>
#include "../csvreader/CSVparser.hpp"
#include"../events/L1TickEvent.h"

class FileGateWay:public FakeGateWay{
public:
    FileGateWay(const char * FileName,int interval_):FakeGateWay(interval_),filename(FileName){}
    virtual void run()=0;

public:
    std::string filename;

};

class CsvFileGateWay:public  FileGateWay
{
public:
    CsvFileGateWay(const char * FileName,int interval_):FileGateWay(FileName,interval_){}
    virtual void run()
    {
        csv::Parser file = csv::Parser(filename);
        auto rowsize = file.rowCount();
        auto columnsize = file.columnCount();
        for(int i=0;i!=rowsize;++i) {
            if(!__active)
                break;
            L1TickPtr tickData(new L1Tick{file[i][1],
                                          file[i][2],
                                          atof(file[i][3].c_str()),
                                          atof(file[i][12].c_str()),
                                          atof(file[i][13].c_str()),
                                          atof(file[i][7].c_str()),
                                          atof(file[i][14].c_str()),
                                          atof(file[i][15].c_str())});
            OnL1Tick(tickData);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }


};


#endif //BT_FILEGATEWAY_H
