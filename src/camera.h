#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class camera
{
public:
    glm::vec3 c_pos, c_look, c_head;
    float yaw, pitch;
    camera(glm::vec3 pos, glm::vec3 z, glm::vec3 y);
    ~camera();
    glm::mat4 get_view_matrix();
    void move(float mx, float mz, int mode);
    void lookat(float offsetx, float offsety);
    glm::vec3 getmX();
	glm::vec3 getmZ();
};