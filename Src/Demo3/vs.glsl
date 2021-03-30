#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float bias;

out vec3 ourColor;
out vec2 texCoord;

void main()
{
    gl_Position = vec4(aPos.x + bias/2, -aPos.y, aPos.z, 1.0);

    ourColor = aColor;
    // texCoord = (vec2(aPos.x + bias/2, aPos.y)+1)/2;
    // 练习2：尝试用不同的纹理环绕方式，
    // 设定一个从[0, 2]范围内的(而不是原来的[0, 1])纹理坐标。
    // 试试看能不能在箱子的角落放置4个笑脸
    // texCoord = (vec2(aPos.x + bias/2, aPos.y)+1);
    texCoord = (vec2(aPos.x + bias/2, aPos.y)+1);
}