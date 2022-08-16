#include<iostream>
using namespace std;

#include "include/main.h"
// #include "CMake.h"
#include "DemoBase.h"
#include "Demo1/Demo1.h"
#include "Demo2/Demo2.h"
#include "Demo3/Demo3.h"
#include "Demo4/Demo4.h"
#include "Demo5/Demo5.h"
#include "Demo6/Demo6.h"
#include "Demo7/Demo7.h"
#include "Demo8/Demo8.h"
#include "Demo9/Demo9.h"
#include "Demo10/Demo10.h"
#include "Demo11/Demo11.h"
#include "Demo12/Demo12.h"
#include "Demo13/Demo13.h"
#include "Demo14/Demo14.h"
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace glm;

int main(){
    DemoBase* demo = new Demo14();

    auto result = demo->run();

    return result;
}