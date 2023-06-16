#version 330 core
out vec4 FragColor;

out vec4 FragColor;  

in vec3 Normal;
in vec3 FragPos;
in vec2 Tex;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct FlashLight {
    vec3  position;
    vec3  direction;
    float cutOffin;
    float cutOffout;
    
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


struct Material {
    sampler2D diffuse;
    sampler2D specular;
}; 
#define NR_POINT_LIGHTS 4
uniform PointLight point_light;

uniform DirLight dir_light;
uniform vec3 eye_pos;
uniform vec3 ambient_light;
uniform Material material;


vec3 calc_dir_light(DirLight light, vec3 norm, vec3 w, vec3 diff_color, vec3 spec_color){
    vec3 v = -normalize(light.direction);
    vec3 diffuse = (max(dot(norm, v), 0.0)*light.diffuse + light.ambient)* diff_color;

    vec3 h = normalize(v + w);
    vec3 specular = pow(max(dot(norm, h), 0.0), 64) * spec_color * light.specular;

    return diffuse + specular;
}

vec3 calc_point_light(PointLight light, vec3 norm, vec3 FragPos, vec3 w, vec3 diff_color, vec3 spec_color){
    vec3 v = normalize(light.position - FragPos);
    float d = length(light.position - FragPos);
    float atten = 1.0/(1.0 + light.linear * d + light.quadratic *d*d);

    vec3 diffuse = (max(dot(norm, v), 0.0)*light.diffuse + light.ambient)* diff_color;

    vec3 h = normalize(v + w);
    vec3 specular = pow(max(dot(norm, h), 0.0), 64) * spec_color * light.specular;

    return (diffuse + specular) * atten;
}

vec3 calc_flash_light(FlashLight light, vec3 norm, vec3 FragPos, vec3 w, vec3 diff_color, vec3 spec_color){
    vec3 v = normalize(light.position - FragPos);

    float theta = dot(-v, normalize(light.direction));
    theta = min((theta-light.cutOffout)/(light.cutOffin - light.cutOffout), 1.0);
    
    if(theta > 0.0){
        float d = length(light.position - FragPos);
        float atten = 1.0/(1.0 + light.linear * d + light.quadratic *d*d);

        vec3 diffuse = (max(dot(norm, v), 0.0)*light.diffuse + light.ambient)* diff_color;

        vec3 h = normalize(v + w);
        vec3 specular = pow(max(dot(norm, h), 0.0), 64) * spec_color * light.specular;
        return (diffuse + specular) * atten * theta;
    }
    else{
        return vec3(0.0);
    }
}

void main()
{
    vec3 diff_color = vec3(texture(material.diffuse, Tex));
    vec3 spec_color = vec3(texture(material.specular, Tex));

    vec3 norm = normalize(Normal);
    vec3 w = normalize(eye_pos - FragPos);

    vec3 light_total = calc_dir_light(dirLight, norm, w, diff_color, spec_color);
    light_total += calc_point_light(point_light, norm, w, diff_color, spec_color);

    FragColor = vec4(light_total, 1.0);
}