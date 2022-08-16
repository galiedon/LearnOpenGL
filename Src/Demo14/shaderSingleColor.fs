#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;
in vec3 color;

float near = 0.1; 
float far  = 10.0; 

struct Material{
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;
    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_specular3;
};

uniform Material material;

void main()
{
    // FragColor = vec4(0.04, 0.28, 0.26, 1.0);
    FragColor = vec4(0.04, 0.28, 0.26, 1.0);
}   