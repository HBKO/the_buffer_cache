//
//  BufferPool.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/17.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#include "BufferPool.hpp"




BufferPool::BufferPool(int block_num)
{
    //新建以下五个链表
    hashqueue_1=new HashQueue(0);
    hashqueue_2=new HashQueue(1);
    hashqueue_3=new HashQueue(2);
    hashqueue_4=new HashQueue(3);
    freelist=new FreeList;
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




//对对应的block的进行释放
bool BufferPool::Brelse(CBuffer* buf)
{
    buf->setstatus(FREE);
    data_cond.notify_all();
    //将使用完的buffer添加到freelist的尾巴，实现LRU
    freelist->addfreebuffer(buf, 0);
    return true;
}



//根据block号来申请对应的buffer,返回NULL说明程序出错了。
CBuffer* BufferPool::getblk(const int block)
{
    int flag_1=0;   //该flag表示对应的buffer是否寻找到，0表示未寻找到
    while(!flag_1)
    {
        CBuffer* buf=Queue_temp[block%4]->getbuffer(block);
        if(buf!=NULL)
        {
            if((buf->getstatus())==BUSY)        //情况五
            {
                std::unique_lock<std::mutex> lk(buf->mux);    //使用unique_lock建立互斥锁,对应取的锁应该是buffer的锁
                data_cond.wait(lk,[&buf]{return buf->getstatus()==FREE;});    //对于lambdas函数表达式，要么将其设置成全局变量（全局函数），或者通过[]里面的值传入
                continue;
            }
            buf->setstatus(BUSY);                //情况一
            freelist->removefreebuffer(buf);
            return buf;
        }
        else        // block not on hash queue //
        {
            CBuffer* freebuf=freelist->alloc();
            if(freebuf==NULL)   //在freelist里面已经没有可以申请出来的块了，情况四
            {
                std::unique_lock<std::mutex> bk(buf->mux);
                data_cond.wait(bk,[this]{return freelist->alloc()!=NULL;});   //对于想要在lambda表达式中传对象成员（函数或者变量，需要把this指针传进去）
                continue;
            }
            freelist->removefreebuffer(freebuf);
            if(buf->getstatus()==DELAY_WRITE)   //情况三
            {
                bwrite(buf,"Delay_write");        //进行延迟写的操作
                continue;
            }
            //情况二，找到了一个空闲的buffer
            //将buf从旧的hash_queue中移除
            int old_block=freebuf->getblock();
            Queue_temp[old_block%4]->deletebuffer(old_block);
            freebuf->setblock(block);
            //将buf添加到新的hash_queue中
            Queue_temp[block%4]->addbuffer(freebuf);
//            flag_1=1;
            return freebuf;
        }
    }
    return NULL;
}





//通过输入block_number从磁盘中将需要的block取出
//分为两个步骤：1.申请新的buffer，然后将
CBuffer* BufferPool::bread(const int block_number)
{
    //利用空循环来实现线程间的交互
    for(int i=0;i<99999;++i);
    
    //对数字进行转化成string
    string number;
    std::stringstream ss;
    ss<<block_number;
    ss>>number;
    CBuffer* res=getblk(block_number);
    res->write("the new block"+number);
    return res;
}

//将buf内的内容写入
void BufferPool::bwrite(CBuffer* buf,string str)
{
    //如果是延迟写，说明buf需要添加到链表头部
    if(buf->getstatus()==DELAY_WRITE)
    {
        freelist->addfreebuffer(buf, 1);
    }
    //不是延迟写，用for循环来说明写的持续时间
    else
    {
        for(int i=0;i<99999;++i);
        buf->write(str);
        Brelse(buf);
    }
}






