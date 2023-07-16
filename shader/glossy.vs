#version 330 core
layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aNormal;
//layout (location = 2) in vec2 aTex;

out vec3 Normal;
out vec3 FragPos;
//out vec2 Tex;

uniform mat4 trans;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 ntrans;

void main()
{   
    gl_Position = proj * view * trans * vec4(aPos, 1.0f);

    Normal = normalize(vec3(ntrans * vec4(aNormal, 1.0)));
    FragPos = vec3(trans * vec4(aPos, 1.0f));
    //Tex = aTex;
}