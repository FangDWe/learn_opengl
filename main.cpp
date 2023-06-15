#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include"src/utils.h"
#include"src/shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main()
{
    // glfw init in util.h
    GLFWwindow*  window = GLFWInit();

    //windows size changed callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // read shader and create progma
    std::string vs = std::string(current_path) + std::string("/shader/VertexShader.vs"), fs = std::string(current_path) + std::string("/shader/FragmentShader.fs");
    ShaderProgma progma1(vs.c_str(), fs.c_str());
    
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("D:\\resource\\nanosuit\\nanosuit.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return 0;
    }

    glm::mat4 premat = glm::mat4(1.0);

    glfwTerminate();
    std::cout << "ok" << premat[0][0] << std::endl;
    int a;
    std :: cin >> a;
	return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}