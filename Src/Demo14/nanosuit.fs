#version 330 core
out vec4 FragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoords;
in vec3 color;

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
    vec3 diffuse1 = vec3(texture(material.texture_diffuse1, texCoords));
    FragColor = vec4(diffuse1, 1.0);
}