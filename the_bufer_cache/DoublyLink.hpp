//
//  DoublyLink.hpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/14.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#ifndef DoublyLink_hpp
#define DoublyLink_hpp

#define BUFFERHEAD -1
#include<string>
#include"buffer.hpp"


class DoublyLink
{
private:
    class CBuffer* header;    //队列头
    class CBuffer* tail;      //队列尾
public:
    DoublyLink();         //带有模数的构造函数
    DoublyLink(const int block);    //模数和block数的构造函数
    class CBuffer* getbuffer(const int block) const;       //根据block数来寻找对应的buffer,如果找不到就返回NULL
    // 尽量类成员中像get这类获取内容的函数，用const修饰，即不能修改得到的内容，但是得到的内容如果是指针，则可以修改指针指向的内容
    bool deletebuffer(const int block);              //根据block数，对指定结点进行删除，0，1判断是否成功
    bool deletebuffer(class CBuffer *q);      //直接根据传入的结点直接删除，省去遍历链表的过程
    int addbuffer(class CBuffer *buf);         //根据传入的结点，添加结点，返回值为1说明正常添加，返回值为-1，说明该结点已经存在，
    //返回值为0，说明传入的空结点
    ~DoublyLink();
};

#endif /* DoublyLink_hpp */
