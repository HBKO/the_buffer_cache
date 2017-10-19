//
//  FreeList.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/16.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#include "FreeList.hpp"
#include <string>
//#include <atomic>
using std::cout;
using std::cin;
using std::endl;
//std::atomic_flag free_lock = ATOMIC_FLAG_INIT;
//因为引用了DoublyLink的头文件，对于全局变量来说，两个文件的全局变量不能相同，考虑把free_lock的全局变量变成成员变量，但是感觉还是有些问题
//所以这边直接采用了两个atomic_flag的全局变量


FreeList::FreeList():DoublyLink()
{
}



//如果为空，则返回NULL,直接返回头结点就好，因为都是从头开始分配
CBuffer* FreeList::alloc()
{
    return header;
}



//添加结点，可以选择添加到尾巴还是添加到头部,1为添加到头部，0为添加到尾部,返回0说明添加错误，返回1说明添加正确
int FreeList::addfreebuffer(CBuffer* buf, int isfirst)
{
    //利用mutex进行保护链表的操作,利用lock_guard<std::mutex>的模版接口可以不用在每个返回的时候都执行一次clear,利用lock_guard在函数结束的时候
    //析构的时候，锁就自动还原了。
    std::lock_guard<std::mutex> l(fm);
    if(buf==NULL)
    {
        return 0;
    }
    if(header==NULL)
    {
        header=tail=buf;
    }
    else
    {
        if(isfirst==1)
        {
            buf->freelist_next=header;
            header->freelist_prev=buf;
            header=buf;
        }
        else if(isfirst==0)
        {
            buf->freelist_prev=tail;
            tail->freelist_next=buf;
            tail=buf;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}


//提供删除结点的功能，因为这个链表控制的是freelist这个指针，所以不能继承，要重新设置，虽然删除结点的功能类型
bool FreeList::removefreebuffer(CBuffer* q)
{
    //利用mutex进行保护链表的操作,利用lock_guard<std::mutex>的模版接口可以不用在每个返回的时候都执行一次clear,利用lock_guard在函数结束的时候
    //析构的时候，锁就自动还原了。
    std::lock_guard<std::mutex> l(fm);
    if(q==NULL)
    {
        return false;
    }
    else
    {
        //只有一个结点的情况
        if(tail==header)
        {
            tail=header=NULL;
        }
        //不只有一个结点
        else
        {
            //该结点为头结点
            if(q==header)
            {
                q->freelist_next->freelist_prev=NULL;
                header=q->freelist_next;
                q->freelist_next=NULL;
            }
            //该结点为尾结点
            else if(q==tail)
            {
                q->freelist_prev->freelist_next=NULL;
                tail=q->freelist_prev;
                q->freelist_prev=NULL;
            }
            //该结点不为头结点也不为尾结点
            else{
                q->freelist_prev->freelist_next=q->freelist_next;
                q->freelist_next->freelist_prev=q->freelist_prev;
                q->freelist_prev=q->freelist_next=NULL;
            }
        }
    }
    return true;

}


//析构函数
FreeList::~FreeList()
{
    while(header!=NULL)
        removefreebuffer(header);
}
