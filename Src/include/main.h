#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <array>
#include <string>
using std::string;
using std::vector;
using std::array;

#define SUCCESS 0
#define FAILED -1

#define uint unsigned int

typedef union{
    float v[4];

    struct{
        float x;
        float y;
        float z;
        float w;
    };

    struct{
        float r;
        float g;
        float b;
        float a;
    };
}Vector4,Color;

typedef union{
    float v[3];

    struct{
        float x;
        float y;
        float z;
    };

    struct{
        float r;
        float g;
        float b;
    };
}Vector3,Color3;