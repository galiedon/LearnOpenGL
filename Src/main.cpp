#include<iostream>
using namespace std;

#include "include/main.h"
#include "CMake.h"
#include "DemoBase.h"
#include "Demo1/Demo1.h"

int main(){
    
    DemoBase* demo = new Demo1();

    auto result = demo->run();

    return result;
}