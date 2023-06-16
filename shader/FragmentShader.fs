#version 330 core
out vec4 FragColor;

struct DirLight{
    vec3 direction;
}

struct PointLight{

}

struct FlashLight{

}

void main()
{
    FragColor = vec4(0.5, 0.0, 0.0, 1.0);
}