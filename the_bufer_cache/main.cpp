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
#include "buffer.h"   //引入buffer头文件
const int Num=10;
using std::cout;
using std::cin;
using std::string;
using std::endl;

int main(int argc, const char * argv[]) {
    // insert code here...
    string test_1="Hello World!";
    CBuffer test(10,test_1);
    CBuffer test_2(2);
    cout<<"test's block: "<<test.getblock()<<" the test's status: "<<test.getstatus()<<endl;
    cout<<"test_2's block: "<<test_2.getblock()<< " the test_2's status: "<<test_2.getstatus()<<endl;
    cout<<"the test's data: "<<test.read()<<endl;
    cout<<"the test_2's data: "<<test_2.read()<<endl;
    test.write("the data is something\n");
    cout<<"the test's data: "<<test.read()<<endl;
    return 0;
}
