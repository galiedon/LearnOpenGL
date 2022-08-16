#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 normal;
out vec3 fragPos;
out vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    fragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    normal = vec3(transpose(inverse(model)) * vec4(aNormal, 0.0));
    texCoord = aTexCoord;
}