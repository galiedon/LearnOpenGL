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
    // [0, 1] -> [-1, 1](NDC)
    float z = gl_FragCoord.z * 2 - 1;
    float linearDepth = (2 * near * far) / (far + near - z * (far - near));
    FragColor = vec4(vec3(linearDepth / far), 1.0);
}