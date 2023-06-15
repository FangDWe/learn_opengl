#pragma once
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include<iostream>


GLFWwindow* GLFWInit() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(800, 600, "Blinn-Phong", NULL, NULL);
    if (window == NULL)
    {
        std :: cout << "Failed to create GLFW window" << std :: endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std :: cout << "Failed to initialize GLAD" << std :: endl;
        return NULL;
    }

    return window;
}