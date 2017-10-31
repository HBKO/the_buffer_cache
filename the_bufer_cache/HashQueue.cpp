//
//  HashQueue,h.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/16.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#include "HashQueue.hpp"


HashQueue::HashQueue(const int mode):DoublyLink()
{
    mod=mode;
}

HashQueue::HashQueue(const int block,const int mode):DoublyLink(block)
{
    mod=mode;
}



//打印hashqueue所有结点
void HashQueue::printallhashnode()
{
    std::lock_guard<std::mutex> l(m);
    CBuffer* head=header;
    while(head!=NULL)
    {
        std::cout<<head->getblock()<<" "<< status[head->getstatus()] <<", ";
        head=head->hash_next;
    }
}






