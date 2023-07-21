#include"utils.h"
#include"src/stb_image.h"

std::string get_shader_path(std::string name, std::string stype){
    return std::string(current_path) + "/shader/" + name + "." + stype;
}

GLFWwindow* GLFWInit() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

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

unsigned int load_cube_map(std::string base_path, std::vector<std::string> paths){
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for(unsigned int i = 0; i < paths.size(); i++){
        unsigned char* data = stbi_load((base_path+paths[i]).c_str(), &width, &height, &nrChannels, 0);

        if(data){
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else{
            std::cout << "cube map error " << paths[i] << std::endl;
            stbi_image_free(data);
            return -1;
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

// {
//         unsigned int textureID;
//     glGenTextures(1, &textureID);
//     glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

//     int width, height, nrChannels;
//     for (unsigned int i = 0; i < paths.size(); i++)
//     {
//         unsigned char *data = stbi_load((base_path+paths[i]).c_str(), &width, &height, &nrChannels, 0);
//         if (data)
//         {
//             glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//             stbi_image_free(data);
//         }
//         else
//         {
//             std::cout << "Cubemap texture failed to load at path: " << paths[i] << std::endl;
//             stbi_image_free(data);
//         }
//     }
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//     glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//     return textureID;
// }