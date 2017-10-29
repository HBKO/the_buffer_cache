//
//  buffer.hpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/14.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#ifndef buffer_hpp
#define buffer_hpp



#include<string>
#include<mutex>


using std::string;
using std::mutex;
#define BUSY 0
#define FREE 1
#define DELAY_WRITE 2
#define INVALID 3




class CBuffer
{
private:
    //暂时不放设备数进去
    int block_num;      //block相关数字
    int status;         //该buffer目前状态
    string data;        //指该buffer指向的数据块
public:
    CBuffer(const int block,string str):block_num(block),data(str),status(FREE),
    hash_next(NULL),hash_prev(NULL),freelist_next(NULL),freelist_prev(NULL){}     //有给予块值和数据字符串的构造函数
    CBuffer(const int block):block_num(block),status(FREE),data("empty"),
    hash_next(NULL),hash_prev(NULL),freelist_next(NULL),freelist_prev(NULL)
    {}                                           //只给予块号的构造函数
    //不允许简单的赋值，含有mutex信号量的对象不允许简单赋值
    CBuffer(CBuffer const& other)
    {
        std::lock_guard<std::mutex> lock(other.mux);
        data=other.data;
        block_num=other.block_num;
        status=other.status;
        hash_next=other.hash_next;
        hash_prev=other.hash_prev;
        freelist_next=other.freelist_next;
        freelist_prev=other.freelist_prev;
    }
//    CBuffer& operator=(const CBuffer&) = delete;  // 不允许简单的赋值

    
    //简单的获取
    int getblock() const {return block_num;}
    void setblock(const int block) {block_num=block;}
    int getstatus() const {return status;}
    void setstatus(const int sta) {status=sta;}
    string read() const {return data;}                //最初版的read
    void write(const string& str){data=str;}      //最初版的write
    ~CBuffer(){}                         //析构函数，将new出来的内存全都delete掉
    
public:                                 //可直接接触到的结点
    class CBuffer* hash_next;   //hash_queue的下一个
    class CBuffer* hash_prev;    //hash_queue的上一个
    class CBuffer* freelist_next;   //freelist的下一个
    class CBuffer* freelist_prev;   //freelist的上一个
    mutable mutex mux;                 //表示进程信号量,加上mutable的目的是为了这个即使是一个常量对象也可以修改这个mux的锁，
};




#endif /* buffer_hpp */
