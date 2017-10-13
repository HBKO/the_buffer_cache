//
//  stcktp1.h
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/13.
//  Copyright © 2017年 何柯文. All rights reserved.
//

#ifndef stcktp1_h
#define stcktp1_h


template <class Type>
class Stack
{
private:
    enum {SIZE=10}; //default size
    int stacksize;
    Type * items;    //holds stack items
    int top;         // index for top stack item
public:
    explicit Stack(int ss=SIZE);   //explicit关键词表示该构造函数不能隐式调用，隐式调用可以表示为Stack st=10;相当于隐式调用构造函数
    Stack(const Stack & st);
    ~Stack() {delete [] items; }
    bool isempty() {return top==0;}
    bool isfull() {return top==stacksize;}
    bool push(const Type & item);  //add item to stack
    bool pop(Type & item);          // pop top into item
    Stack & operator=(const Stack & st);
};

template <class Type>
Stack<Type>:: Stack(int ss):stacksize(ss),top(0)  //初始化列表
{
    items=new Type [stacksize];
}

template <class Type>
Stack<Type>::Stack(const Stack & st)   //拷贝构造函数
{
    stacksize=st.stacksize;
    top=st.top;
    items=new Type[stacksize];
    for(int i=0;i<top;++i)
        items[i]=st.items[i];
}

template <class Type>
bool Stack<Type>::push(const Type & item)
{
    if(top<stacksize)
    {
        items[top++]=item;
        return true;
    }
    else
        return false;
}

template <class Type>
bool Stack<Type>::pop(Type & item)
{
    if(top>0)
    {
        item=items[--top];
        return true;
    }
    else
        return false;
}

template <class Type>
Stack<Type> & Stack<Type>::operator=(const Stack<Type> & st)
{
    if(this == &st)
        return *this;
    delete [] items;
    stacksize=st.stacksize;
    top=st.top;
    items=new Type[stacksize];
    for(int i=0;i<top;++i)
        items[i]=st.items[i];
    return *this;
}



#endif /* stcktp1_h */
