//
//  DoublyLink.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/14.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#include "DoublyLink.hpp"
#include <iostream>



using std::cin;
using std::cout;
using std::endl;


DoublyLink::DoublyLink()
{
    header=NULL;
    tail=NULL;
}

DoublyLink::DoublyLink(const int block)
{
    class CBuffer* first=new CBuffer(block);
    header=first;
    tail=first;
}


class CBuffer*  DoublyLink::getbuffer(const int block) const
{
    //如果是一个空的双向链表进行处理
    if(header==NULL) return NULL;
    class CBuffer* buffer=this->header;
    //遍历寻找结点
    while(buffer!=NULL)
    {
        if(buffer->getblock()==block)
        {
            return buffer;
        }
        else
        {
            buffer=buffer->hash_next;
        }
    }
    //到达最终结点，查看寻找的是否是尾巴结点
    if(buffer==tail && buffer->getblock()!=block)
    {
        return NULL;
    }
    else
    {
        return buffer;
    }
}



//根据传入的结点，添加结点，返回值为1说明正常添加，返回值为-1，说明该结点已经存在，
//返回值为0，说明传入的空结点,添加结点直接添加在hash queue 尾巴
int DoublyLink::addbuffer(class CBuffer *buf)
{
    //传入的buf为空，返回0
    if(buf==NULL)
    {
        cout<<"the buf is NULL!"<<endl;
        return 0;
    }
    //判断添加的结点是否存在
    if(getbuffer(buf->getblock())!=NULL)
    {
        cout<<"the buf is exist!"<<endl;
        return -1;
    }
    if(header==NULL)
        header=buf;
    else
    {
        tail->hash_next=buf;
        buf->hash_prev=tail;
    }
    //buf成为尾巴
    tail=buf;
    return 1;
}



//根据block数，对指定结点进行删除，0，1判断是否成功
bool DoublyLink::deletebuffer(const int block)
{
    CBuffer *q=getbuffer(block);
    return deletebuffer(q);
    
}


//直接根据传入的结点直接删除，省去遍历链表的过程
bool DoublyLink::deletebuffer(class CBuffer* q)
{
    if(q==NULL) return false;
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
                q->hash_next->hash_prev=NULL;
                header=q->hash_next;
                q->hash_next=NULL;
            }
            //该结点为尾结点
            else if(q==tail)
            {
                q->hash_prev->hash_next=NULL;
                tail=q->hash_prev;
                q->hash_prev=NULL;
            }
            //该结点不为头结点也不为尾结点
            else{
                q->hash_prev->hash_next=q->hash_next;
                q->hash_next->hash_prev=q->hash_prev;
                q->hash_prev=q->hash_next=NULL;
            }
        }
    }
    return true;
}

DoublyLink::~DoublyLink()
{
    while(header!=NULL)
    {
        deletebuffer(header);
    }
}
