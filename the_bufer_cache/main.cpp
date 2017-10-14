//
//  main.cpp
//  the_bufer_cache
//
//  Created by 何柯文 on 2017/10/13.
//  Copyright © 2017年 何柯文. All rights reserved.
//


// stacktem.cpp -- testing the template stack class
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib> // for rand(),srand()
#include <ctime>    // for time()
#include "stcktp1.h"
#include "buffer.hpp"   //引入buffer头文件
#include "DoublyLink.hpp"
using std::cout;
using std::cin;
using std::string;
using std::endl;

int main(int argc, const char * argv[]) {
    // insert code here...
    CBuffer test(10,"the 10th CBuffer");
    CBuffer test_2(2);
    CBuffer test_3(3,"the third CBuffer");
    CBuffer test_4(4,"the 4th CBuffer");
    CBuffer test_5(4);
    DoublyLink hash_queue;
    cout<<hash_queue.deletebuffer(4)<<endl;
    hash_queue.addbuffer(&test);
    CBuffer *temp=hash_queue.getbuffer(10);
    cout<<temp->read()<<endl;
    cout<<hash_queue.deletebuffer(10)<<endl;
    temp=hash_queue.getbuffer(10);
    if(temp==NULL) cout<<"the temp is NULL."<<endl;
    hash_queue.addbuffer(&test_2);
    hash_queue.addbuffer(&test_3);
    hash_queue.addbuffer(&test_4);
    hash_queue.addbuffer(&test_5);
    temp=hash_queue.getbuffer(2);
    cout<<(temp->read())<<endl;
    temp=hash_queue.getbuffer(3);
    cout<<(temp->read())<<endl;
    temp=hash_queue.getbuffer(4);
    cout<<(temp->read())<<endl;
    hash_queue.deletebuffer(3);
    hash_queue.deletebuffer(2);
    temp=hash_queue.getbuffer(4);
    cout<<(temp->read())<<endl;
    hash_queue.deletebuffer(4);
    temp=hash_queue.getbuffer(4);
    if(temp==NULL) cout<<"the temp is NULL."<<endl;
    return 0;
}
