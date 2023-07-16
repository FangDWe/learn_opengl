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
    void use();
	void set_vec3(std::string name, float x, float y, float z);
    void set_vec3(std::string name, glm::vec3 v);
    void set_mat4(std::string name, glm::mat4 m);
    void set_float(std::string name, float a);
    void set_int(std::string name, unsigned int a);

    void set_dir_light(std::string name, DirLight light);
    void set_point_light(std::string name, PointLight light);
    void set_flash_light(std::string name, FlashLight light);
    void set_uniform_buffer(std::string name, unsigned int a);
private:
	unsigned int ID;
};
