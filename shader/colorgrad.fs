#version 330 core
out vec4 FragColor;

in vec2 Tex;

uniform sampler2D Raw;
//uniform sampler2D LUT;
//uniform float grade;

void main(){
    vec4 RawColor = texture(Raw, Tex);
    FragColor = RawColor;
}