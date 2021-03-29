#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float bias;

out vec3 ourColor;

void main()
{
    // 练习1： 让三角形上下颠倒
    // 原理：[-1,1] -> [0,1] -> [1, 0] -> [1, -1] 简化得：-aPos.y
    
    // gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
    
    //练习2： 通过uniform实现三角形的移动
    gl_Position = vec4(aPos.x + bias/2, -aPos.y, aPos.z, 1.0);


    ourColor = aColor;
}