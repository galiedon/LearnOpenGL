#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

in vec3 normal;
in vec3 fragPos;
in vec2 texCoord;

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive;
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
    vec3 lightDir = normalize(light.lightPos - fragPos);

    vec3 diffuseTex = vec3(texture(material.diffuse, texCoord));
    
    // 环境光
    vec3 ambient = light.ambient * diffuseTex;

    // 漫反射
    vec3 diffuse = light.diffuse * max(dot(norm, lightDir), 0.0) * diffuseTex;

    // 镜面光照
    vec3 specularTex = vec3(texture(material.specular, texCoord));
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularTex * spec * light.specular;

    // 自发光
    vec3 emissive = vec3(texture(material.emissive, texCoord));


    vec3 result = ambient + diffuse + specular + emissive;
    FragColor = vec4(result, 1.0f);
}