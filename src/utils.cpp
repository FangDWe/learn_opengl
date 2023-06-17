#include"utils.h"

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

DirLight get_dir_light(glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular){
    DirLight light;
    light.direction = dir;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    return light;
}

PointLight get_point_light(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float l, float q){
    PointLight light;
    light.position = pos;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    light.linear = l;
    light.quadratic = q;
    return light;
}

FlashLight get_flash_light(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float l, float q, float in, float out){
    FlashLight light;
    light.position = pos;
    light.direction = dir;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    light.linear = l;
    light.quadratic = q;
    light.cutOffin = in;
    light.cutOffout = out;
    return light;
}