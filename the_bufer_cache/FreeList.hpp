//
//  FreeList.hpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/16.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#ifndef FreeList_hpp
#define FreeList_hpp

#include <iostream>
#include "DoublyLink.hpp"


class FreeList:public DoublyLink
{
private:
    mutable std::mutex fm;
public:
    FreeList();
    CBuffer* alloc();  //提供申请一个结点的功能，没有就返回NULL
    int addfreebuffer(CBuffer* buf,int isfirst); //提供从链表头添加还是从链表尾添加的功能
    bool removefreebuffer(CBuffer* q);  //提供删除结点的功能
    void printallfreenode();            //打印所有空闲结点
    ~FreeList();
    
};

#endif /* FreeList_hpp */
