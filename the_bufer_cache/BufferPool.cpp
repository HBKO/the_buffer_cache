//
//  BufferPool.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/17.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#include "BufferPool.hpp"
#include <vector>

BufferPool::BufferPool(int block_num)
{
    //新建以下五个链表
    hashqueue_1=new HashQueue(0);
    hashqueue_2=new HashQueue(1);
    hashqueue_3=new HashQueue(2);
    hashqueue_4=new HashQueue(3);
    freelist=new FreeList;
    std::vector<HashQueue* > Queue_temp;
    Queue_temp.push_back(hashqueue_1);
    Queue_temp.push_back(hashqueue_2);
    Queue_temp.push_back(hashqueue_3);
    Queue_temp.push_back(hashqueue_4);
    //新建对应的block块
    for(int i=0;i<block_num;++i)
    {
        CBuffer* temp=new CBuffer(i);
        (Queue_temp[i%4])->addbuffer(temp);
        freelist->addfreebuffer(temp, 1);  //刚开始所有的块全为free，全加入freelist里面
    }
}


BufferPool::~BufferPool()
{
    delete hashqueue_1;
    delete hashqueue_2;
    delete hashqueue_3;
    delete hashqueue_4;
    delete freelist;
}



//释放一个buf的资源
void BufferPool::Brelse(CBuffer* buf)
{
    
}

//根据block号来申请对应的buffer
CBuffer* BufferPool::getblk(const int block)
{
    return NULL;
}

//将buf内的内容读取出来
string BufferPool::bread(CBuffer* buf)
{
    string a="123";
    return a;
}

//将buf内的内容写入
void BufferPool::bwrite(CBuffer* buf)
{
}






