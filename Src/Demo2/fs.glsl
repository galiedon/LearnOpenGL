#version 330 core
out vec4 FragColor;
in vec3 ourColor;

uniform vec4 outColor;

void main()
{
    FragColor = vec4(outColor.rgb * ourColor.rgb, 1);
}