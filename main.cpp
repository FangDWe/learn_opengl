#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include<iostream>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include"src/model.h"
#include"src/camera.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double x, double y);
glm::mat4 *randRadius(float radius, float offset1, float offset2, float min_scale, float max_scale, int amount);
void test1(GLFWwindow*  window);
void test2(GLFWwindow*  window);



float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 ambient = glm::vec3(0.2);
//camera cm(glm::vec3(0.0,0.0,5.0), glm::vec3(0.0,0.0,-1.0), glm::vec3(0.0,1.0,0.0));
camera cm(glm::vec3(0.0,0.0,115.0), glm::vec3(0.0,0.0,-1.0), glm::vec3(0.0,1.0,0.0));

int main()
{
#pragma region init glfw
    //glfw init in util.h
    GLFWwindow*  window = GLFWInit();

    glEnable(GL_MULTISAMPLE);

    //windows size changed callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
#pragma endregion

    test2(window);

    //close window
    glfwTerminate();

    cout << "ok" << endl;
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

    cm.move(movex, movez, 0);
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

    float sensitivity = 0.08;
    float offsetx = (x - xpos) * sensitivity;
    float offsety = (ypos - y) * sensitivity;
    xpos = x;
    ypos = y;

    cm.lookat(offsetx, offsety);
}

void test1(GLFWwindow*  window){
        // read shader and create progma
    ShaderProgma model_shader(get_shader_path("model", "vs").c_str(), get_shader_path("model", "fs").c_str());
    ShaderProgma sky_shader(get_shader_path("skybox", "vs").c_str(), get_shader_path("skybox", "fs").c_str());
    ShaderProgma colorgrad_shader(get_shader_path("colorgrad", "vs").c_str(), get_shader_path("colorgrad", "fs").c_str());
    //ShaderProgma glossy_shader(get_shader_path("glossy", "vs").c_str(), get_shader_path("glossy", "fs").c_str());

    vector<string> faces{
        "right.jpg",
        "left.jpg",
        "top.jpg",
        "bottom.jpg",
        "front.jpg",
        "back.jpg"
    };

    unsigned int skyboxTex = load_cube_map(string(current_path) + "/asset/skybox/", faces);

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    // glfwTerminate();



#pragma region init 3D relative asset
    cout << string(current_path) + string("/asset/nanosuit/nanosuit.obj") << endl;
    MModel::Model ourModel(string(current_path) + string("/asset/nanosuit/nanosuit.obj"), false);

    // cout << ourModel.textures_loaded.size() << endl;
    // cout << ourModel.meshes.size() << endl;
    // for(int i = 0; i < ourModel.meshes.size(); i++){
    //     cout << i << " " << ourModel.meshes[i].m_vertices.size() << endl;
    //     for(int j = 0; j < ourModel.meshes[i].m_textures.size(); j++){
    //         cout << i << " " << ourModel.meshes[i].m_textures[j].type << endl;
    //     }
    // }

     unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
#pragma endregion


    unsigned int framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    // create a color attachment texture
    unsigned int textureColorbuffer;
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "error framebuffer is not complete!" << endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

#pragma region run
    //open the window 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glm::mat4 trans = glm::mat4(1.0);
    glm::mat4 projection = glm::perspective(glm::radians(40.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    //model_shader.set_dir_light("dir_light", dirlight);
    //model_shader.set_flash_light("flash_light", flashlight);

    while(!glfwWindowShouldClose(window)){
        processInput(window);


        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 view = cm.get_view_matrix();
        
        sky_shader.use();
        glm::mat4 viewsky = glm::mat4(glm::mat3(view));
        sky_shader.set_mat4("proj", projection);
        sky_shader.set_mat4("view", viewsky);
        sky_shader.set_int("skybox", 0);
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);


        model_shader.use();
        model_shader.set_mat4("proj", projection);
        model_shader.set_mat4("view", view);
        model_shader.set_vec3("eye_pos", cm.c_pos);

        // render the loaded model
        // glossy_shader.use();
        // glossy_shader.set_mat4("proj", projection);
        // glossy_shader.set_mat4("view", view);
        // glossy_shader.set_vec3("eye_pos", cm.c_pos);
        // glossy_shader.set_int("skybox", 0);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        model_shader.set_mat4("trans", model);
        glm::mat4 ntrans = glm::transpose(glm::inverse(model));
        model_shader.set_mat4("ntrans", ntrans);
        ourModel.Draw(model_shader);



        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        //glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        colorgrad_shader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(quadVAO);
        glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
        colorgrad_shader.set_int("Raw", 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);


        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
#pragma endregion

    //release asset
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);

}


void test2(GLFWwindow*  window){
    // read shader and create progma
    ShaderProgma instan_shader(get_shader_path("instance", "vs").c_str(), get_shader_path("model", "fs").c_str());
    ShaderProgma model_shader(get_shader_path("model", "vs").c_str(), get_shader_path("model", "fs").c_str());

    stbi_set_flip_vertically_on_load(true);

#pragma region init 3D relative asset
    //cout << string(current_path) + string("/asset/planet/planet.obj") << endl;
    MModel::Model planet_model(string(current_path) + string("/asset/planet/planet.obj"), false);
    MModel::Model rock_model(string(current_path) + string("/asset/rock/rock.obj"), false);

    int amount = 100000;
    glm::mat4 * model_trans = randRadius(150.0f, 25.0f, 1.0f, 0.05f, 0.25f, amount);
    unsigned int instan;
    glGenBuffers(1, &instan);
    glBindBuffer(GL_ARRAY_BUFFER, instan);
    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), model_trans, GL_STATIC_DRAW);

    for(int i = 0; i < rock_model.meshes.size(); i++){
        glBindVertexArray(rock_model.meshes[i].VAO);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(2*sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void *)(3*sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);
        glBindVertexArray(0);
    }
#pragma endregion
    unsigned int uboMatrices;
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 128, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 128);

#pragma region run
    //open the window 

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glm::mat4 trans = glm::mat4(1.0);
    glm::mat4 model = glm::translate(trans, glm::vec3(0.0f, -3.0f, 0.0f));
    model = glm::scale(trans, glm::vec3(4.0f, 4.0f, 4.0f));
    glm::mat4 projection = glm::perspective(glm::radians(40.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);

    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    while(!glfwWindowShouldClose(window)){
        processInput(window);

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 view = cm.get_view_matrix();

        glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        model_shader.use();
        model_shader.set_mat4("proj", projection);
        model_shader.set_mat4("view", view);
        //model_shader.set_vec3("eye_pos", cm.c_pos);

        // render the loaded model
        model_shader.set_mat4("trans", model);
        glm::mat4 ntrans = glm::transpose(glm::inverse(model));
        model_shader.set_mat4("ntrans", ntrans);
        planet_model.Draw(model_shader);

        instan_shader.use();
        instan_shader.set_uniform_buffer("Matrices", 0);
        instan_shader.set_int("material.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, rock_model.textures_loaded[0].id);
        for(int i = 0; i < rock_model.meshes.size(); i++){
            glBindVertexArray(rock_model.meshes[i].VAO);
            glDrawElementsInstanced(GL_TRIANGLES, rock_model.meshes[i].m_indices.size(), GL_UNSIGNED_INT, 0, amount);
        }

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
#pragma endregion

    //release asset

}

glm::mat4 *randRadius(float radius, float offset1, float offset2, float min_scale, float max_scale, int amount){
    glm::mat4 *model_trans;
    model_trans = new glm::mat4[amount];
    srand(glfwGetTime());

    for(int i = 0; i < amount; i++){
        glm::mat4 t = glm::mat4(1.0);
        
        float angle = float(i)/float(amount)*360.0f;
        float d = (rand()%(int)(2*offset1*100))/100.0f - offset1;
        float y = (rand()%(int)(2*offset2*100))/100.0f - offset2;
        float x = sin(angle)*(radius+d);
        float z = cos(angle)*(radius+d);

        float scale = (rand()%(int)((max_scale-min_scale)*100))/100.0f + min_scale;
        float rot = (rand() % 360);

        t = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
        t = glm::scale(t, glm::vec3(scale));
        t = glm::rotate(t, rot, glm::vec3(0.4f, 0.6f, 0.8f));

        model_trans[i] = t;
    }

    return model_trans;
}