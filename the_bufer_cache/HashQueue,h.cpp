//
//  HashQueue,h.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/16.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#include "HashQueue,h.hpp"


HashQueue::HashQueue(const int mode):DoublyLink()
{
    mod=mode;
}

HashQueue::HashQueue(const int block,const int mode):DoublyLink(block)
{
    mod=mode;
}


