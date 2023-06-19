#pragma once
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include<iostream>
#include<vector>
#include <glm/glm.hpp>


std::string get_shader_path(std::string name, std::string model);

struct DirLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight {
    glm::vec3 position;

    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct FlashLight {
    glm::vec3  position;
    glm::vec3  direction;
    float cutOffin;
    float cutOffout;
    
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


GLFWwindow* GLFWInit();

DirLight get_dir_light(glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

PointLight get_point_light(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float l, float q);

FlashLight get_flash_light(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float l, float q, float in, float out);

unsigned int load_cube_map(std::string base_path, std::vector<std::string> paths);

