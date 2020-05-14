
#version 110

uniform sampler2D CC_Texture0;
uniform sampler2D CC_Texture1;
uniform vec3 viewPos;

varying vec3 FragPos;
varying vec3 Normal;

varying vec2 v_texCoord;

struct Material {
   // uniform sampler2D diffuse;
   // uniform sampler2D specular;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};


uniform Material material;
uniform Light light;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
#define NR_POINT_LIGHTS 4  
uniform PointLight pointLights[NR_POINT_LIGHTS];


struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

uniform SpotLight spotLight;


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
       // 一些属性
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // 第一步，计算平行光照
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // 第二步，计算顶点光照
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // 第三部，计算 Spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    gl_FragColor = vec4(result, 1.0);

    // gl_FragColor = vec4(1.0f, 0.5f, 0.31f,1.0)*vec4(1.0f, 1.0f, 1.0f, 1.0f); 
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射强度
    vec3 reflectDir = reflect(-lightDir, normal);
    float tr = max(dot(viewDir, reflectDir), 0.0);
    float spec = pow(tr, material.shininess);
    // 合并各个光照分量
    vec3 ambient  = light.ambient  * vec3(texture2D(CC_Texture0, v_texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture2D(CC_Texture0, v_texCoord));
    vec3 specular = light.specular * spec * vec3(texture2D(CC_Texture1, v_texCoord));
    return (ambient + diffuse + specular);
  //return lightDir;
}  



// 计算定点光在确定位置的光照颜色
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // 计算漫反射强度
    float diff = max(dot(normal, lightDir), 0.0);
    // 计算镜面反射
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // 计算衰减
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance +
                 light.quadratic * (distance * distance));
    // 将各个分量合并
    vec3 ambient  = light.ambient  * vec3(texture2D(CC_Texture0, v_texCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture2D(CC_Texture0, v_texCoord));
    vec3 specular = light.specular * spec * vec3(texture2D(CC_Texture1, v_texCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture2D(CC_Texture0, v_texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture2D(CC_Texture0, v_texCoord));
    vec3 specular = light.specular * spec * vec3(texture2D(CC_Texture1, v_texCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}