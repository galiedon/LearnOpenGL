#include<iostream>
using namespace std;

#include "include/main.h"
#include "CMake.h"
#include "DemoBase.h"
#include "Demo1/Demo1.h"
#include "Demo2/Demo2.h"

int main(){
    
    DemoBase* demo = new Demo2();

    auto result = demo->run();

    return result;
}