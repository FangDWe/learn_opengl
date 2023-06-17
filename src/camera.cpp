#include"camera.h"

camera::camera(glm::vec3 pos, glm::vec3 z, glm::vec3 y){
    c_pos = pos;
    c_look = normalize(z);
    c_head = normalize(y);
    yaw = -90.0;
    pitch = 0.0;
}

glm::mat4 camera::get_view_matrix(){
    return glm::lookAt(c_pos, c_pos+c_look, c_head);
}

camera::~camera()
{
}

void camera::move(float mx, float mz, int mode){
    if (mode == 0) {
		c_pos += mz * c_look;
	}
	else if (mode == 1) {
		c_pos += mz * getmZ();
	}
	c_pos += mx * getmX();
}

glm::vec3 camera::getmX() {
	return glm::normalize(glm::cross(c_look, c_head));
}

glm::vec3 camera::getmZ() {
	glm::vec3 mx = getmX();
	return glm::normalize(glm::cross(c_head, mx));
}

void camera::lookat(float offsetx, float offsety) {
	yaw += offsetx;
	pitch += offsety;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	c_look = glm::normalize(front);
}