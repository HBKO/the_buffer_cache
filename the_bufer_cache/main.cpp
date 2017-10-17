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
#include "HashQueue,h.hpp"
#include "FreeList.hpp"
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
    CBuffer* temp;
    return 0;
}
