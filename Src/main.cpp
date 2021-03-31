#include<iostream>
using namespace std;

#include "include/main.h"
#include "CMake.h"
#include "DemoBase.h"
#include "Demo1/Demo1.h"
#include "Demo2/Demo2.h"
#include "Demo3/Demo3.h"
#include "Demo4/Demo4.h"
#include "Demo5/Demo5.h"
#include "Demo6/Demo6.h"
#include <SOIL/SOIL.h>
using namespace glm;


void testGLM(){
    vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    // 译注：下面就是矩阵初始化的一个例子，如果使用的是0.9.9及以上版本
    // 下面这行代码就需要改为:
    // mat4 trans = mat4(1.0f)
    // 之后将不再进行提示
    
    mat4 trans(1.0f);
    trans = translate(trans, vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    
    std::cout << vec.x << vec.y << vec.z << std::endl;
}

int main(){
    DemoBase* demo = new Demo6();

    auto result = demo->run();

    return result;
}