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
#include "BufferPool.hpp"
using namespace std;



DoublyLink link_2;
FreeList freelist;
BufferPool pool(30);
vector<CBuffer* > bufblock;

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
        string str="the"+int2str(i+num)+"th buffer in the thread02";
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
            cout<<(showbuffer->read())<<endl;
        if(showbuffer_2!=NULL)
            cout<<(showbuffer_2->read())<<endl;
        link_2.deletebuffer(showbuffer);
        freelist.removefreebuffer(showbuffer_2);
    }
}





//开第一个线程，申请已经存在于hash_queue的buffer,不释放
class myfun
{
private:
    int num;
public:
    myfun(int number):num(number){};
    
    void operator()()
    {
        vector<CBuffer*> res;
        for(int i=0;i<num;++i)
        {
            CBuffer* test=pool.bread(i);
            res.push_back(test);
            cout<<"alloc the block is: "<<i<<endl;
            pool.bwrite(test);
        }
/*
        for(auto k:res)
        {
            cout<<k->read()<<endl;
            pool.bwrite(k);
        }
 */
    }
};



//开第二个线程一直申请hash_queue中没有的buffer，释放
void thread03(int num)
{
    vector<CBuffer *> res;
    for(int i=0;i<num;++i)
    {
        CBuffer* test=pool.bread(i+30);
        res.push_back(test);
        cout<<"alloc the block is: "<<i+30<<endl;
        pool.bwrite(test);
    }
/*
    for(auto k:res)
    {
        cout<<k->read()<<endl;
        pool.bwrite(k);
    }
*/
}


//开第三个线程也一直申请hash_queue中没有的buffer
void thread04(int num)
{
    vector<CBuffer *> res;
    for(int i=0;i<num;++i)
    {
        CBuffer* test=pool.bread(i+40);
        res.push_back(test);
        cout<<"alloc the block is: "<<i+40<<endl;
        pool.bwrite(test);
    }
/*
    for(auto k:res)
    {
        cout<<k->read()<<endl;
//        pool.bwrite(k);
    }
*/
}


//开第四个线程申请
void thread05(int num)
{
    for(int i=0;i<num;++i)
    {
        CBuffer* test=pool.bread(i);
        bufblock.push_back(test);
    }
}


//开第五个线程进行释放，用来测试第五种情况
void thread06()
{
    for(auto k:bufblock)
    {
        pool.bwrite(k);
    }
}










int main(int argc, const char * argv[]) {
    // insert code here...
    myfun func(29);
    thread05(29);
    pool.readcontext();
    std::thread t2(thread03,10);
    std::thread t3(thread04,10);
    std::thread t1(func);
//    std::thread t4(thread05,28);
    
    t2.join();
    t3.join();
    
    std::thread t4(thread06);
    t4.join();
    t1.join();
//    t4.join();
    
    pool.readcontext();
    
    return 0;
}
