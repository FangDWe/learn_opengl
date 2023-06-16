#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<iostream>
#include"src/utils.h"
#include"src/shader.h"
#include"src/camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main()
{
#pragma region init glfw and shader
    // glfw init in util.h
    GLFWwindow*  window = GLFWInit();

    //windows size changed callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    // read shader and create progma
    std::string vs = std::string(current_path) + std::string("/shader/VertexShader.vs"), fs = std::string(current_path) + std::string("/shader/FragmentShader.fs");
    ShaderProgma progma1(vs.c_str(), fs.c_str());
#pragma endregion


#pragma region init 3D relative
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile("D:\\resource\\nanosuit\\nanosuit.obj", aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return 0;
    }

    glm::mat4 premat = glm::mat4(1.0);
    camera cm(glm::vec3(0.0,0.0,-3.0), glm::vec3(0.0,0.0,-1.0), glm::vec3(0.0,1.0,0.0));
    premat = cm.get_view_matrix();
#pragma endregion


    //open the window
    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    //close window
    glfwTerminate();

    //release asset

    std::cout << "ok" << std::endl;
	return 0;
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 0.05f, movez = 0, movex = 0; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movez += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movez -= cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movex -= cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movex += cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double x, double y) {
    static bool first = true;
    static float xpos, ypos;
    if (first) {
        xpos = x;
        ypos = y;
        first = false;
    }

    float sensitivity = 0.05;
    float offsetx = (x - xpos) * sensitivity;
    float offsety = (ypos - y) * sensitivity;
    xpos = x;
    ypos = y;

    //cm.lookat(offsetx, offsety);
}