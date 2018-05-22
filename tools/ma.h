//
// Created by root on 5/11/18.
//

#ifndef BT_MA_H
#define BT_MA_H
#include<list>
class Ma{
public:
    Ma(int period):Period(period){}
    size_t size()const {return que.size(); }
    float data()const{
        float result=0;
        for(auto & p:que)
            result+=p;
        return result/size();
    }



    void push(float v){
        if (que.size()==Period)
            pop();
        que.push_back(v);
    }
private:
    void pop(){
        que.pop_front();
    }

    std::list<float> que;
    int Period;

};


#endif //BT_MA_H
