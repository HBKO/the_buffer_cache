//
//  HashQueue,h.hpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/16.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#ifndef HashQueue_h_hpp
#define HashQueue_h_hpp


//派生类在实例化的时候，先实例化基类，然后实例化派生类，所以先调用基类的构造函数
//派生类利用初始化列表初始化基类的构造函数，不利用初始化列表的话
//有一种替代方案：1.直接传基类对象的引用进入。否则，就调用基类的默认构造函数（不含参）
//在实例对象释放的时候，是调用派生类的析构函数，后调用基类的析构函数


#include "DoublyLink.hpp"


class HashQueue:public DoublyLink
{
private:
    int mod;    //获取模数
public:
    HashQueue(const int mode);  //默认构造函数
    HashQueue(const int block,const int mode); //知道块号的构造函数
    int getmod() const {return mod;} //获取块号
    void printallhashnode();           //打印所有hashqueue的结点
};





#endif /* HashQueue_h_hpp */
