//
//  main.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/13.
//  Copyright © 2017年 何柯文. All rights reserved.
//


// stacktem.cpp -- testing the template stack class
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib> // for rand(),srand()
#include <ctime>    // for time()
#include <thread>
#include <unistd.h>
#include <atomic>
#include <sstream>
#include <vector>
#include "stcktp1.h"
#include "buffer.hpp"   //引入buffer头文件
#include "DoublyLink.hpp"
#include "HashQueue,h.hpp"
#include "FreeList.hpp"
using namespace std;



DoublyLink link_2;
FreeList freelist;

string int2str(const int &int_temp)
{
    string temp;
    stringstream stream;
    stream<<int_temp;
    temp=stream.str();   //此处也可以用 stream>>string_temp
    return temp;
}


//定义多线程函数
void thread01(int num)
{
    
    vector<CBuffer> res;
    
    
    for(int i=0;i<num;++i)
    {
        string str="the"+int2str(i)+"th buffer in the thread01";
        CBuffer test((i),str);
        res.push_back(test);
    }
    
    for(int i=0;i<num;++i)
    {
        link_2.addbuffer(&(res[i]));
        freelist.addfreebuffer(&(res[i]), 1);
        CBuffer* showbuffer=link_2.getbuffer(i);
        CBuffer* showbuffer_2=freelist.alloc();
        if(showbuffer!=NULL)
            cout<<showbuffer->read()<<endl;
        if(showbuffer_2!=NULL)
            cout<<showbuffer_2->read()<<endl;
            link_2.deletebuffer(showbuffer);
            freelist.removefreebuffer(showbuffer_2);
    }
}


void thread02(int num)
{
    vector<CBuffer> res;
    for(int i=0;i<num;++i)
    {
        string str="the"+int2str(i+num)+"th buffer in the thread01";
        CBuffer test((i+num),str);
        res.push_back(test);
    }
    
    
    
    for(int i=0;i<num;++i)
    {
        link_2.addbuffer(&(res[i]));
        freelist.addfreebuffer(&(res[i]),1);
        CBuffer* showbuffer=link_2.getbuffer(i+num);
        CBuffer* showbuffer_2=freelist.alloc();
        if(showbuffer!=NULL)
            cout<<showbuffer->read()<<endl;
        if(showbuffer_2!=NULL)
            cout<<showbuffer_2->read()<<endl;
            link_2.deletebuffer(showbuffer);
            freelist.removefreebuffer(showbuffer_2);
    }
}





int main(int argc, const char * argv[]) {
    // insert code here...
    thread t1(thread01,10);
    thread t2(thread02,10);
    t1.join();
    t2.join();
    return 0;
}
