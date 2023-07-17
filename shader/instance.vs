#version 330 core
layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;
layout (location = 3) in mat4 instancetrans;

layout (std140) uniform Matrices
{
    mat4 proj;
    mat4 view;
};

out vec3 Normal;
out vec3 FragPos;
out vec2 Tex;

void main()
{   
    gl_Position = proj * view * instancetrans * vec4(aPos, 1.0f);

    Normal = normalize(aNormal);
    FragPos = vec3(instancetrans * vec4(aPos, 1.0f));
    Tex = aTex;
}