#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class camera
{
private:
    /* data */
public:
    glm::vec3 c_pos, c_look, c_head;
    float Yaw, Pitch;
    camera(glm::vec3 pos, glm::vec3 z, glm::vec3 y);
    ~camera();
    glm::mat4 get_view_matrix();
};

camera::camera(glm::vec3 pos, glm::vec3 z, glm::vec3 y){
    c_pos = pos;
    c_look = normalize(z);
    c_head = normalize(y);
    Yaw = -90.0;
    Pitch = 0.0;
}

glm::mat4 camera::get_view_matrix(){
    return glm::lookAt(c_pos, c_pos+c_look, c_head);
}

camera::~camera()
{
}
