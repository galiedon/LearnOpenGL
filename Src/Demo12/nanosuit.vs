#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aColor;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoords;
out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    fragPos = vec3(model * vec4(aPos, 1.0);
    normal = aNormal;
    texCoords = aTexCoords;
    color = aColor;
}