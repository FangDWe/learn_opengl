#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 Tex;

uniform vec3 eye_pos;
uniform samplerCube skybox;

void main()
{
    vec3 w = normalize(eye_pos - FragPos);
    vec3 norm = normalize(Normal);

    vec3 v = 2*dot(w, norm)*norm - w;

    // vec3 spec_color = vec3(texture(material.specular, Tex));

    // vec3 norm = normalize(Normal);
    // vec3 w = normalize(eye_pos - FragPos);

    //vec3 light_total = calc_dir_light(dir_light, norm, w, diff_color, spec_color);
    //vec3 light_total = calc_point_light(point_light, norm, FragPos, w, diff_color, spec_color);
    //vec3 light_total = calc_flash_light(flash_light, norm, FragPos, w, diff_color, spec_color);

    FragColor = texture(skybox, v);
    
    //FragColor = vec4(light_total, 1.0);
}