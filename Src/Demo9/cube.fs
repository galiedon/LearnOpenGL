#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

in vec3 normal;
in vec3 fragPos;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light{
    vec3 lightPos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir =normalize(light.lightPos - fragPos);

    // 环境光强度
    vec3 ambient = material.ambient * light.ambient;

    // 漫反射
    vec3 diffuse = light.diffuse * max(dot(norm, lightDir), 0.0) * material.diffuse;

    // 镜面光照
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = material.specular * spec * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0f);
}