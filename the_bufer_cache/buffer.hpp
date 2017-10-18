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


using std::string;
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
    hash_next(NULL),hash_prev(NULL),freelist_next(NULL),freelist_prev(NULL){};     //有给予块值和数据字符串的构造函数
    CBuffer(const int block):block_num(block),status(FREE),data("empty"),
    hash_next(NULL),hash_prev(NULL),freelist_next(NULL),freelist_prev(NULL)
    {};                                           //只给予块号的构造函数
    //简单的获取
    int getblock() const {return block_num;}
    void setblock(const int block) {block_num=block;}
    int getstatus() const {return status;}
    void setstatus(const int sta) {status=sta;}
    string read() const {return data;}                //最初版的read
    void write(const string& str){data=str;}      //最初版的write
public:                                 //可直接接触到的结点
    class CBuffer* hash_next;   //hash_queue的下一个
    class CBuffer* hash_prev;    //hash_queue的上一个
    class CBuffer* freelist_next;   //freelist的下一个
    class CBuffer* freelist_prev;   //freelist的上一个
};




#endif /* buffer_hpp */
