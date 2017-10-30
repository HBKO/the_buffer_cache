//
//  BufferPool.hpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/17.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#ifndef BufferPool_hpp
#define BufferPool_hpp

#include <string>
#include <condition_variable>
#include "HashQueue,h.hpp"
#include "FreeList.hpp"
#include <vector>
#include <iostream>
#include <sstream>


class BufferPool
{
private:
    std::vector<HashQueue* > Queue_temp;  //存储四个hash_queue的vector
    FreeList* freelist;      //一个freelist，存储空闲的列表（LRU）
    HashQueue* hashqueue_1;   //存储链表的hashqueue_1
    HashQueue* hashqueue_2;   //hashqueue_2
    HashQueue* hashqueue_3;   //hashqueue_3
    HashQueue* hashqueue_4;   //hashqueue_4
    int num;                //链表中要存储的buffer数量
     std::condition_variable data_cond;  //表示等待事件的变量
    mutable std::mutex mut;
public:
    /* block_num表示要创建多少块buffer，这个函数的功能：
     1.创建buffer.2.将buffer插入到hash_queue中。3.遍历hash_queue将空闲的buffer增加到freelist中
     */
    BufferPool(int block_num);
    bool Brelse(CBuffer* buf);      //释放一个buf的资源
    CBuffer* getblk(const int block);   //根据block号来申请对应的buffer
    CBuffer* bread(const int block_number);         //将buf内的内容读取出来
    void bwrite(CBuffer* buf);          //将buf内的内容写入
    void readcontext();                 //用于测试用，输出所有节点的block值
    ~BufferPool();                     //析构函数，主要把申请的buffer全都释放掉
};



#endif /* BufferPool_hpp */
