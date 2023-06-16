#pragma once
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"src/utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iostream>
#include<fstream>
#include<sstream>

class ShaderProgma
{
public:
	ShaderProgma(const char* vertex_shader_path, const char* frag_shader_path);
	~ShaderProgma();
    void use(){
        glUseProgram(ID);
    }

	void set_vec3(std::string name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
	}
    void set_vec3(std::string name, glm::vec3 v) {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), v.x, v.y, v.z);
	}

    void set_mat4(std::string name, glm::mat4 m){
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
    }

    void set_float(std::string name, float a){
        glUniform1f(glGetUniformLocation(ID, name.c_str()), a);
    }

    void set_int(std::string name, unsigned int a){
        glUniform1i(glGetUniformLocation(ID, name.c_str()), a);
    }

    void set_dir_light(std::string name, DirLight light);
    void set_point_light(std::string name, PointLight light);
    void set_flash_light(std::string name, FlashLight light);
private:
	unsigned int ID;
};

ShaderProgma::ShaderProgma(const char* vertex_shader_path, const char* frag_shader_path){
    std::ifstream vsf, fsf;
    vsf.open(vertex_shader_path);
    fsf.open(frag_shader_path);
    if (!vsf || !fsf) {
        std::cout << "open shader file error" << std::endl;
        return;
    }

    const char* vShaderCode, * fShaderCode;
    std::string vShaderString, fShaderString;
    std::stringstream vsStream, fsStream;
    vsStream << vsf.rdbuf();
    fsStream << fsf.rdbuf();

    vsf.close();
    fsf.close();

    vShaderString = vsStream.str();
    fShaderString = fsStream.str();

    vShaderCode = vShaderString.c_str();
    fShaderCode = fShaderString.c_str();




    //create shader
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "SHADER VERTEX COMPILATION FAILED\n" << infoLog << std::endl;
    };


    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "SHADER FRAGMENT COMPILATION FAILED\n" << infoLog << std::endl;
    };




    //link shader
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "SHADER PROGRAM LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

ShaderProgma::~ShaderProgma(){
}

void ShaderProgma::set_dir_light(std::string name, DirLight light){
    set_vec3(name+".direction", light.direction);
    set_vec3(name+".ambient", light.ambient);
    set_vec3(name+".diffuse", light.diffuse);
    set_vec3(name+".specular", light.specular);
}

void ShaderProgma::set_point_light(std::string name, PointLight light){
    set_vec3(name+".position", light.position);
    set_vec3(name+".ambient", light.ambient);
    set_vec3(name+".diffuse", light.diffuse);
    set_vec3(name+".specular", light.specular);

    set_float(name+".linear", light.linear);
    set_float(name+".quadratic", light.quadratic); 
}


void ShaderProgma::set_flash_light(std::string name, FlashLight light){
    set_vec3(name+".direction", light.direction);
    set_vec3(name+".position", light.position);
    set_vec3(name+".ambient", light.ambient);
    set_vec3(name+".diffuse", light.diffuse);
    set_vec3(name+".specular", light.specular);

    set_float(name+".linear", light.linear);
    set_float(name+".quadratic", light.quadratic); 
    set_float(name+".cutOffin", light.cutOffin);
    set_float(name+".cutOffout", light.cutOffout); 
}