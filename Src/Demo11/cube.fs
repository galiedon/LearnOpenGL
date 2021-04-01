#version 330 core
out vec4 FragColor;

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

// phone 光照模型
struct PhoneLightModel{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    vec3 color;
};

// 平行光
struct DirLight{
    vec3 direction;
    PhoneLightModel model;
};
uniform DirLight dirLight;

// 点光源
struct PointLight{
    vec3 pos;
    PhoneLightModel model;
    
    float constant;
    float linear;
    float quadratic;
};
#define POINT_LIGHT_NUM 4
uniform PointLight pointLight;
uniform PointLight pointLights[POINT_LIGHT_NUM];

// 聚光
struct SpotLight{
    vec3 pos;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    
    PhoneLightModel model;
    sampler2D color;
};
uniform SpotLight spotLight;

uniform int renderTestId;

vec3 calcDirectionLighting(DirLight dirLight, vec3 normal, vec3 viewDir){

    vec3 norm = normalize(normal);
    vec3 lightDir = -normalize(dirLight.direction);

    vec3 diffuseTex = vec3(texture(material.diffuse, texCoord));
    
    // 环境光
    vec3 ambient = dirLight.model.ambient * diffuseTex;

    // 漫反射
    vec3 diffuse = dirLight.model.diffuse * max(dot(norm, lightDir), 0.0) * diffuseTex;

    // 镜面光照
    vec3 specularTex = vec3(texture(material.specular, texCoord));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularTex * spec * dirLight.model.specular;

    return ambient + diffuse + specular;
}

vec3 calcPointLighting(PointLight pointLight, vec3 normal, vec3 fragPos, vec3 viewDir){

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(pointLight.pos - fragPos);

    vec3 diffuseTex = vec3(texture(material.diffuse, texCoord));

    // 计算衰减
    float dist = length(pointLight.pos - fragPos);
    float linear = pointLight.linear * dist;
    float quad = pointLight.quadratic * dist * dist;
    float attenuation = 1.0/(pointLight.constant + linear + quad);
    
    // 环境光
    vec3 ambient = pointLight.model.ambient * diffuseTex;

    // 漫反射
    vec3 diffuse = pointLight.model.diffuse * max(dot(norm, lightDir), 0.0) * diffuseTex;

    // 镜面光照
    vec3 specularTex = vec3(texture(material.specular, texCoord));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularTex * spec * pointLight.model.specular;

    return (ambient + diffuse + specular) * attenuation;
}


vec3 calcSpotLighting(SpotLight spotLight, vec3 normal, vec3 fragPos, vec3 viewDir){

    vec3 lightDir = normalize(spotLight.pos - fragPos);
    float theta = dot(lightDir, normalize(-spotLight.direction));
    float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
    vec3 diffuseTex = vec3(texture(material.diffuse, texCoord));

    // 计算衰减
    float dist = length(spotLight.pos - fragPos);
    float linear = spotLight.linear * dist;
    float quad = spotLight.quadratic * dist * dist;
    float attenuation = 1.0/(spotLight.constant + linear + quad);

    vec3 lightColor = vec3(texture(spotLight.color, texCoord)); 
    
    // 环境光
    vec3 ambient = spotLight.model.ambient * diffuseTex;

    vec3 norm = normalize(normal);

    // 漫反射
    vec3 diffuse = spotLight.model.diffuse * max(dot(norm, lightDir), 0.0) * diffuseTex;

    // 镜面光照
    vec3 specularTex = vec3(texture(material.specular, texCoord));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = specularTex * spec * spotLight.model.specular;

    return ambient + (diffuse + specular) * intensity * attenuation;
}

vec4 dirLightingRender(){
    // 自发光
    vec3 emissive = vec3(texture(material.emissive, texCoord));
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result;
    result += calcDirectionLighting(dirLight, normal, viewDir);

    return vec4(result, 1.0f);
}

vec4 pointLightingRender(){
    // 自发光
    vec3 emissive = vec3(texture(material.emissive, texCoord));
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result;
    result += calcPointLighting(pointLight, normal, fragPos, viewDir);

    return vec4(result, 1.0f);
}

vec4 spotLightingRender(){
    // 自发光
    vec3 emissive = vec3(texture(material.emissive, texCoord));
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result;
    result += calcSpotLighting(spotLight, normal, fragPos, viewDir);

    return vec4(result, 1.0f);
}

vec4 mixLightingRender(){
    // 自发光
    vec3 emissive = vec3(texture(material.emissive, texCoord));
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 result;

    result += calcDirectionLighting(dirLight, normal, viewDir);
    int i = 0;
    for(i = 0; i < POINT_LIGHT_NUM; i += 1){
        result += calcPointLighting(pointLights[i], normal, fragPos, viewDir);
    }

    result += calcSpotLighting(spotLight, normal, fragPos, viewDir);

    return vec4(result, 1.0f);
}

void main()
{
    if(renderTestId == 1){
        FragColor = dirLightingRender();
    }else if(renderTestId == 2){
        FragColor = pointLightingRender();
    }else if(renderTestId == 3){
        FragColor = spotLightingRender();
    }else{
        FragColor = mixLightingRender();
    }
}
